#include <raylib.h>
#include <iostream>
#include <vector>

#include "screenAssist.hpp"
#include "objects/Particle.hpp"

using namespace std;

int main()
{
	InitWindow(800, 800, "sim");
	SetTargetFPS(60);

	Vector2 simS = Vector2 {400, 400};
	Vector2 Camera = Vector2 {0, 0};

	vector<Particle*> particles;

	particles.push_back(new Particle({0, 0}, {1, 1}, {0, 0}, {0, 0}, 2, 5, RED));
	particles.push_back(new Particle({100, 100}, {0, 0}, {0, 0}, {0, 0}, 2, 5, GREEN));
	particles.push_back(new Particle({-100, -100}, {0, 0}, {0, 0}, {0, 0}, 1, 5, BLUE));

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		drawBounds(simS, Camera);

		for(Particle* p : particles)
		{
			for(Particle* o : particles)
			{
				if(p != o)
				{
					p->checkCollision(o);
				}
			}
			p->enforceBounds(simS);
			p->update(1);
			p->draw(Camera);
		}

		EndDrawing();
	}

	return 0;
}
