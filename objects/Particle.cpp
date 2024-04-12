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

Particle::~Particle()
{

}

void Particle::update(float dt)
{
	vel.x += acc.x * dt;
	vel.y += acc.y * dt;

	pos.x += vel.x * dt;
	pos.y += vel.y * dt;
}

void Particle::enforceBounds(Vector2 bounds)
{
	if(pos.x > bounds.x/2 - radius)
	{
		vel.x = -abs(vel.x) * restitution;
		pos.x = bounds.x/2 - radius;
	}

	if(pos.x < -bounds.x/2 + radius)
	{
		vel.x = abs(vel.x) * restitution;
		pos.x = -bounds.x/2 + radius;
	}

	if(pos.y > bounds.y/2 - radius)
	{
		vel.y = -abs(vel.y) * restitution;
		pos.y = bounds.y/2 - radius;
	}

	if(pos.y < -bounds.y/2 + radius)
	{
		vel.y = abs(vel.y) * restitution;
		pos.y = -bounds.y/2 + radius;
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

  Vector2 relVel = {other->vel.x - vel.x, other->vel.y - vel.y};
  float velAlongNormal = relVel.x * normal.x + relVel.y * normal.y;

  if (velAlongNormal > 0) {
    return;
  }

  float j = -(1 + restitution) * velAlongNormal;
  j /= (1 / mass + 1 / other->mass);

  vel.x -= j / mass * normal.x;
  vel.y -= j / mass * normal.y;

  other->vel.x += j / other->mass * normal.x;
  other->vel.y += j / other->mass * normal.y;
}

void Particle::draw(Vector2 cam)
{
	DrawCircleV(calculateScreenPos(pos, cam), radius, color);
}
