#include "objects/Looper.hpp"

int main()
{
  InitWindow(800, 800, "Sim");
  SetTargetFPS(120);

  Looper* sim = new Looper();

  sim->addParticle(new Particle(-100, -100, 2, 0, 5, WHITE));
  sim->addParticle(new Particle(100, 100, 2, 0, 5, WHITE));
  sim->addParticle(new Particle(-100, 200, 2, 0, 5, WHITE));
  sim->addParticle(new Particle(100, -100, 2, 0, 5, WHITE));
  sim->addParticle(new Particle(0, 0, 2, 0, 5, WHITE));


  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);
    
    sim->update();
    
    EndDrawing();
  }
  
  delete sim;
  return 0;
}

