#pragma once
#include <raylib.h>
#include <iostream>
#include <cmath>

#include "../screenAssist.hpp"

class Particle
{
public:
	float restitution = 0.5;
	float G = 0.1;
	float I = 0.00000001;
	Vector2 pos;
	Vector2 posL;
	Vector2 vel;
	Vector2 acc;
	float mass;
	float radius;
	Color color;

	bool movable;
  bool inBounds;

	Particle(Vector2 p, Vector2 v, Vector2 a, float m, float r, Color c, bool mv);
	~Particle();

	void update(float dt);
	void enforceBounds(Vector2 bounds);
	void checkCollision(Particle* other);
	void performCollision(Particle* other, Vector2 diff, float dist);
	void atraction(Particle* other, Vector2 diff, float dist);
	void applyGravity();
	void draw(Vector2 cam);
};
