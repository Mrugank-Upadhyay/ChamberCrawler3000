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
    bool hasMoved;
    static bool isStopped;
    bool isHostile;
    bool giveGold;
    int gold;
    Cell * cell = nullptr;

    bool distanceLessThanTwo(std::pair<int, int> position);

    protected:
        int randomGold();
        void transferGold(Player * player);


    public:
        Enemy(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position, bool hostile, int gold, bool giveGold);

        void resetMoved();
        static void setStopped(bool stopped);
        void setHostile(bool hostile);
        void setGold(int value);
        void setCell(Cell * cell);
        static bool getStopped();
        bool getHostile();
        int getGold();
        Cell * getCell();

        virtual void move();

        virtual std::string attack(std::shared_ptr<Player> player) = 0;
        virtual std::string getStruckBy(Shade * shade);
        virtual std::string getStruckBy(Drow * drow);
        virtual std::string getStruckBy(Vampire * vampire);
        virtual std::string getStruckBy(Troll * troll);
        virtual std::string getStruckBy(Goblin * goblin);
        
        void nextTurn() override;
};

#endif
