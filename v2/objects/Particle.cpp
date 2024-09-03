#include "Particle.hpp"
#include <iostream>

Particle::Particle(float x, float y, float vx, float vy, float mass, Color color)
{
  pos = new Vec2(x, y);
  oldPos = new Vec2(x, y);
  vel = new Vec2(vx, vy);
  acc = new Vec2(0, 0);
  this->mass = mass;
  this->color = color;
}

Particle::~Particle()
{

}

void Particle::update(Vec2* force)
{
  oldPos->copy(pos);
  vel->add(acc);
  pos->add(vel);
  
  acc->x = 0;
  acc->y = 0;

  vel->x = pos->x - oldPos->x;
  vel->y = pos->y - oldPos->y;

  applyForce(force);
}

void Particle::draw()
{
  DrawCircle(pos->x, pos->y, mass, color);
}

void Particle::applyForce(Vec2* force)
{
  force->scale(1 / mass);
  acc->add(force);
}

