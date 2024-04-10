#include "Particle.hpp"

using namespace std;

Particle::Particle(Vector2 p, Vector2 v, Vector2 a, float m, float r, Color c)
{
	pos = p;
	vel = v;
	acc = a;
	mass = m;
	radius = r;
	color = c;
}

void Particle::update(float dt)
{
	vel.x += acc.x * dt;
	vel.y += acc.y * dt;
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;
}

void Particle::draw(Vector2 cam)
{
	DrawCircleV(calculateScreenPos(pos, cam), radius, color);
}
