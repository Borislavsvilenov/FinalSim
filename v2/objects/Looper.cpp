#include "Looper.hpp"

Looper::Looper()
{
  qt = new QT(0, 0, 800, 800, true);
  tp = new ThreadPool(std::thread::hardware_concurrency());
  cam = new Cammera();
  bounds = new Box(0, 0, 800, 800);
  aroundP = new Box();
  frame = 0;
  fontSize = 15;

  paused = false;
  spawn = true;
  multithreaded = false;
  showMenu = true;
  
  pColor = GREEN;
  tColor = GREEN;
  mColor = RED;
}

Looper::~Looper()
{ 
  delete qt;
  for (Particle* p : particles)
  {
    delete p;
  }
}

void Looper::update()
{
  cam->draw(bounds);

  if(!paused) {
    qt->clear();
    for (Particle* p : particles) {
      qt->addParticle(p);
    }
    for (Particle* p : particles)
    {
      p->update(new Vec2(0, 0.5f));
      bounds->enforceBounds(p);

      aroundP->pos->x = p->pos->x - (1.5*p->radius);
      aroundP->pos->y = p->pos->y - (1.5*p->radius);
      aroundP->size->x = p->pos->x + (1.5*p->radius);
      aroundP->size->y = p->pos->y + (1.5*p->radius);

      if(multithreaded) {
        qt->fetch(closeP, aroundP, tp, resultMutex, 0);
      } else {
        qt->fetch(closeP, aroundP);
      }

      for (Particle* o : closeP) {
        if (p != o) {
          p->checkCollision(o);
        }
      }

      closeP.clear();

      /* for (Particle* o : particles)
         {
         if (p != o)
         {
         p->checkCollision(o);
         }
         } */
    } 
    if(frame % 5 == 1 && spawn)
    {
      addParticle(new Particle(400, 400, 2, 0, 10, 5, PINK));
    }
    frame++;
  }

  for(Particle* p: particles) {
    cam->draw(p);
  }

  if (paused) {
    pColor = RED;
  } else {
    pColor = GREEN;
  }

  if (multithreaded) {
    mColor = GREEN;
  } else {
    mColor = RED;
  }

  if (showMenu) {
    tColor = GREEN;
  } else {
    tColor = RED;
  }

  DrawFPS(0,0);
  DrawText(TextFormat("Particles: %i", particles.size()), 0, 1*fontSize + 3, fontSize, WHITE);
  DrawText(TextFormat("Pause: SPACE"), 0, 2*fontSize + 3, fontSize, pColor);
  DrawText(TextFormat("Toggle menu: T"), 0, 3*fontSize + 3, fontSize, tColor);
  if (showMenu) {
    DrawText(TextFormat("Multithread: M"), 0, 4*fontSize + 3, fontSize, mColor);
  }

}

void Looper::addParticle(Particle* p)
{
  particles.push_back(p);
  qt->addParticle(p);
}

