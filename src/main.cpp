#include "boid.hpp"
#include "raylib.h"
#include "rules.hpp"
#include <string>
#include <vector>

// Some constants such as title, screen dimensions, etc
const int screen_width = 800;
const int screen_height = 800;
const int FPS = 60;
const int number_boids = 200;
const int min_speed = 950;
const int boid_size = 8;
const int max_speed = 1250;
const float max_acceleration = 600;
const int edge_dist = 20;
const char *title = "Boids - Flock of birds";

bool enable_debug = true;
bool enable_separation = true;
bool enable_edge = true;

/// Generates boids with different colors, sizes and max speeds
/// @return vector of boids
std::vector<Boid> get_random_boids()
{
    std::vector<Boid> boids;
    for (int i = 0; i < number_boids; i++)
    {
        float x = GetRandomValue(0, screen_width);
        float y = GetRandomValue(0, screen_height);

        Vector2 direction = {static_cast<float>(GetRandomValue(-1000, 1000)),
                             static_cast<float>(GetRandomValue(-1000, 1000))};
        direction = Vector2Normalize(direction);

        Vector2 velocity =
            Vector2Scale(direction, static_cast<float>(GetRandomValue(100, 1000)) / 10.0);

        Color boid_color = {static_cast<unsigned char>(GetRandomValue(0, 200)),
                            static_cast<unsigned char>(GetRandomValue(0, 200)),
                            static_cast<unsigned char>(GetRandomValue(200, 255)), 255};

        int topSpeed = GetRandomValue(min_speed, max_speed);

        int maxAcceleration = GetRandomValue(max_acceleration / 2, max_acceleration);

        if (i == 0)
        {
            boids.push_back(Boid({x, y}, velocity, {0, 0}, {255, 0, 0, 255}, boid_size * 1.5,
                                 topSpeed, max_acceleration));
        }
        else
        {

            boids.push_back(
                Boid({x, y}, velocity, {0, 0}, boid_color, boid_size, topSpeed, max_acceleration));
        }
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
        // Get key presses
        if (IsKeyPressed(KEY_F2))
            enable_debug = !enable_debug;
        if (IsKeyPressed(KEY_S))
            enable_separation = !enable_separation;
        if (IsKeyPressed(KEY_E))
            enable_edge = !enable_edge;
        if (IsKeyPressed(KEY_R))
            boids = get_random_boids();

        // Update position, velocity, etc
        float dt = GetFrameTime();

        // Apply rules
        rules.clear_forces(boids);
        if (enable_separation)
            rules.separation(boids);
        if (enable_edge)
            rules.edge_rules(boids, screen_width, screen_height, edge_dist);

        // Update velocity and position of boids after applying forces
        for (auto &boid : boids)
            boid.update(dt);

        // Draw the shapes to the screen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        boids[0].debug();
        for (const auto &boid : boids)
        {
            boid.draw();
            if (enable_debug)
                boid.debug();
        }
        auto fps = std::to_string(GetFPS());
        DrawText(fps.c_str(), 10, 10, 40, RED);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
