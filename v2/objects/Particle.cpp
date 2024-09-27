#include "Particle.hpp"

Particle::Particle(float x, float y, float vx, float vy, float radius, float mass, Color color)
{
  pos = new Vec2(x, y);
  oldPos = new Vec2(x, y);
  vel = new Vec2(vx, vy);
  acc = new Vec2(0, 0);
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
  
  Vec2* vcp1 = new Vec2();
  Vec2* vcp2 = new Vec2();

  vcp1->copy(vel);
  vcp2->copy(p->vel);

  vcp1->sub(vcp2);

  float velNorm = vcp1->dot(diff);
  float totalMass = mass + p->mass;

  pos->sub(diff);
  p->pos->add(diff); 

  Vec2* d1 = new Vec2();
  Vec2* d2 = new Vec2();

  d1->copy(diff);
  d2->copy(diff);

  d1->scale(velNorm * p->mass / totalMass);
  d2->scale(velNorm * mass / totalMass);

  vel->sub(d1);
  p->vel->sub(d2);

  delete vcp1;
  delete vcp2;
  delete d1;
  delete d2;

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










