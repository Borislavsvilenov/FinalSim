#include <raylib.h>
#include "objects/Particle.hpp"
#include "screenAssist.cpp"

int main()
{
	InitWindow(800, 800, "sim");
	SetTargetFPS(60);

	Vector2 simS = Vector2 {400, 400};

	Vector2 Camera = Vector2 {0, 0};

	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		drawBounds(simS, Camera);

		EndDrawing();
	}

	return 0;
}
