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
  delete pos;
  delete oldPos;
  delete vel;
  delete acc;
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
  DrawCircle(pos->x+100, pos->y+100, mass, RED);
}

void Particle::applyForce(Vec2* force)
{
  force->scale(1 / mass);
  acc->add(force);
}

