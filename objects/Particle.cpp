#include "Particle.hpp"

using namespace std;

Particle::Particle(Vector2 p, Vector2 v, Vector2 a, Vector2 f, float m, float r, Color c)
{
	pos = p;
	vel = v;
	acc = a;
	force = f;
	mass = m;
	radius = r;
	color = c;
}

Particle::~Particle()
{

}

void Particle::update(float dt)
{
	acc.x = force.x / mass;
	acc.y = force.y / mass;

	vel.x += acc.x * dt;
	vel.y += acc.y * dt;
	
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;
}

void Particle::enforceBounds(Vector2 bounds)
{
	if(pos.x > bounds.x/2 - 10)
	{
		vel.x = -abs(vel.x);
		pos.x = bounds.x/2 - 10;
	}

	if(pos.x < -bounds.x/2 + 10)
	{
		vel.x = abs(vel.x);
		pos.x = -bounds.x/2 + 10;
	}

	if(pos.y > bounds.y/2 - 10)
	{
		vel.y = -abs(vel.y);
		pos.y = bounds.y/2 - 10;
	}

	if(pos.y < -bounds.y/2 + 10)
	{
		vel.y = abs(vel.y);
		pos.y = -bounds.y/2 + 10;
	}
}

void Particle::checkCollision(Particle* other)
{
	Vector2 diff = {pos.x - other->pos.x, pos.y - other->pos.y};
	float dist = sqrt(diff.x * diff.x + diff.y * diff.y);
	if(dist < radius + other->radius)
	{
		performCollision(other, diff, dist);
	}
}

void Particle::performCollision(Particle* other, Vector2 diff, float dist)
{
	float overlap = (radius + other->radius - dist) / 2;
	Vector2 normal = {diff.x / dist, diff.y / dist};
	Vector2 relVel = {vel.x - other->vel.x, vel.y - other->vel.y};

	float velDot = relVel.x / normal.x + relVel.y / normal.y;

	float totMass = mass + other->mass;

	pos.x += normal.x * overlap;
	pos.y += normal.y * overlap;

	other->pos.x -= normal.x * overlap;
	other->pos.y -= normal.y * overlap;

	vel.x -= normal.x * velDot * (totMass - other->mass) / totMass;
	vel.y -= normal.y * velDot * (totMass - other->mass) / totMass;

	other->vel.x += normal.x * velDot * (totMass - mass) / totMass;
	other->vel.y += normal.y * velDot * (totMass - mass) / totMass;
}

void Particle::draw(Vector2 cam)
{
	DrawCircleV(calculateScreenPos(pos, cam), radius, color);
}
