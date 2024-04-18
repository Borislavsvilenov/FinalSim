#include <raylib.h>
#include <iostream>
#include <vector>

#include "screenAssist.hpp"
#include "objects/Particle.hpp"
#include "objects/QuadTree.hpp"

using namespace std;

int main()
{
	int frame = 0;
	int substeps = 3;

	bool paused = false;
	bool spawn = false;

	InitWindow(1000, 1000, "sim");
	SetTargetFPS(120);

	Vector2 simS = Vector2 {2000, 2000};
	Vector2 Camera = Vector2 {0, 0};

	vector<Particle*> particles;

	particles.push_back(new Particle({0, 0}, {0, 0}, {0, 0}, 3, 20, YELLOW, false));

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		drawBounds(simS, Camera);

		for(Particle* p : particles)
		{
			if(!paused)
			{
				for(int step = 0; step < substeps; step++)
				{
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
					particles.push_back(new Particle({0, 400}, {1, 0}, {0, -0.1}, 0.01, 5, WHITE, true));
				}
			}
		frame++;
		}


		EndDrawing();

		if(IsKeyDown(KEY_R))
		{
			particles.clear();
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
