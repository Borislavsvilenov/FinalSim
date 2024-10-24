#include "box.hpp"

Box::Box(float x, float y, float w, float h) {
  pos = new Vec2(x, y);
  size = new Vec2(w, h);
}

Box::Box() {
  pos = new Vec2(0, 0);
  size = new Vec2(0, 0);
}

Box::~Box() {
  delete pos;
  delete size;
}

bool Box::checkInbounds(Particle* p) {
  if (p->pos->x > pos->x && p->pos->x <= pos->x + size->x) {
    if (p->pos->y > pos->y && p->pos->y <= pos->y + size->y) {
      return true;
    }
  }
  return false;
}

bool Box::intersects(Box* b) {
  return !(pos->x > b->pos->x + b->size->x || 
      pos->x + size->x < b->pos->x || 
      pos->y > b->pos->y + b->size->y || 
      pos->y + size->y < b->pos->y);
}

void Box::enforceBounds(Particle* p)
{
  if(p->pos->x > size->x - p->radius)
  {
    p->pos->x = size->x - p->radius;
    p->vel->scale(-bounciness);
    p->oldPos->x = p->pos->x - p->vel->x;
  }

  if(p->pos->y > size->y - p->radius)
  {
    p->pos->y = size->y - p->radius; 
    p->vel->scale(-bounciness);
    p->oldPos->y = p->pos->y - p->vel->y;
  }

  if(p->pos->x < pos->x + p->radius)
  {
    p->pos->x = pos->x + p->radius;
    p->vel->scale(-bounciness);
    p->oldPos->x = p->pos->x - p->vel->x;
  }

  if(p->pos->y < pos->y + p->radius)
  {
    p->pos->y = pos->y + p->radius;
    p->vel->scale(-bounciness);
    p->oldPos->y = p->pos->y - p->vel->y;
  }
}

void Box::draw() {
  DrawRectangle(pos->x, pos->y, size->x, size->y, RED);
  DrawRectangle(pos->x + 2, pos->y + 2, size->x - 4, size->y -4, BLACK);
}
