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

    void separation(std::vector<Boid> &boids)
    {
        bool flag = true;
        for (auto &boid : boids)
        {
            Vector2 separation_steer = {0, 0};
            for (const auto &other : boids)
            {
                if (&boid == &other)
                    continue;
                Vector2 displacement = {0, 0};
                float d = 0.0;

                if (boid.is_in_fov(other.position, displacement, d))
                {
                    auto direction = Vector2Negate(Vector2Normalize(displacement));
                    separation_steer =
                        Vector2Add(separation_steer, Vector2Scale(direction, 1.0 / (d)));
                }
            }
            separation_steer = Vector2Scale(separation_steer, 500);
            if (flag)
            {
                printf("%.02f %.02f %.02f\n", separation_steer.x, separation_steer.y,
                       Vector2Length(separation_steer));
            }
            boid.velocity = Vector2Add(boid.velocity, separation_steer);
            flag = false;
        }
    }
};