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
    bool restart = false;
    std::map<std::string, bool> visibleItems;
    void printFloor();
    void printInfo();
    void movePlayer(std::pair<int, int> newpos);

    public:
        Display(std::string playerClass, std::string file, int height, int width, bool generate);
        void print();
        void applyCommand(std::string command);
        bool hasRestarted();
};

#endif
