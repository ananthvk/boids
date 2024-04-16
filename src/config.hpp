#pragma once
#include <iostream>

class Config
{
  private:
    int screen_width_;
    int screen_height_;
    int FPS_;
    int number_boids_;
    int min_speed_;
    int boid_size_;
    int max_speed_;

    int edge_dist_;

    bool enable_debug_;
    bool enable_separation_;
    bool enable_edge_;

    int boid_sides_; // For triangle
    int debug_vector_length_;
    int debug_vector_thickness_;

    Config()
    {
        screen_width_ = 800;
        screen_height_ = 800;
        FPS_ = 60;
        number_boids_ = 150;
        min_speed_ = 50;
        boid_size_ = 8;
        max_speed_ = 100;
        edge_dist_ = 20;
        title = "Boids - Flock of birds";
        enable_debug_ = true;
        enable_separation_ = true;
        enable_edge_ = true;
        boid_sides_ = 3; // For triangle
        debug_vector_length_ = 20;
        debug_vector_thickness_ = 2;
    }

  public:
    const char *title;

    const int &screen_width = screen_width_;
    const int &screen_height = screen_height_;
    const int &FPS = FPS_;
    const int &number_boids = number_boids_;
    const int &min_speed = min_speed_;
    const int &boid_size = boid_size_;
    const int &max_speed = max_speed_;
    const int &edge_dist = edge_dist_;

    bool &enable_debug = enable_debug_;
    bool &enable_separation = enable_separation_;
    bool &enable_edge = enable_edge_;

    const int &boid_sides = boid_sides_;
    const int &debug_vector_length = debug_vector_length_;
    const int &debug_vector_thickness = debug_vector_thickness_;

    static Config &get()
    {
        static Config config;
        return config;
    }

    static void toggle(bool &b) { b = !b; }

    // Delete copy assignment & copy constructors, also delete move
    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;
    Config(Config &&) = delete;
    Config &operator=(Config &&) = delete;
};