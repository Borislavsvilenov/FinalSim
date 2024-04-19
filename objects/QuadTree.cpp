#include "QuadTree.hpp"

using namespace std;

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
	if(!divided && particles.size() > maxParticles)
	{
		topLeft = new QuadTree(pos, {bounds.x / 2, bounds.y / 2}, maxParticles);
		topRight = new QuadTree({pos.x + bounds.x / 2, pos.y}, {bounds.x / 2, bounds.y / 2}, maxParticles);
		bottomLeft = new QuadTree({pos.x, pos.y + bounds.y / 2}, {bounds.x / 2, bounds.y / 2}, maxParticles);
		bottomRight = new QuadTree({pos.x + bounds.x / 2, pos.y + bounds.y / 2}, {bounds.x / 2, bounds.y / 2}, maxParticles);
		divided = true;
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
				if(isInBounds(particle->pos, topLeft->pos, topLeft->bounds))
				{
					topLeft->insert(p);
				}
				else if(isInBounds(particle->pos, topRight->pos, topRight->bounds))
				{
					topRight->insert(p);
				}
				else if(isInBounds(particle->pos, bottomLeft->pos, bottomLeft->bounds))
				{
					bottomLeft->insert(p);
				}
				else if(isInBounds(particle->pos, bottomRight->pos, bottomRight->bounds))
				{
					bottomRight->insert(p);
				}
			}
			particles.clear();
		}
	}	
	else
	{
		if(isInBounds(particle->pos, topLeft->pos, topLeft->bounds))
		{
			topLeft->insert(particle);
		}
		else if(isInBounds(particle->pos, topRight->pos, topRight->bounds))
		{
			topRight->insert(particle);
		}
		else if(isInBounds(particle->pos, bottomLeft->pos, bottomLeft->bounds))
		{
			bottomLeft->insert(particle);
		}
		else if(isInBounds(particle->pos, bottomRight->pos, bottomRight->bounds))
		{
			bottomRight->insert(particle);
		}
	}
}

vector<Particle*> QuadTree::search(Vector2 pos, Vector2 bounds, vector<Particle*> results)
{
	if(!intersects(pos, bounds, this->pos, this->bounds))
	{
		return results;
	}

	if(!divided)
	{
		for(Particle* p : particles)
		{
			if(isInBounds(p->pos, pos, bounds))
			{
				results.push_back(p);
			}
		}
	}
	else
	{
		results = topLeft->search(pos, bounds, results);
		results = topRight->search(pos, bounds, results);
		results = bottomLeft->search(pos, bounds, results);
		results = bottomRight->search(pos, bounds, results);
	}
	
	return results;
}

void QuadTree::clear()
{
	if(divided)
	{
		topLeft->clear();
		delete topLeft;
		topRight->clear();
		delete topRight;
		bottomLeft->clear();
		delete bottomLeft;
		bottomRight->clear();
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
