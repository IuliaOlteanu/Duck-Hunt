#pragma once
#include "components/simple_scene.h"
#include "components/text_renderer.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void spawnDuck();
        void shootDuck();
        void escapeDuck();
        void drawText(char* text, float x, float y, float z);

    protected:
        // TODO(student): If you need any other class variables, define them here.
        bool duckActive;      // Duck state
        float duckX, duckY;   // Duck position
        float speedX, speedY; // Duck speed
        float lifetime;       // Duck time since spawning
        int lives;            // Number of remaining lives
        int bullets;          // Number of remaining bullets
        int score;            // Current game score
        int totalDucks;       // Total number of spawned ducks
        float bulletRevolverX, bulletRevolverY;  // Bullet revolver position

    };
}   // namespace m1
