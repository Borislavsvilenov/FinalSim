#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2(float x, float y)
{
  this->x = x;
  this->y = y;
}

Vec2::Vec2()
{
  this->x = 0;
  this->y = 0;
}

Vec2::~Vec2()
{

}

void Vec2::copy(Vec2* other)
{
  this->x = other->x;
  this->y = other->y;
}

void Vec2::add(Vec2* other)
{ 
  this->x += other->x;
  this->y += other->y;
}

void Vec2::sub(Vec2* other)
{
  this->x -= other->x;
  this->y -= other->y;
}

void Vec2::scale(float s)
{
  this->x *= s;
  this->y *= s;
}

float Vec2::dot(Vec2* other)
{
  return this->x * other->x + this->y * other->y;
}

float Vec2::mag()
{
  return sqrt(this->x * this->x + this->y * this->y);
}

void Vec2::normalize()
{
  float mag = this->mag();

  this->x /= mag;
  this->y /= mag;
}
