#pragma once
#include <raylib.h>

#include "Vec2.hpp"

class MenuLable {
  public:
    char* lable;
    Color color;
    int value;
    int fontSize;
    Vec2* pos;

    MenuLable(char* l, int v, int fs, Color c, Vec2* p);
    ~MenuLable();

    void draw();
};
