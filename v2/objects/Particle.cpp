#include "Particle.hpp"

Particle::Particle(float x, float y, float vx, float vy, float mass, Color color) : pos(x, y), oldPos(0, 0), vel(vx, vy), acc(0, 0), mass(mass), color(color)
{
}

Particle::~Particle()
{
}

void Particle::update(Vec2 force)
{
  oldPos = pos;
  vel = vel.add(acc.scale(mass));
  pos = pos.add(vel);
  
  acc = Vec2(0, 0);
  vel = oldPos.sub(pos);

  applyForce(force);
}

void Particle::draw()
{
  DrawCircle(pos.x, pos.y, mass, color);
}

void Particle::applyForce(Vec2 force)
{
  acc = acc.add(force.scale(1 / mass));
}

