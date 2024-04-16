#include <raylib.h>
#include <iostream>
#include <vector>

#include "screenAssist.hpp"
#include "objects/Particle.hpp"

using namespace std;

int main()
{
	int frame = 0;
	int substeps = 3;

	InitWindow(800, 800, "sim");
	SetTargetFPS(60);

	Vector2 simS = Vector2 {1000, 1000};
	Vector2 Camera = Vector2 {0, 0};

	vector<Particle*> particles;

	particles.push_back(new Particle({0, 0}, {0, 0}, {0, 0}, 30, 20, YELLOW, false));

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		drawBounds(simS, Camera);

		for(Particle* p : particles)
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
			p->draw(Camera);
		}

		if(frame % 100 == 0)
		{
			particles.push_back(new Particle({0, 900}, {1, 0}, {0, -0.1}, 0.01, 5, WHITE, true));
		}
		
		frame++;
		EndDrawing();

		if(IsKeyDown(KEY_R))
		{
			particles.clear();
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
