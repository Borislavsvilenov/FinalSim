#pragma once
#include <vector>

#include "MenuLable.hpp"

class Menu {
  public:
    std::vector<MenuLable*> perms;
    std::vector<MenuLable*> toggles;

    int fontSize;
    int margin;
    bool toggled = true;

    Menu(std::vector<char*> p, std::vector<char*> t, int fs, int m);
    ~Menu();

    void draw();
};
