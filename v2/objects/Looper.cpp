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
  showQT = false;
  
  pColor = GREEN;
  tColor = GREEN;
  mColor = RED;
  sColor = GREEN;
  qColor = RED;
}

Looper::~Looper()
{ 
  delete qt;
  for (Particle* p : particles)
  {
    delete p;
  }
}

void Looper::updateParticle(Particle* p) 
{
  p->update(new Vec2(0, 0.5f), dt);
  bounds->enforceBounds(p);
  
  Box* aroundP = new Box();
  std::vector<Particle*> closeP;

  aroundP->pos->x = p->pos->x - (1.5*p->radius);
  aroundP->pos->y = p->pos->y - (1.5*p->radius);
  aroundP->size->x = p->pos->x + (1.5*p->radius);
  aroundP->size->y = p->pos->y + (1.5*p->radius);
  
  qt->fetch(closeP, aroundP);

  /*
     if(multithreaded) {
     qt->fetch(closeP, aroundP, tp, resultMutex, 0);
     } else {
     qt->fetch(closeP, aroundP);
     } 
     */

  for (Particle* o : closeP) {
    if (p != o) {
      p->checkCollision(o, multithreaded);
    }
  }

  /*
     if (multithreaded) {
     for (Particle* o: closeP) {
     if (p != o) {
     tp->enqueue([p, o, this] { p->checkCollision(o, this->resultMutex); });
     }
     }
     } else {
     for (Particle* o: closeP) {
     if (p != o) {
     p->checkCollision(o, multithreaded);
     }
     }
     }
     */

  closeP.clear();
  delete(aroundP);
}

void Looper::update()
{
  cam->draw(bounds);
  if(showQT)
  {
    qt->draw(cam);
  }

  if(!paused) {
    qt->clear();

    for (Particle* p : particles) {
      qt->addParticle(p);
    }

    for (Particle* p : particles) {
      if (multithreaded) {
        futures.push_back(tp->enqueue([p, this] {updateParticle(p); }));
      } else {
        updateParticle(p);
      }
    }

    for (auto& f : futures) {
      f.get();
    }

    futures.clear();

    if(frame % 5 == 1 && spawn)
    {
      addParticle(new Particle(200, 200, 2*dt, 0, 5, 5, WHITE));
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

  if (spawn) {
    sColor = GREEN;
  } else {
    sColor = RED;
  }

  if (showQT) {
    qColor = GREEN;
  } else {
    qColor = RED;
  }

  DrawFPS(0,0);
  DrawText(TextFormat("Particles: %i", particles.size()), 0, 1*fontSize + 3, fontSize, WHITE);
  DrawText(TextFormat("Pause: SPACE"), 0, 2*fontSize + 3, fontSize, pColor);
  DrawText(TextFormat("Toggle menu: T"), 0, 3*fontSize + 3, fontSize, tColor);
  if (showMenu) {
    DrawText(TextFormat("Multithread: M"), 0, 4*fontSize + 3, fontSize, mColor);
    DrawText(TextFormat("Show QT: Q"), 0, 5*fontSize + 3, fontSize, qColor);
    DrawText(TextFormat("Spawn: B"), 0, 6*fontSize + 3, fontSize, sColor);
    DrawText(TextFormat("Move: W-A-S-D"), 0, 7*fontSize + 3, fontSize, WHITE);
  }

}

void Looper::addParticle(Particle* p)
{
  particles.push_back(p);
  qt->addParticle(p);
}
