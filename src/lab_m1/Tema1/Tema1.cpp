#include "lab_m1/Tema1/Tema1.h"
#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Start the game
    lives = 3;
    score = 0;
    totalDucks = 0;
    bulletRevolverX = 0;
    bulletRevolverY = 0;

    spawnDuck();

    // Create the grass rectangle
    Mesh* grass = object2D::CreateRectangle("grass", glm::vec3(0, 0, 0), window->GetResolution().x, 100, glm::vec3(0.6823f, 1, 0.2f), true);
    AddMeshToList(grass);

    // Create the sky rectangle
    Mesh* sky = object2D::CreateRectangle("sky", glm::vec3(0, 0, 0), window->GetResolution().x, 100, glm::vec3(0.2f, 0.8313f, 1), true);
    AddMeshToList(sky);

    // Create the cloud circle
    Mesh* cloud = object2D::CreateCircle("cloud", 40, glm::vec3(0.9529f, 0.9137f, 0.9372f));
    AddMeshToList(cloud);

    // Create the body triangle
    Mesh* body = object2D::CreateTriangle("body", glm::vec3(-80, 50, 0), glm::vec3(-80, -50, 0), glm::vec3(80, 0, 0), glm::vec3(0.1137f, 0.8901f, 0.7372f));
    AddMeshToList(body);

    // Create the wing triangle
    Mesh* wing = object2D::CreateTriangle("wing", glm::vec3(0, 30, 0), glm::vec3(0, -30, 0), glm::vec3(100, 0, 0), glm::vec3(0.1137f, 0.8901f, 0.7372f));
    AddMeshToList(wing);

    // Create the head circle
    Mesh* head = object2D::CreateCircle("head", 40, glm::vec3(0.6f, 0.4f, 0.4f));
    AddMeshToList(head);

    // Create the beak triangle
    Mesh* beak = object2D::CreateTriangle("beak", glm::vec3(0, 10, 0), glm::vec3(0, -10, 0), glm::vec3(30, 0, 0), glm::vec3(0.9f, 0.8f, 0.2f));
    AddMeshToList(beak);

    // Create the life circle
    Mesh* life = object2D::CreateCircle("life", 20, glm::vec3(1, 0.2f, 0.4352f));
    AddMeshToList(life);

    // Create the bullet square
    Mesh* bullet = object2D::CreateSquare("bullet", glm::vec3(0, 0, 0), 40, glm::vec3(0.6156f, 0.2f, 1), true);
    AddMeshToList(bullet);

    // Create the score squares (solid and wired)
    Mesh* solidScore = object2D::CreateSquare("solidScore", glm::vec3(0, 0, 0), 30, glm::vec3(0.3764f, 0.0588f, 0.2627f), true);
    AddMeshToList(solidScore);
    Mesh* wiredScore = object2D::CreateSquare("wiredScore", glm::vec3(0, 0, 0), 30, glm::vec3(1, 1, 1), false);
    AddMeshToList(wiredScore);

    // Create the bullet revolver
    Mesh* bulletRevolver = object2D::CreateCircle("bulletRevolver", 20, glm::vec3(1, 0.5803f, 0.2f));
    AddMeshToList(bulletRevolver);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{

    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!

    // Update duck position and its lifetime
    duckX += speedX * deltaTimeSeconds;
    duckY += speedY * deltaTimeSeconds;
    lifetime += deltaTimeSeconds / 2;

    if (duckActive)
    {
        // Reflect from windows edges
        if (duckX < 0 && speedX < 0) speedX *= -1;
        if (duckY < 200 && speedY < 0) speedY *= -1;
        if (duckX > window->GetResolution().x && speedX > 0) speedX *= -1;
        if (duckY > window->GetResolution().y && speedY > 0) speedY *= -1;

        // If the duck is active for 4 seconds, it escapes
        if (lifetime > 4)
            escapeDuck();
    }
    else if (duckY < 0 || duckY > window->GetResolution().y)
    {
        // Duck is shot or escaping and reached the top/bottom edge
        if (lives > 0) spawnDuck();
    }

    // Duck direction angle depends on its speed vector
    float duckAngle = atan2(speedY, speedX);

    // Wing flapping angle depends on the current time
    float wingAngle = 30 * sin(lifetime * 20);

    if (!duckActive && speedY < 0) wingAngle = 30; // Wings are folded when falling

    // Draw the grass
    glm::mat3 grassMatrix = glm::mat3(1);
    grassMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], grassMatrix);

    // Draw the sky
    glm::mat3 skyMatrix = glm::mat3(1);
    skyMatrix *= transform2D::Translate(0, 100);
    skyMatrix *= transform2D::Scale(1, 10);
    RenderMesh2D(meshes["sky"], shaders["VertexColor"], skyMatrix);

    // Draw clouds
    // First cloud
    glm::mat3 cloud1Matrix = glm::mat3(1);
    cloud1Matrix *= transform2D::Translate(400, 670);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud1Matrix);

    glm::mat3 cloud2Matrix = glm::mat3(1);
    cloud2Matrix *= transform2D::Translate(460, 670);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud2Matrix);

    glm::mat3 cloud3Matrix = glm::mat3(1);
    cloud3Matrix *= transform2D::Translate(350, 625);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud3Matrix);

    glm::mat3 cloud4Matrix = glm::mat3(1);
    cloud4Matrix *= transform2D::Translate(425, 625);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud4Matrix);

    glm::mat3 cloud5Matrix = glm::mat3(1);
    cloud5Matrix *= transform2D::Translate(500, 625);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud5Matrix);

    // Second cloud
    glm::mat3 cloud6Matrix = glm::mat3(1);
    cloud6Matrix *= transform2D::Translate(800, 670);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud6Matrix);

    glm::mat3 cloud7Matrix = glm::mat3(1);
    cloud7Matrix *= transform2D::Translate(860, 670);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud7Matrix);

    glm::mat3 cloud8Matrix = glm::mat3(1);
    cloud8Matrix *= transform2D::Translate(750, 625);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud8Matrix);

    glm::mat3 cloud9Matrix = glm::mat3(1);
    cloud9Matrix *= transform2D::Translate(825, 625);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud9Matrix);

    glm::mat3 cloud10Matrix = glm::mat3(1);
    cloud10Matrix *= transform2D::Translate(900, 625);
    RenderMesh2D(meshes["cloud"], shaders["VertexColor"], cloud10Matrix);

    // Draw the body
    glm::mat3 bodyMatrix = glm::mat3(1);
    bodyMatrix *= transform2D::Translate(duckX, duckY);
    bodyMatrix *= transform2D::Rotate(duckAngle);
    RenderMesh2D(meshes["body"], shaders["VertexColor"], bodyMatrix);

    // Draw the left wing
    glm::mat3 wingMatrix = bodyMatrix;
    wingMatrix *= transform2D::Rotate(glm::radians(100 + wingAngle));
    RenderMesh2D(meshes["wing"], shaders["VertexColor"], wingMatrix);

    // Draw the right wing
    wingMatrix = bodyMatrix;
    wingMatrix *= transform2D::Rotate(glm::radians(-100 - wingAngle));
    RenderMesh2D(meshes["wing"], shaders["VertexColor"], wingMatrix);

    // Draw the head
    glm::mat3 headMatrix = bodyMatrix;
    headMatrix *= transform2D::Translate(80, 0);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], headMatrix);

    // Draw the beak
    glm::mat3 beakMatrix = bodyMatrix;
    beakMatrix *= transform2D::Translate(115, 0);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], beakMatrix);

    // Draw the remaining lives
    for (int i = 0; i < lives; i++)
    {
        glm::mat3 lifeMatrix(1);
        lifeMatrix *= transform2D::Translate(30.0f + i * 50, 670);
        RenderMesh2D(meshes["life"], shaders["VertexColor"], lifeMatrix);
    }

    // Exit the game 
    if (lives == 0) 
    {
        // Render text
        cout << "!! You've just lost !!" << endl;
        cout << "Score achieved " << score << endl;
        exit(-1);
    }

    // Draw the remaining bullets
    for (int i = 0; i < bullets; i++)
    {
        glm::mat3 bulletMatrix(1);
        bulletMatrix *= transform2D::Translate(10.0f + i * 50, 570);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], bulletMatrix);
    }

    // Score matrix
    glm::mat3 scoreMatrix(1);
    scoreMatrix *= transform2D::Translate(940, 640);
    scoreMatrix *= transform2D::Scale(10, 1);

    // Draw the current game score
    glm::mat3 solidScoreMatrix = scoreMatrix;
    solidScoreMatrix *= transform2D::Scale(score / 30.0f, 1);
    RenderMesh2D(meshes["solidScore"], shaders["VertexColor"], solidScoreMatrix);

    // Draw the maximum score level
    RenderMesh2D(meshes["wiredScore"], shaders["VertexColor"], scoreMatrix);

    // Draw the bullet revolver
    glm::mat3 bulletRevolverMatrix(1);
    bulletRevolverMatrix *= transform2D::Translate(bulletRevolverX, bulletRevolverY);
    RenderMesh2D(meshes["bulletRevolver"], shaders["VertexColor"], bulletRevolverMatrix);

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    bulletRevolverX = mouseX;

    // Flip the vertical coordinate to use bottom-left origin
    bulletRevolverY = window->GetResolution().y - mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event

    // Spend a bullet
    bullets--;

    if (duckActive && abs(bulletRevolverX - duckX) < 100 && abs(bulletRevolverY - duckY) < 100)
    {
        // If clicked inside the bounding rectangle of the duck, it dies
        shootDuck();
    }
    else if (bullets == 0)
    {
        // When consumed all bullets without hitting, the duck escapes
        escapeDuck();
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::spawnDuck()
{
    // Reload bullets every time a new duck appears
    duckActive = true;
    bullets = 3;

    // Random position at the bottom of the window
    duckX = float(rand() % window->GetResolution().x);
    duckY = 100;

    // Speed boost after each 5 spawned ducks
    float speed = 300 * (1 + (totalDucks / 5) * 0.2f);
    totalDucks++;

    // Random flying direction
    float duckAngle = rand() % 70 + 10.0f; // Random angle in the 10..80 degree range
    if (rand() % 2) duckAngle += 90;       // 10..170 degree range, avoiding too small angles to the axes
    speedX = speed * cos(glm::radians(duckAngle));
    speedY = speed * sin(glm::radians(duckAngle));

    // Reset the lifetime of the duck
    lifetime = 0;
}

void Tema1::shootDuck()
{
    // Increase the score (up to 30 points max)
    score++;
    if (score > 30) score = 30;

    // Start falling
    duckActive = false;
    speedX = 0;
    speedY = -500;
}

void Tema1::escapeDuck()
{
    // Lose a life
    lives--;

    // Start escaping
    duckActive = false;
    speedX = 0;
    speedY = 500;
}