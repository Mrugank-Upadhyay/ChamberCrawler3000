#ifndef _ENEMY_
#define _ENEMY_

#include "character.h"
#include <memory>


class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;
class Cell;

class Enemy : public Character {
    static bool isStopped;
    bool isHostile;
    bool giveGold;
    int gold;
    
    // Add pointer back to cell
    Cell * cell = nullptr;

    protected:
        int randomGold();
        void transferGold(Player * player);


    public:
        Enemy(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position, bool hostile, int gold, bool giveGold);

        static void setStopped(bool stopped);
        void setHostile(bool hostile);
        void setGold(int value);
        void setCell(Cell * cell);
        static bool getStopped();
        bool getHostile();
        int getGold();
        Cell * getCell();

        virtual std::pair<int, int> move();

        virtual void attack(std::shared_ptr<Player> player) = 0;

        // How is gold going to be transferred? Will we need to differentiate if its a human, merchant or Drag?
        virtual void getStruckBy(Shade * shade);
        virtual void getStruckBy(Drow * drow);
        virtual void getStruckBy(Vampire * vampire);
        virtual void getStruckBy(Troll * troll);
        virtual void getStruckBy(Goblin * goblin);

        // Keep purely virtual? or make simply virtual and implement a blank
        //TODO: possibly dd move in here
        void nextTurn() override;

        virtual std::string info() override;
};

#endif
