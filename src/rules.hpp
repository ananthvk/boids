#pragma once
#include "boid.hpp"
#include <vector>

const float vision = 50;

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

    void cohesion(std::vector<Boid> &boids)
    {
        for (int i = 0; i < boids.size(); i++)
        {
            Vector2 centroid = {0, 0};
            Vector2 sepCentroid = {0, 0};
            int sepN = 0;
            Vector2 commonVelocity = {0, 0};
            int n = 0;


            for (int j = 0; j < boids.size(); j++)
            {
                if (i == j)
                    continue;

                float dist = Vector2DistanceSqr(boids[i].position, boids[j].position);
                if (dist < vision)
                {
                    if (dist < (boids[i].size * boids[i].size + 50))
                    {
                        continue;
                    }
                    n++;
                    sepN++;
                    centroid = Vector2Add(centroid, boids[j].position);
                    sepCentroid = Vector2Add(sepCentroid, boids[j].position);
                    commonVelocity = Vector2Add(commonVelocity, boids[j].velocity);
                }
            }

            if (n == 0)
                continue;

            centroid = Vector2Scale(centroid, 1.0 / n);
            commonVelocity = Vector2Scale(commonVelocity, 1.0 / n);

            Vector2 cohesiveForce = Vector2Subtract(centroid, boids[i].position);
            Vector2 alignmentForce = Vector2Subtract(commonVelocity, boids[i].velocity);
            if (sepN != 0)
            {
                sepCentroid = Vector2Scale(sepCentroid, 1.0 / sepN);
                Vector2 separationForce = Vector2Subtract(boids[i].position, sepCentroid);
                boids[i].add_to_new_acceleration(Vector2Scale(separationForce, 300));
            }

            boids[i].add_to_new_acceleration(Vector2Scale(cohesiveForce, 1800));
            boids[i].add_to_new_acceleration(Vector2Scale(alignmentForce, 600));
        }
    }

    void edges(std::vector<Boid> &boids)
    {
        for (auto &boid : boids)
        {
            Vector2 pos = boid.position;
            float xFactor = ((1.0 / 6.0) * GetScreenWidth());
            float xS = pos.x / xFactor;
            float v = GetRandomValue(100, 200);
            float vSecond = GetRandomValue(-50, 50);

            if (pos.x < xFactor)
            {
                boid.add_to_new_acceleration({v, vSecond});
            }
            if (pos.x > 5 * xFactor)
            {
                boid.add_to_new_acceleration({-v, vSecond});
            }

            float yFactor = (((1.0 / 6.0) * GetScreenHeight()));
            float xY = pos.y / xFactor;

            if (pos.y < yFactor)
            {
                // Boid is near top of the screen
                boid.add_to_new_acceleration({vSecond, v});
            }
            if (pos.y > 5 * yFactor)
            {
                boid.add_to_new_acceleration({vSecond, -v});
            }
        }
    }
};