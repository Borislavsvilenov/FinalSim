#include <raylib.h>
#include <iostream>
#include <vector>

#include "screenAssist.hpp"
#include "objects/Particle.hpp"

using namespace std;

int main()
{
	int frame = 0;
	int substeps = 1;

	InitWindow(800, 800, "sim");
	SetTargetFPS(120);

	Vector2 simS = Vector2 {400, 400};
	Vector2 Camera = Vector2 {0, 0};

	vector<Particle*> particles;

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
			p->draw(Camera);
		}

		if(frame % 10 == 0)
		{
			particles.push_back(new Particle({0, 0}, {2, 0}, {0, 0.1}, 3, 5, RED));
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
