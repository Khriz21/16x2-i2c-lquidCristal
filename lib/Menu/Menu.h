#include <Arduino.h>
#include <MenuItem.h>

#ifndef MENU_H
#define MENU_H
class Menu
{
private:
    const uint8_t MAX_MENU_ITEMS = 10;
    const char* title;

    MenuItem* items[MAX_MENU_ITEMS];
    uint8_t itemCout;
    uint8_t currentIndex;
public:
    // Menu(/* args */);
};

#endif // Menu