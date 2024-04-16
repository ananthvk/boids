#pragma once

class Config
{
  private:
    Config() {}

  public:

    static Config &get()
    {
        static Config config;
        return config;
    }

    // Delete copy assignment & copy constructors, also delete move
    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;
    Config(Config &&) = delete;
    Config &operator=(Config &&) = delete;
};