#include "box.hpp"

Box::Box(float x, float y, float w, float h) {
  pos = new Vec2(x, y);
  size = new Vec2(w, h);
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

void Box::enforceBounds(Particle* p)
{
  if(!this->checkInbounds(p)) 
  {
    if(p->pos->x > size->x)
    {
      p->pos->x = size->x;
      p->vel->x = -abs(p->vel->x);
    }
    
    if(p->pos->y > size->y)
    {
      p->pos->y = size->y;
      p->vel->y = -abs(p->vel->y);
    }

    if(p->pos->x < pos->x)
    {
      p->pos->x = pos->x;
      p->vel->x = abs(p->vel->x);
    }
    
    if(p->pos->y < pos->y)
    {
      p->pos->y = pos->y;
      p->vel->y = abs(p->vel->y);
    }
  }
}

void Box::draw() {
  DrawRectangle(pos->x, pos->y, size->x, size->y, RED);
}
