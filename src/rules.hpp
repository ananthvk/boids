#pragma once
#include "boid.hpp"
#include "config.hpp"
#include <vector>

class Rules
{
  public:
    void edge_rules(std::vector<Boid> &boids)
    {
        int max_x = Config::get().screen_width;
        int max_y = Config::get().screen_height;
        int buffer = Config::get().edge_dist;
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

    void separation(std::vector<Boid> &boids) {}
};