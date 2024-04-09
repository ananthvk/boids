#pragma once
#include "boid.hpp"
#include <vector>

class Rules
{
  public:
    void steer_towards_mouse(std::vector<Boid> &boids)
    {
        for (auto &boid : boids)
        {
            steer_towards_mouse(boid);
        }
    }

    void steer_towards_mouse(Boid &boid)
    {
        Vector2 mouse = GetMousePosition();
        mouse.y = GetScreenHeight() - mouse.y;
        auto displacement = Vector2Subtract(mouse, boid.position);
        boid.add_to_new_acceleration(Vector2Scale(displacement, 10));
    }

    void clear_forces(Boid &boid) { boid.new_acceleration = {0, 0}; }

    void clear_forces(std::vector<Boid> &boids)
    {
        for (auto &boid : boids)
        {
            clear_forces(boid);
        }
    }
};