#include "MenuLable.hpp"

MenuLable::MenuLable (char* l, int v, int fs, Color c, Vec2* p) {
  lable = l;
  value = v;
  fontSize = fs;
  color = c;
  pos = p;
}

MenuLable::~MenuLable () {
  delete pos;
  delete lable;
}

void MenuLable::draw () {
  DrawText(TextFormat(lable, value), pos->x, pos->y, fontSize, color);
}
