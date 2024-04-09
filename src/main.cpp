#include "boid.hpp"
#include "raylib.h"
#include <string>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 800;
const int FPS = 60;
const char *title = "Boids - Flock of birds";

int main(void)
{

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(FPS);

    std::vector<Boid> boids;
    boids.push_back(Boid({300, 200}));

    while (!WindowShouldClose())
    {
        // Update position, velocity, etc
        float dt = GetFrameTime();
        for (auto &boid : boids)
            boid.update(dt);
        
        // Draw the shapes to the screen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (const auto &boid : boids)
            boid.draw();
        auto fps = std::to_string(GetFPS());
        DrawText(fps.c_str(), 10, 10, 40, RED);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
