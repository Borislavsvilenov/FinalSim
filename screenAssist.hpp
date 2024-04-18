#pragma once
#include <raylib.h>

void drawBounds(Vector2 simS, Vector2 cam);

Vector2 calculateScreenPos(Vector2 pos, Vector2 cam);

bool isInBounds(Vector2 pos, Vector2 bounds);

