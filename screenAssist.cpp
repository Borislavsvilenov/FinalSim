#pragma once
#include <raylib.h>

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
	Vector2 origin2 = calculateScreenPos({simS.x / 2, simS.y / 2}, cam);
	
	DrawRectangleV(origin1, Vector2{10, simS.y}, RED);
	DrawRectangleV(origin1, Vector2{simS.x, 10}, RED);
	DrawRectangleV(origin2, Vector2{-10, -simS.y}, RED);
	DrawRectangleV(origin2, Vector2{-simS.x, -10}, RED);


}
