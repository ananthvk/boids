#include "boid.hpp"
#include "raylib.h"
#include "rules.hpp"
#include <string>
#include <vector>

// Some constants such as title, screen dimensions, etc
const int screen_width = 800;
const int screen_height = 800;
const int FPS = 60;
const int number_boids = 100;
const int min_speed = 950;
const int boid_size = 8;
const int max_speed = 1250;
const float max_acceleration = 200;
const int edge_dist = 20;
const char *title = "Boids - Flock of birds";

/// Generates boids with different colors, sizes and max speeds
/// @return vector of boids
std::vector<Boid> get_random_boids()
{
    std::vector<Boid> boids;
    for (int i = 0; i < number_boids; i++)
    {
        float x = GetRandomValue(0, screen_width);
        float y = GetRandomValue(0, screen_height);

        float xvel = GetRandomValue(-50, 50);
        float yvel = GetRandomValue(-50, 50);

        float xacc = GetRandomValue(-5, 5);
        float yacc = GetRandomValue(-5, 5);

        Color boid_color = {static_cast<unsigned char>(GetRandomValue(0, 255)),
                            static_cast<unsigned char>(GetRandomValue(0, 255)),
                            static_cast<unsigned char>(GetRandomValue(0, 255)), 255};

        int topSpeed = GetRandomValue(min_speed, max_speed);

        int maxAcceleration = GetRandomValue(max_acceleration / 2, max_acceleration);

        boids.push_back(
            Boid({x, y}, {xvel, yvel}, {xacc, yacc}, boid_color, 8, topSpeed, max_acceleration));
    }
    return boids;
}

int main(void)
{
    Rules rules;
    InitWindow(screen_width, screen_height, title);
    SetTargetFPS(FPS);

    std::vector<Boid> boids = get_random_boids();

    while (!WindowShouldClose())
    {
        // Update position, velocity, etc
        float dt = GetFrameTime();

        // Apply rules
        rules.clear_forces(boids);
        rules.edge_rules(boids, screen_width, screen_height, edge_dist);

        // Update velocity and position of boids after applying forces
        for (auto &boid : boids)
            boid.update(dt);

        // Draw the shapes to the screen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (const auto &boid : boids)
        {
            boid.draw();
            boid.debug();
        }
        auto fps = std::to_string(GetFPS());
        DrawText(fps.c_str(), 10, 10, 40, RED);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
