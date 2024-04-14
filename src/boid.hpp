#pragma once

#include "raylib.h"
#include "raymath.h"
#include <string>

const int BOID_SIDES = 3; // For triangle

class Boid
{
  private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Color color;
    float size;
    float rotation;
    int topSpeed;
    Vector2 new_acceleration;
    float max_acceleration;

  public:
    Boid(Vector2 initial_position, Vector2 initial_velocity = {0, 0},
         Vector2 initial_acceleration = {0, 0}, Color color = {0, 0, 255, 255}, float size = 15,
         int topSpeed = 100, float max_acceleration = 75)
        : position(initial_position), velocity(initial_velocity),
          acceleration(initial_acceleration), color(color), size(size), rotation(0),
          topSpeed(topSpeed), new_acceleration({0, 0}), max_acceleration(max_acceleration)
    {
    }

    // Updates position and velocity using verlet integration
    // dt is time elapsed (in seconds)
    // https://en.wikipedia.org/wiki/Verlet_integration
    void update(float dt)
    {
        // Calmp new acceleration
        new_acceleration = Vector2ClampValue(new_acceleration, 0, max_acceleration);

        auto comp1 = Vector2Add(position, Vector2Scale(velocity, dt));
        auto comp2 = Vector2Scale(acceleration, (dt * dt * 0.5));
        Vector2 new_position = Vector2Add(comp1, comp2);

        // Vector2 new_acceleration = rules();

        comp1 = Vector2Scale(Vector2Add(acceleration, new_acceleration), (dt * 0.5));
        Vector2 new_velocity = Vector2Add(velocity, comp1);

        position = new_position;
        velocity = new_velocity;
        acceleration = new_acceleration;

        // Clamp the velocity of the boid
        velocity = Vector2ClampValue(velocity, 0, topSpeed);

        // Update rotation to point in the direction of the velocity vector
        // Find the angle between shape and x axis
        rotation = (180 / PI) * Vector2Angle(velocity, {1, 0});
    }

    // Call this method before calling update
    void set_new_acceleration(Vector2 new_acceleration)
    {
        this->new_acceleration = new_acceleration;
    }

    // Call this method before calling update
    void add_to_new_acceleration(Vector2 acceleration)
    {
        this->new_acceleration = Vector2Add(new_acceleration, acceleration);
    }

    void draw() const
    {
        Vector2 pos = position;
        pos.y = GetScreenHeight() - pos.y;
        DrawPoly(pos, BOID_SIDES, size, rotation, color);
    }

    friend class Rules;
};