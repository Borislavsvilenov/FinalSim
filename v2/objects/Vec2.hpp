#pragma once

class Vec2
{

public:
  float x;
  float y;

  Vec2(float x, float y);
  Vec2();
  ~Vec2();
  
  void copy(Vec2* other);

  void add(Vec2* other);
  void sub(Vec2* other);

  void scale(float s);

  float dot(Vec2* other);
  float mag();

  void normalize();
};
