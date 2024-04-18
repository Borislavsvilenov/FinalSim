#include "QuadTree.hpp"

QuadTree::QuadTree(Vector2 pos, Vector2 bounds, int maxParticles)
{
	this->pos = pos;
	this->bounds = bounds;
	this->maxParticles = maxParticles;
}

QuadTree::~QuadTree()
{
	if(divided)
	{
		delete topLeft;
		delete topRight;
		delete bottomLeft;
		delete bottomRight;
		divided = false;
	}
}

void QuadTree::subdivide()
{
	if(!divided)
	{
		if(particles.size() > maxParticles)
		{
			topLeft = new QuadTree(pos, {bounds.x / 2, bounds.y / 2}, maxParticles);
			topRight = new QuadTree({pos.x + bounds.x / 2, pos.y}, {bounds.x / 2, bounds.y / 2}, maxParticles);
			bottomLeft = new QuadTree({pos.x, pos.y + bounds.y / 2}, {bounds.x / 2, bounds.y / 2}, maxParticles);
			bottomRight = new QuadTree({pos.x + bounds.x / 2, pos.y + bounds.y / 2}, {bounds.x / 2, bounds.y / 2}, maxParticles);
			divided = true;
		}
	}
}

void QuadTree::insert(Particle* particle)
{
	if(!divided)
	{
		particles.push_back(particle);
		if(particles.size() > maxParticles)
		{
			subdivide();
			for(Particle* p : particles)
			{
				if(isInBounds(particle->pos, topLeft->bounds))
				{
					topLeft->insert(p);
				}
				if(isInBounds(particle->pos, topRight->bounds))
				{
					topRight->insert(p);
				}
				if(isInBounds(particle->pos, bottomLeft->bounds))
				{
					bottomLeft->insert(p);
				}
				if(isInBounds(particle->pos, bottomRight->bounds))
				{
					bottomRight->insert(p);
				}
			}
			particles.clear();
		}
	}	
	else
	{
		if(isInBounds(particle->pos, topLeft->bounds))
		{
			topLeft->insert(particle);
		}
		if(isInBounds(particle->pos, topRight->bounds))
		{
			topRight->insert(particle);
		}
		if(isInBounds(particle->pos, bottomLeft->bounds))
		{
			bottomLeft->insert(particle);
		}
		if(isInBounds(particle->pos, bottomRight->bounds))
		{
			bottomRight->insert(particle);
		}
	}
}

void QuadTree::clear()
{
	if(divided)
	{
		topLeft->clear();
		topRight->clear();
		bottomLeft->clear();
		bottomRight->clear();
		delete topLeft;
		delete topRight;
		delete bottomLeft;
		delete bottomRight;
		divided = false;
	}
	else
	{
		particles.clear();
	}
}

void QuadTree::draw(Vector2 cam)
{
	if(divided)
	{
		topLeft->draw(cam);
		topRight->draw(cam);
		bottomLeft->draw(cam);
		bottomRight->draw(cam);
	}
	else
	{
		Vector2 origin1 = calculateScreenPos(pos, cam);
		DrawRectangleLines(origin1.x, origin1.y, bounds.x, bounds.y, GREEN);
	}
}
