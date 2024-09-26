#pragma once
#include "Vec2.hpp"
#include <raylib.h>

class Particle
{
  public:
    Vec2* pos;
    Vec2* oldPos;
    Vec2* vel;
    Vec2* acc;
    float radius;
    float mass;

    Color color;

    Particle(float x, float y, float vx, float vy, float radius, float mass, Color color);
    ~Particle();

    void update(Vec2* force);
    void draw();

    void applyForce(Vec2* force);

    void handleCollision(Particle* p, Vec2* diff, float d);
    void checkCollision(Particle* p);
};
