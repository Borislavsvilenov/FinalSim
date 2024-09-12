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

std::list<Particle*> QT::fetch()
{
  return particles;
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
      if (topRight->box->checkInbounds(p)) {
        topRight->addParticle(p);
      }
      if (bottomLeft->box->checkInbounds(p)) {
        bottomLeft->addParticle(p);
      }
      if (bottomRight->box->checkInbounds(p)) {
        bottomRight->addParticle(p);
      }
    }

    subdivided = true;

  }
}

void QT::addParticle(Particle* p)
{ 
  if (!subdivided) {
    particles.push_back(p);
    if (particles.size() >= size) {
      this->subdivide();
    }
  } else {
    if (topLeft->box->checkInbounds(p)) {
      topLeft->addParticle(p);
    }
    if (topRight->box->checkInbounds(p)) {
      topRight->addParticle(p);
    }
    if (bottomLeft->box->checkInbounds(p)) {
      bottomLeft->addParticle(p);
    }
    if (bottomRight->box->checkInbounds(p)) {
      bottomRight->addParticle(p);
    }
  }
}

void QT::draw()
{
  box->draw();
}