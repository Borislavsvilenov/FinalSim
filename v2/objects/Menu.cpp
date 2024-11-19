#include "Menu.hpp"

Menu::Menu(std::vector<char*> p, std::vector<char*> t, int fs, int m) {
  fontSize = fs;
  margin = m;

  int i = 0;
  for (char* l : p) {
    perms.push_back(new MenuLable(l, 0, fs, WHITE, new Vec2(m, fs*i)));
    i++;
  }

  for (char* l : t) {
    toggles.push_back(new MenuLable(l, 0, fs, WHITE, new Vec2(m, fs*i)));
    i++;
  }
}

Menu::~Menu() {

}

void Menu::draw () {

}
