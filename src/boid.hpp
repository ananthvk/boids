#pragma once
#include "config.hpp"
#include "raylib.h"
#include "raymath.h"
#include <string>

class Boid
{
  private:
    Vector2 position;
    Vector2 velocity;
    Color color;
    float size;
    float rotation;
    int topSpeed;
    float vision_radius;

    // Draw a vector (for debugging purpose)
    void draw_vector(Vector2 v, Color c) const
    {
        Vector2 pos = position;
        pos.y = GetScreenHeight() - pos.y;
        v.y = -v.y;
        DrawLineEx(pos, Vector2Add(pos, Vector2Scale(v, Config::get().debug_vector_length)),
                   Config::get().debug_vector_thickness, c);
    }

  public:
    Boid(Vector2 initial_position, Vector2 initial_velocity = {0, 0},
         Color color = {0, 0, 255, 255}, float size = 15, int topSpeed = 100,
         float max_acceleration = 75)
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
        draw_vector(velocity_direction, GREEN);
    }

    friend class Rules;
};