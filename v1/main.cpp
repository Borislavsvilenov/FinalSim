#include <raylib.h>
#include <iostream>
#include <vector>

#include "screenAssist.hpp"
#include "objects/Particle.hpp"
#include "objects/QuadTree.hpp"

using namespace std;

void insert(Particle* p, QuadTree* QT, vector<Particle*> *particles)
{
  QT->insert(p);
  particles->push_back(p);
}

int main()
{
	int frame = 0;
	int substeps = 3;

	bool paused = false;
	bool spawn = false;

	InitWindow(900, 900, "sim");
	SetTargetFPS(60);

	Vector2 simS = {2000, 2000};
	Vector2 Camera = {0, 0};

	vector<Particle*> particles = {};
  vector<Particle*> OutOfBounds = {};
	
	QuadTree* QT = new QuadTree({-simS.x / 2, -simS.y / 2}, simS, 4);

  insert(new Particle({0, 0}, {0, 0}, {0, 0}, 3, 20, YELLOW, false), QT, &particles);
	
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		drawBounds(simS, Camera);
    //QT->draw(Camera);
		
		for(Particle* p : particles)
		{
			if(!paused)
			{
				for(int step = 0; step < substeps; step++)
				{
          //vector<Particle*> others = QT->search({p->pos.x - 10, p->pos.y - 10}, {20, 20}, {});
					for(Particle* o : particles)
					{
						if(p != o)
						{
							p->checkCollision(o);
						}
					}
				}
				p->enforceBounds(simS);
				p->update(1);
				//p->applyGravity();
			}
			p->draw(Camera);
		}

		if(!paused)
		{
			if(frame % 10 == 0)
			{
				if(spawn)
				{
          insert(new Particle({0, 400}, {1, 0}, {0, -0.1}, 0.01, 5, WHITE, true), QT, &particles);
				}
			}
		  frame++;

      QT->checkOutOfBounds(&OutOfBounds);
      for(Particle* p : OutOfBounds)
      {
        QT->remove(p);
        QT->insert(p);
      }
      OutOfBounds.clear();
		}
    
    DrawFPS(0,0);
    DrawText(TextFormat("Particles: %i", particles.size()), 0, 20, 20, WHITE);

		EndDrawing();

		if(IsKeyDown(KEY_R))
		{
			QT->clear();
		}

		if(IsKeyPressed(KEY_ENTER))
		{
			spawn = !spawn;
		}

		if(IsKeyPressed(KEY_SPACE))
		{
			paused = !paused;
		}

		if(IsKeyDown(KEY_S))
		{
			Camera.y += 5;
		}

		if(IsKeyDown(KEY_W))
		{
			Camera.y -= 5;
		}

		if(IsKeyDown(KEY_A))
		{
			Camera.x -= 5;
		}	

		if(IsKeyDown(KEY_D))
		{
			Camera.x += 5;
		}
	}

	return 0;
}
