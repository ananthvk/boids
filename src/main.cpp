#include "boid.hpp"
#include "config.hpp"
#include "raylib.h"
#include "rules.hpp"
#include <iostream>
#include <string>
#include <vector>

/// Generates boids with different colors, sizes and max speeds
/// @return vector of boids
std::vector<Boid> get_random_boids()
{
    std::vector<Boid> boids;
    for (int i = 0; i < Config::get().number_boids; i++)
    {
        float x = GetRandomValue(0, Config::get().screen_width);
        float y = GetRandomValue(0, Config::get().screen_height);

        Vector2 direction = {static_cast<float>(GetRandomValue(-1000, 1000)),
                             static_cast<float>(GetRandomValue(-1000, 1000))};
        direction = Vector2Normalize(direction);

        Vector2 velocity = Vector2Scale(
            direction,
            static_cast<float>(
                GetRandomValue(Config::get().min_speed * 10, Config::get().max_speed * 10) / 10.0));

        Color boid_color = {static_cast<unsigned char>(GetRandomValue(0, 200)),
                            static_cast<unsigned char>(GetRandomValue(0, 200)),
                            static_cast<unsigned char>(GetRandomValue(200, 255)), 255};

        int topSpeed = GetRandomValue(Config::get().min_speed, Config::get().max_speed);


        if (i == 0)
        {
            boids.push_back(
                Boid({x, y}, velocity, {255, 0, 0, 255}, Config::get().boid_size * 1.5, topSpeed));
        }
        else
        {

            boids.push_back(Boid({x, y}, velocity, boid_color, Config::get().boid_size, topSpeed));
        }
    }
    return boids;
}

int main(void)
{
    Rules rules;
    InitWindow(Config::get().screen_width, Config::get().screen_height, Config::get().title);
    SetTargetFPS(Config::get().FPS);

    std::vector<Boid> boids = get_random_boids();

    while (!WindowShouldClose())
    {
        // Get key presses
        if (IsKeyPressed(KEY_F2))
            Config::toggle(Config::get().enable_debug);
        if (IsKeyPressed(KEY_S))
            Config::toggle(Config::get().enable_separation);
        if (IsKeyPressed(KEY_E))
            Config::toggle(Config::get().enable_edge);
        if (IsKeyPressed(KEY_R))
            boids = get_random_boids();

        // Update position, velocity, etc
        float dt = GetFrameTime();

        // Apply rules
        if (Config::get().enable_separation)
            rules.separation(boids);
        if (Config::get().enable_edge)
            rules.edge_rules(boids);

        // Update velocity and position of boids after applying forces
        for (auto &boid : boids)
            boid.update(dt);

        // Draw the shapes to the screen
        BeginDrawing();
        ClearBackground(RAYWHITE);
        boids[0].detailed_debug(boids);
        for (const auto &boid : boids)
        {
            boid.draw();
        }
        auto fps = std::to_string(GetFPS());
        DrawText(fps.c_str(), 10, 10, 40, RED);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
