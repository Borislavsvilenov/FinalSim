#pragma once

class Vec2
{

public:
  float x;
  float y;

  Vec2(float x, float y);
  ~Vec2();
  
  Vec2 add(Vec2 other);
  Vec2 sub(Vec2 other);

  Vec2 scale(float s);

  float dot(Vec2 other);
  float mag();

  Vec2 normalize();
};
