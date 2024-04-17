#include "Particle.hpp"

using namespace std;

Particle::Particle(Vector2 p, Vector2 v, Vector2 a, float m, float r, Color c, bool mv)
{
	pos = p;
	posL.x = p.x - v.x;
	posL.y = p.y - v.y;
	acc = a;
	mass = m;
	radius = r;
	color = c;
	movable = mv;
}

Particle::~Particle()
{

}

void Particle::update(float dt)
{
	if(!movable){return;}
	vel.x = pos.x - posL.x;
	vel.y = pos.y - posL.y;

	posL = pos;

	pos.x += vel.x + acc.x * dt * dt;
	pos.y += vel.y + acc.y * dt * dt;

	acc = {0, 0};
}

void Particle::enforceBounds(Vector2 bounds)
{
	if(pos.x > bounds.x/2 - radius)
	{
		pos.x = bounds.x/2 - radius;
		vel.x = -abs(vel.x) * restitution;
		posL.x = pos.x - vel.x;
	}

	if(pos.x < -bounds.x/2 + radius)
	{
		pos.x = -bounds.x/2 + radius;
		vel.x = abs(vel.x) * restitution;
		posL.x = pos.x - vel.x;
	}

	if(pos.y > bounds.y/2 - radius)
	{
		pos.y = bounds.y/2 - radius;
		vel.y = -abs(vel.y) * restitution;
		posL.y = pos.y - vel.y;
	}

	if(pos.y < -bounds.y/2 + radius)
	{
		pos.y = -bounds.y/2 + radius;
		vel.y = abs(vel.y) * restitution;
		posL.y = pos.y - vel.y;
	}
}

void Particle::checkCollision(Particle* other)
{
	Vector2 diff = {other->pos.x - pos.x, other->pos.y - pos.y};
  float dist = sqrt(diff.x * diff.x + diff.y * diff.y);

	if (dist < std::numeric_limits<float>::epsilon()) {
    return;
	}

	if(dist < radius + other->radius)
	{
		performCollision(other, diff, dist);
	}

	atraction(other, diff, dist);
}

void Particle::performCollision(Particle* other, Vector2 diff, float dist)
{
	float overlap = (radius + other->radius) - dist;
  Vector2 normal = {diff.x / dist, diff.y / dist};

	if(!movable)
	{
		other->pos.x += normal.x * overlap;
		other->pos.y += normal.y * overlap;

		return;
	}

	if(!other->movable)
	{
		pos.x -= normal.x * overlap;
		pos.y -= normal.y * overlap;

		return;
	}
	pos.x -= normal.x * overlap / 2;
	pos.y -= normal.y * overlap / 2;

	other->pos.x += normal.x * overlap / 2;
	other->pos.y += normal.y * overlap / 2;
}

void Particle::atraction(Particle* other, Vector2 diff, float dist)
{
	Vector2 normal = {diff.x / dist, diff.y / dist};

	acc.x += G * other->mass * normal.x / dist;
	acc.y += G * other->mass * normal.y / dist;

	other->acc.x -= G * mass * normal.x / dist;
	other->acc.y -= G * mass * normal.y / dist;
}

void Particle::applyGravity()
{
	acc.y = 0.1;
}

void Particle::draw(Vector2 cam)
{
	DrawCircleV(calculateScreenPos(pos, cam), radius, color);
}
