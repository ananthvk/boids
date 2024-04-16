#pragma once
#include "boid.hpp"
#include <vector>

const float vision = 10000;
const float scale_factor = 5.0;
const float friction_max = 30;
const float friction_percent = 0.1;
int steer_factor = 500 * 1000;

class Rules
{
  public:
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

    void edge_rules(std::vector<Boid> &boids, int max_x, int max_y, int buffer)
    {
        for (auto &boid : boids)
        {
            // Make the boid move out of the screen before changing the position
            if (boid.position.x > (max_x + buffer) && boid.velocity.x > 0)
            {
                boid.position.x = -buffer;
            }
            else if (boid.position.x < -buffer && boid.velocity.x < 0)
            {
                boid.position.x = max_x + buffer;
            }

            if (boid.position.y > (max_y + buffer) && boid.velocity.y > 0)
            {
                boid.position.y = -buffer;
            }
            else if (boid.position.y < -buffer && boid.velocity.y < 0)
            {
                boid.position.y = max_y + buffer;
            }
        }
    }

    void separation(std::vector<Boid> &boids)
    {
    }
};