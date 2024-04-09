#include "boid.hpp"
#include "raylib.h"
#include <string>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 800;
const int FPS = 60;
const int numberBoids = 30;
const char *title = "Boids - Flock of birds";

int main(void)
{

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(FPS);

    std::vector<Boid> boids;
    for (int i = 0; i < numberBoids; i++)
    {
        float x = GetRandomValue(0, screenWidth);
        float y = GetRandomValue(0, screenHeight);

        float xvel = GetRandomValue(-50, 50);
        float yvel = GetRandomValue(-50, 50);

        unsigned char r = GetRandomValue(0, 255);
        unsigned char g = GetRandomValue(0, 255);
        unsigned char b = GetRandomValue(0, 255);
        
        int topSpeed = GetRandomValue(500, 800);

        boids.push_back(Boid({x, y}, {xvel, yvel}, {0.0, 0.0}, {r, g, b, 255}, 15, topSpeed));
    }

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
