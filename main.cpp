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
			particles.push_back(new Particle({0, 0}, {1, 1}, {0, 0.1}, 1, 5, RED));
		}
		
		frame++;
		EndDrawing();
	}

	return 0;
}
