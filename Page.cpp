#include "Page.h"

Page::Page() : Page(-1, -1) { }

Page::Page(int number) : Page(number, -1) { }

Page::Page(int number, int time) {
    this->number = number;
    this->accessTime = time;
    this->secondChance = false;
}