#pragma once
#include <raylib.h>
#include <iostream>
#include <list>
#include <vector>

#include "Particle.hpp"
#include "../screenAssist.hpp"

class QuadTree
{
	public:
		Vector2 pos;
		Vector2 bounds;
		int maxParticles;

		QuadTree* topLeft = nullptr;
		QuadTree* topRight = nullptr;
		QuadTree* bottomLeft = nullptr;
		QuadTree* bottomRight = nullptr;
		bool divided = false;

		std::list<Particle*> particles;

		QuadTree(Vector2 pos, Vector2 bounds, int maxParticles);
		~QuadTree();

		void subdivide();
		void insert(Particle* particle);
    void remove(Particle* particle);
    void checkOutOfBounds(std::vector<Particle*> *OutOfBounds);
		std::vector<Particle*> search(Vector2 pos, Vector2 bounds, std::vector<Particle*> results);
		void clear();
		void draw(Vector2 cam);
};
