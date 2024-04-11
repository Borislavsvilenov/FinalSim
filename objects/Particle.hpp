#pragma once
#include <raylib.h>
#include <iostream>
#include <cmath>

#include "../screenAssist.hpp"

class Particle
{
public:
	Vector2 pos;
	Vector2 vel;
	Vector2 acc;
	Vector2 force;
	float mass;
	float radius;
	Color color;

	Particle(Vector2 p, Vector2 v, Vector2 a, Vector2 f, float m, float r, Color c);
	~Particle();

	void update(float dt);
	void enforceBounds(Vector2 bounds);
	void checkCollision(Particle* other);
	void performCollision(Particle* other, Vector2 diff, float dist);
	void draw(Vector2 cam);
};
