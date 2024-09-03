#include "objects/Looper.hpp"

int main()
{
  InitWindow(800, 800, "Sim");
  SetTargetFPS(120);

  Looper* sim = new Looper();

  sim->addParticle(Particle(400, 400, 2, 0, 20, WHITE));

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);
    
    sim->update();
    
    EndDrawing();
  }

  return 0;
}

