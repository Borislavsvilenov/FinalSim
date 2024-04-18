#include "screenAssist.hpp"

Vector2 calculateScreenPos(Vector2 pos, Vector2 cam)
{
	int mx = GetScreenWidth() / 2;
	int my = GetScreenHeight() / 2;

	Vector2 screenPos = {mx + pos.x - cam.x, my + pos.y - cam.y};

	return screenPos;
}

void drawBounds(Vector2 simS, Vector2 cam)
{
	Vector2 origin1 = calculateScreenPos({-simS.x / 2, -simS.y / 2}, cam);
	
	DrawRectangleLines(origin1.x, origin1.y, simS.x, simS.y, RED);
}

bool isInBounds(Vector2 pos, Vector2 bounds)
{
	return (pos.x > bounds.x / 2 && pos.x < -bounds.x / 2 && pos.y > bounds.y / 2 && pos.y < -bounds.y / 2);
}

bool intersects(Vector2 posA, Vector2 sizeA, Vector2 posB, Vector2 sizeB)
{
	return (posA.x < posB.x + sizeB.x && posA.x + sizeA.x > posB.x && posA.y < posB.y + sizeB.y && posA.y + sizeA.y > posB.y);
}
