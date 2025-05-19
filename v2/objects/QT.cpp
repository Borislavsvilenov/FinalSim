#include "QT.hpp"

QT::QT(float x, float y, float w, float h, bool mt)
{
  box = new Box(x, y, w, h);
  MainTree = mt;
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

void QT::fetch(std::vector<Particle*>& l, Box* area, ThreadPool* pool, std::mutex& resultMutex, int depth) {
  if (!area->intersects(box)) {
    return;
  }

  if (subdivided) {
    if (pool && depth < 1) {  
      std::vector<std::future<void>> futures;

      futures.push_back(pool->enqueue([&] { topLeft->fetch(l, area, pool, resultMutex, depth + 1); }));
      futures.push_back(pool->enqueue([&] { topRight->fetch(l, area, pool, resultMutex, depth + 1); }));
      futures.push_back(pool->enqueue([&] { bottomLeft->fetch(l, area, pool, resultMutex, depth + 1); }));
      futures.push_back(pool->enqueue([&] { bottomRight->fetch(l, area, pool, resultMutex, depth + 1); }));

      for (auto& f : futures) {
        f.get();  
      }
    } else {
      topLeft->fetch(l, area, pool, resultMutex, depth + 1);
      topRight->fetch(l, area, pool, resultMutex, depth + 1);
      bottomLeft->fetch(l, area, pool, resultMutex, depth + 1);
      bottomRight->fetch(l, area, pool, resultMutex, depth + 1);
    }
  } else {
    std::vector<Particle*> localParticles;
    for (Particle* p : particles) {
      if (area->checkInbounds(p)) {
        localParticles.push_back(p);
      }
    }

    std::lock_guard<std::mutex> lock(resultMutex);
    l.insert(l.end(), localParticles.begin(), localParticles.end());
  }
}

void QT::fetch(std::vector<Particle*>& l, Box* area) 
{
  if (area->intersects(box)) {
    if (subdivided) {
      topLeft->fetch(l, area);
      topRight->fetch(l, area);
      bottomLeft->fetch(l, area);
      bottomRight->fetch(l, area);    
    } else {
      for (Particle* p : particles) {
        if(area->checkInbounds(p)) {
          l.push_back(p);
        }
      }
    }
  }
  return;
}


void QT::subdivide()
{
  if (!subdivided) {

    topLeft = new QT(box->pos->x, box->pos->y, box->size->x / 2, box->size->y / 2, false);
    topRight = new QT(box->pos->x + box->size->x / 2, box->pos->y, box->size->x / 2, box->size->y / 2, false);
    bottomLeft = new QT(box->pos->x, box->pos->y + box->size->y / 2, box->size->x / 2, box->size->y / 2, false);
    bottomRight = new QT(box->pos->x + box->size->x / 2, box->pos->y + box->size->y / 2, box->size->x / 2, box->size->y / 2, false);

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
    particles.clear();

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
