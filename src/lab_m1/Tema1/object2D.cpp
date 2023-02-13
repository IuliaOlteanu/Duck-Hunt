#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {
        0, 1, 2, 3
    };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float heigth,
    glm::vec3 color,
    bool fill) {

    Mesh* rectangle = new Mesh(name);

    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, heigth, 0), color),
        VertexFormat(corner + glm::vec3(0, heigth, 0), color)


    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2, 3
    };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }
    rectangle->InitFromData(vertices, indices);

    return rectangle;
}

Mesh* object2D::CreateTriangle(
    const std::string& name,
    glm::vec3 v0,
    glm::vec3 v1,
    glm::vec3 v2,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(v0, color),
        VertexFormat(v1, color),
        VertexFormat(v2, color)
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2
    };

    Mesh* triangle = new Mesh(name);
    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* object2D::CreateCircle(
    const std::string& name,
    float radius,
    glm::vec3 color)
{
    // Number of circle sectors
    const int n = 60;

    // Create vertices on the circle
    std::vector<VertexFormat> vertices;
    for (int i = 0; i < n; i++)
    {
        float angle = glm::radians(i * 360.0f / n);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    // Add a vertex for the circle center
    vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), color));

    // Create indices for sector triangles
    std::vector<unsigned int> indices;
    for (int i = 0; i < n; i++)
    {
        indices.push_back(i);           // Index of the current vertex on the circle
        indices.push_back((i + 1) % n); // Index of the next vertex on the circle
        indices.push_back(n);           // Index of the center vertex
    }

    Mesh* circle = new Mesh(name);
    circle->InitFromData(vertices, indices);
    return circle;
}