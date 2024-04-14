#pragma once
#include "boid.hpp"
#include <vector>

const float vision = 100;
const float scale_factor = 5.0;
const float friction_max = 30;
const float friction_percent = 0.1;

class Rules
{
  public:
    // Make all given boids move towards the mouse
    void steer_towards_mouse(std::vector<Boid> &boids)
    {
        for (auto &boid : boids)
        {
            steer_towards_mouse(boid);
        }
    }

    // Make this boid move towards the mouse
    void steer_towards_mouse(Boid &boid)
    {
        Vector2 mouse = GetMousePosition();
        mouse.y = GetScreenHeight() - mouse.y;
        auto displacement = Vector2Subtract(mouse, boid.position);
        auto direction = Vector2Normalize(displacement);
        // As the boids move closer to the mouse, reduce the velocity required
        auto length = Vector2Length(displacement);
        // printf("Mag: %f\n", length / acceleration_scale_factor);
        // boid.add_to_new_acceleration(Vector2Scale(direction, length / acceleration_scale_factor));
        boid.velocity = Vector2Add(boid.velocity, Vector2Scale(direction, length / scale_factor));
        // Add friction
        boid.velocity = Vector2Subtract(boid.velocity, Vector2ClampValue(Vector2Scale(boid.velocity, friction_percent), 0, friction_max));
    }

    // Removes all forces acting on this boid
    void clear_forces(Boid &boid) { boid.new_acceleration = {0, 0}; }

    // Removes all forces acting on the given boids
    void clear_forces(std::vector<Boid> &boids)
    {
        for (auto &boid : boids)
        {
            clear_forces(boid);
        }
    }
};