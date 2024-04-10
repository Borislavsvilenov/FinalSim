#include "Particle.hpp"

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
	vel += acc * dt;
	pos += vel * dt;
}

void Particle::draw(Vector2 cam)
{
	
}
