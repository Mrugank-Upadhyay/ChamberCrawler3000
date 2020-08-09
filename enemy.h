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
    bool isHostile;
    bool giveGold;
    int gold;

    // Add pointer back to cell
    std::shared_ptr<Cell>  cell;

    protected:
        int randomGold();
        void transferGold(Player * player);


    public:
        Enemy(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position, bool hostile, int gold, bool giveGold);

        void setHostile(bool hostile);
        void setGold(int value);
        void setCell(std::shared_ptr<Cell> cell);
        bool getHostile();
        int getGold();
        std::shared_ptr<Cell> getCell();

        virtual std::pair<int, int> move(int x, int y);
        virtual void attack(std::shared_ptr<Player> player) = 0;

        // How is gold going to be transferred? Will we need to differentiate if its a human, merchant or Drag?
        virtual void getStruckBy(Shade * shade);
        virtual void getStruckBy(Drow * drow);
        virtual void getStruckBy(Vampire * vampire);
        virtual void getStruckBy(Troll * troll);
        virtual void getStruckBy(Goblin * goblin);

        // Keep purely virtual? or make simply virtual and implement a blank
        //TODO: possibly dd move in here
        virtual void nextTurn() = 0;

};

#endif
