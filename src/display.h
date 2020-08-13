#ifndef _DISPLAY_
#define _DISPLAY_

#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <iomanip>

class Game;

class Display {
    std::shared_ptr<Game> game;
    int height;
    int width;
    std::map<std::string, bool> hiddenItems;
    void printFloor();
    void printInfo();

    public:
        Display(std::string playerClass, std::string file, int height, int width, bool generate);
        void print();
        void applyCommand(std::string command);
};

#endif
