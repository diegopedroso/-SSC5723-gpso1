#include "Page.h"

Page::Page(int number) {
    this->number = number;
    this->secondChance = false;
}

Page::Page() {
    this->number = -1;
    this->secondChance = false;
}
