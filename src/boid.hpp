#pragma once
#include "config.hpp"
#include "raylib.h"
#include "raymath.h"
#include <string>
#include <vector>

class Boid
{
  public:
    Vector2 position;
    Vector2 velocity;
    Color color;
    float size;
    float rotation;
    int topSpeed;

    // Draw a vector (for debugging purpose)
    void draw_vector(Vector2 v, Color c, bool scale_unit) const
    {
        Vector2 pos = position;
        pos.y = GetScreenHeight() - pos.y;
        v.y = -v.y;
        if (scale_unit)
            DrawLineEx(pos, Vector2Add(pos, Vector2Scale(v, Config::get().debug_vector_length)),
                       Config::get().debug_vector_thickness, c);
        else
            DrawLineEx(pos, Vector2Add(pos, v), Config::get().debug_vector_thickness, c);
    }

    Boid(Vector2 initial_position, Vector2 initial_velocity = {0, 0},
         Color color = {0, 0, 255, 255}, float size = 15, int topSpeed = 100)
        : position(initial_position), velocity(initial_velocity), color(color), size(size),
          rotation(0), topSpeed(topSpeed)

    {
    }

    // Update position with just velocity and time elapsed
    void update(float dt)
    {
        // Clamp the velocity of the boid
        velocity = Vector2ClampValue(velocity, 0, topSpeed);

        position = Vector2Add(position, Vector2Scale(velocity, dt));

        // Update rotation to point in the direction of the velocity vector
        // Find the angle between shape and x axis
        rotation = (180 / PI) * Vector2Angle(velocity, {1, 0});
    }

    void draw() const
    {
        Vector2 pos = position;
        pos.y = GetScreenHeight() - pos.y;
        DrawPoly(pos, Config::get().boid_sides, size, rotation, color);

        if (Config::get().enable_debug)
            debug();
    }

    void debug() const
    {
        Vector2 velocity_direction = Vector2Normalize(velocity);
        draw_vector(velocity_direction, GREEN, true);
    }

    void detailed_debug(const std::vector<Boid> &boids) const
    {
        Vector2 pos = position;
        pos.y = GetScreenHeight() - pos.y;

        debug();
        DrawCircle(pos.x, pos.y, Config::get().fov_radius, {128, 128, 128, 10});

        for (const auto &boid : boids)
        {
            if (&boid != this)
            {
                auto displacement = Vector2Subtract(boid.position, position);
                if (Vector2LengthSqr(displacement) <=
                    (Config::get().fov_radius * Config::get().fov_radius))
                    draw_vector(displacement, YELLOW, false);
            }
        }
    }

    // Checks if the point is within the field of view of the boid
    // Also sets displacement to the vector pointing towards the point, and length_sqr square of
    // distance between the points
    bool is_in_fov(Vector2 pos, Vector2 &displacement, float &length_sqr)
    {
        displacement = Vector2Subtract(pos, position);
        length_sqr = Vector2LengthSqr(displacement);
        if (length_sqr <= (Config::get().fov_radius * Config::get().fov_radius))
        {
            // Also check FOV
            float dot = Vector2Angle(velocity, displacement);
            if (dot > 0.5)
                return true;
        }
        return false;
    }

    friend class Rules;
};