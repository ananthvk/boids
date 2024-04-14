#include "boid.hpp"
#include "raylib.h"
#include "rules.hpp"
#include <string>
#include <vector>

// Some constants such as title, screen dimensions, etc
const int screenWidth = 800;
const int screenHeight = 800;
const int FPS = 60;
const int numberBoids = 1;
const int minSpeed = 950;
const int maxSpeed = 1250;
const float max_acceleration = 200;
const char *title = "Boids - Flock of birds";

/// Generates boids with different colors, sizes and max speeds
/// @return vector of boids
std::vector<Boid> get_random_boids()
{
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

        int topSpeed = GetRandomValue(minSpeed, maxSpeed);

        boids.push_back(Boid({x, y}, {xvel, yvel}, {0.0, 0.0}, {r, g, b, 255}, 8, topSpeed, max_acceleration));
    }
    return boids;
}

int main(void)
{
    Rules rules;
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(FPS);

    std::vector<Boid> boids = get_random_boids();

    while (!WindowShouldClose())
    {
        // Update position, velocity, etc
        float dt = GetFrameTime();

        // Apply rules
        rules.clear_forces(boids);
        rules.steer_towards_mouse(boids);

        // Update velocity and position of boids after applying forces
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
