#include "Cammera.hpp"

Cammera::Cammera () {
  pos = new Vec2(0, 0);
}

Cammera::~Cammera() {
  delete pos;
}

void Cammera::mvCam(Vec2* vel) {
  pos->add(vel);
}

void Cammera::draw(Particle* p) {
  DrawCircle(p->pos->x - pos->x, p->pos->y - pos->y, p->radius, p->color);
}

void Cammera::draw(Box* b) {
  DrawRectangle(b->pos->x - 2 - pos->x, b->pos->y - 2 - pos->y, b->size->x + 4, b->size->y + 4, RED);
  DrawRectangle(b->pos->x - pos->x, b->pos->y - pos->y, b->size->x, b->size->y, BLACK);
}
