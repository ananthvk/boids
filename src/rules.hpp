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
                // printf("%.02f %.02f %.02f\n", separation_steer.x, separation_steer.y,
                //        Vector2Length(separation_steer));
            }
            boid.velocity = Vector2Add(boid.velocity, separation_steer);
            flag = false;
        }
    }

    // A bit inefficient
    void cohesion(std::vector<Boid> &boids)
    {
        bool flag = true;
        for (auto &boid : boids)
        {
            Vector2 cohesion_steer = {0, 0};
            Vector2 centroid = {0, 0};
            int n = 0;
            for (const auto &other : boids)
            {
                if (&boid == &other)
                    continue;
                Vector2 displacement = {0, 0};
                float d = 0.0;

                if (boid.is_in_fov(other.position, displacement, d))
                {
                    centroid = Vector2Add(centroid, other.position);
                    n++;
                }
            }
            if (n != 0)
            {
                centroid = Vector2Scale(centroid, 1.0 / n);
                cohesion_steer = Vector2Normalize(Vector2Subtract(centroid, boid.position));
                cohesion_steer = Vector2Scale(cohesion_steer, 2.0);
                if (flag)
                {
                    // printf("%.02f %.02f %.02f\n", cohesion_steer.x, cohesion_steer.y,
                    //        Vector2Length(cohesion_steer));
                }
                boid.velocity = Vector2Add(boid.velocity, cohesion_steer);
            }
            flag = false;
        }
    }

    void alignment(std::vector<Boid> &boids)
    {
        bool flag = true;
        for (auto &boid : boids)
        {
            Vector2 alignment_steer = {0, 0};
            Vector2 velocity = {0, 0};
            int n = 0;
            for (const auto &other : boids)
            {
                if (&boid == &other)
                    continue;
                Vector2 displacement = {0, 0};
                float d = 0.0;

                if (boid.is_in_fov(other.position, displacement, d))
                {
                    velocity = Vector2Add(velocity, other.velocity);
                    n++;
                }
            }
            if (n != 0)
            {
                velocity = Vector2Scale(velocity, 1.0 / n);
                alignment_steer = Vector2Subtract(velocity, boid.velocity);
                alignment_steer = Vector2Scale(alignment_steer, 0.1);
                if (flag)
                {
                    //printf("%.02f %.02f %.02f %.02f %0.2f\n", alignment_steer.x, alignment_steer.y,
                    //       Vector2Length(alignment_steer), boid.velocity.x, boid.velocity.y);
                }
                boid.velocity = Vector2Add(boid.velocity, alignment_steer);
            }
            flag = false;
        }
    }

    void check_if_velocity_less_than_min_speed(std::vector<Boid> &boids)
    {
        for (auto &boid : boids)
        {
            if (Vector2Length(boid.velocity) <= Config::get().min_speed)
            {
                boid.velocity =
                    Vector2Scale(Vector2Normalize(boid.velocity), Config::get().min_speed);
            }
        }
    }
};