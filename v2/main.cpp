#include "objects/Looper.hpp"

int main()
{
  InitWindow(800, 800, "Sim");
  SetTargetFPS(60);

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

    if(IsKeyPressed(KEY_SPACE))
    {
      sim->paused = !sim->paused;
    }

    if(IsKeyPressed(KEY_B))
    {
      sim->spawn = !sim->spawn;
    }

    if(IsKeyPressed(KEY_M))
    {
      sim->multithreaded = !sim->multithreaded;
    }

    if(IsKeyPressed(KEY_T))
    {
      sim->showMenu = !sim->showMenu;
    }

    if(IsKeyPressed(KEY_Q))
    {
      sim->showQT = !sim->showQT;
    }
  }

  delete sim;
  return 0;
}

