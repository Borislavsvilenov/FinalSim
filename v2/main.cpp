#include "objects/Looper.hpp"

int main()
{
  InitWindow(800, 800, "Sim");
  SetTargetFPS(120);

  Looper* sim = new Looper();


  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);
    
    sim->update();
    
    EndDrawing();
  
    if(IsKeyDown(KEY_S))
		{
			sim->cam->pos->y += 5;
		}

		if(IsKeyDown(KEY_W))
		{
			sim->cam->pos->y -= 5;
		}

		if(IsKeyDown(KEY_A))
		{
			sim->cam->pos->x -= 5;
		}	

		if(IsKeyDown(KEY_D))
		{
			sim->cam->pos->x += 5;
		}  
  }
  
  delete sim;
  return 0;
}

