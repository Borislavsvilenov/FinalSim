#pragma once
#include <raylib.h>

class Particle
{
public:
	Vector2 pos;
	Vector2 vel;
	Vector2 acc;
	float mass;
	float radius;
	Color color;

	Particle(Vector2 p, Vector2 v, Vector2 a, float m, float r, Color c);
	void update(float dt);
	void draw(Vector2 cam);
};
