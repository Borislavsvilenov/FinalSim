#include "QT.hpp"
#include <iostream>

QT::QT(float x, float y, float w, float h)
{
  box = new Box(x, y, w, h);
}

QT::~QT()
{
  delete box;
  
  if (subdivided) {
    delete topLeft;
    delete topRight;
    delete bottomLeft;
    delete bottomRight;
  }
}

void QT::fetch(std::vector<Particle*>& l, Box* area)
{
  return;
}

void QT::subdivide()
{
  if (!subdivided) {

    topLeft = new QT(box->pos->x, box->pos->y, box->size->x / 2, box->size->y / 2);
    topRight = new QT(box->pos->x + box->size->x / 2, box->pos->y, box->size->x / 2, box->size->y / 2);
    bottomLeft = new QT(box->pos->x, box->pos->y + box->size->y / 2, box->size->x / 2, box->size->y / 2);
    bottomRight = new QT(box->pos->x + box->size->x / 2, box->pos->y + box->size->y / 2, box->size->x / 2, box->size->y / 2);

    for (Particle* p : particles) {
      if (topLeft->box->checkInbounds(p)) {
        topLeft->addParticle(p);
      }
      else if (topRight->box->checkInbounds(p)) {
        topRight->addParticle(p);
      }
      else if (bottomLeft->box->checkInbounds(p)) {
        bottomLeft->addParticle(p);
      }
      else if (bottomRight->box->checkInbounds(p)) {
        bottomRight->addParticle(p);
      }
    }

    subdivided = true;

  }
}

void QT::addParticle(Particle* p)
{ 
  if (box->checkInbounds(p)) {
  particles.push_back(p);

    if (!subdivided) {
      if (particles.size() >= size) {
        this->subdivide();
      }
    } else {
      topLeft->addParticle(p);
      topRight->addParticle(p);
      bottomLeft->addParticle(p);
      bottomRight->addParticle(p);
    }
  }
}

void QT::clear()
{
  particles.clear();
  if(subdivided) {
    topLeft->clear();
    topRight->clear();
    bottomLeft->clear();
    bottomRight->clear();
  }
}

void QT::draw(Cammera* cam)
{
  cam->draw(box);
  if(subdivided) {
    topLeft->draw(cam);
    topRight->draw(cam);
    bottomLeft->draw(cam);
    bottomRight->draw(cam);
  }
}
