#include "objects/Looper.hpp"

int main()
{
  InitWindow(800, 800, "Sim");
  SetTargetFPS(120);

  Looper sim;

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);
    
    sim.update();
    
    EndDrawing();
  }

  return 0;
}

