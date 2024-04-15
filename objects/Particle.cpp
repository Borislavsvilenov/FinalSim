#include "Particle.hpp"

using namespace std;

Particle::Particle(Vector2 p, Vector2 v, Vector2 a, float m, float r, Color c)
{
	pos = p;
	posL.x = p.x - v.x;
	posL.y = p.y - v.y;
	acc = a;
	mass = m;
	radius = r;
	color = c;
}

Particle::~Particle()
{

}

void Particle::update(float dt)
{
	vel.x = pos.x - posL.x;
	vel.y = pos.y - posL.y;

	posL = pos;

	pos.x += vel.x + acc.x * dt * dt;
	pos.y += vel.y + acc.y * dt * dt;
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
}

void Particle::performCollision(Particle* other, Vector2 diff, float dist)
{
	float overlap = (radius + other->radius) - dist;
  Vector2 normal = {diff.x / dist, diff.y / dist};

	pos.x -= normal.x * overlap / 2;
	pos.y -= normal.y * overlap / 2;

	other->pos.x += normal.x * overlap / 2;
	other->pos.y += normal.y * overlap / 2;
}

void Particle::draw(Vector2 cam)
{
	DrawCircleV(calculateScreenPos(pos, cam), radius, color);
}
