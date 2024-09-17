#include "Cammera.hpp"

Cammera::Cammera () {
  pos = new Vec2(0, 0);
}

Cammera::~Cammera () {
  delete pos;
}

void Cammera::mvCam (Vec2* vel) {
  pos->add(vel);
}

void Cammera::drawParticle (Particle* p) {
  DrawCircle(p->pos->x - pos->x, p->pos->y - pos->y, p->mass, p->color);
}
