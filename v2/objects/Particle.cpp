#include "Particle.hpp"

Particle::Particle(float x, float y, float vx, float vy, float radius, float mass, Color color)
{
  pos = new Vec2(x, y);
  oldPos = new Vec2(x - vx, y - vy);
  vel = new Vec2();
  acc = new Vec2();
  this->radius = radius;
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
  vel->x = pos->x - oldPos->x;
  vel->y = pos->y - oldPos->y;
  
  applyForce(force);
  
  oldPos->copy(pos);
  
  vel->add(acc);
  pos->add(vel);
  
  acc->x = 0;
  acc->y = 0;

}

void Particle::draw()
{
  DrawCircle(pos->x+100, pos->y+100, radius, RED);
}

void Particle::applyForce(Vec2* force)
{
  force->scale(1 / mass);
  acc->add(force);
}

void Particle::handleCollision(Particle* p, Vec2* diff, float d)
{
  float overlap = (radius + p->radius) - d;
  diff->scale(1/d);
  diff->scale(overlap / 2);

  pos->sub(diff);
  p->pos->add(diff); 
}

void Particle::checkCollision(Particle* p)
{
  Vec2* diff = new Vec2(0, 0);
  diff->copy(p->pos);
  diff->sub(pos);

  float d = diff->mag();

  if(d <= radius + p->radius){
    handleCollision(p, diff, d);
  }
}










