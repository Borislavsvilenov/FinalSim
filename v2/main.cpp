#include "objects/Looper.hpp"

int main()
{
  InitWindow(800, 800, "Sim");
  SetTargetFPS(120);

  Looper* sim = new Looper();

  sim->addParticle(new Particle(400, 400, 2, 0, 5, 5, WHITE));
  sim->addParticle(new Particle(600, 200, 2, 0, 5, 5, WHITE));
  sim->addParticle(new Particle(200, 600, 2, 0, 5, 5, WHITE));
  sim->addParticle(new Particle(200, 200, 2, 0, 5, 5, WHITE));
  sim->addParticle(new Particle(600, 600, 2, 0, 5, 5, WHITE));

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

