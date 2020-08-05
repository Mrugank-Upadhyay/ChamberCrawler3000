#ifndef _ENEMY_
#define _ENEMY_

#include "character.h"

// should we forward declare these? Or keep just #include in header?
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"

#include <memory>


class Player;

class Enemy : public Character {
    bool isHostile;
    int gold;

    public:
    Enemy(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position, bool hostile, int gold);

    void setHostile(bool hostile);
    bool getHostile();
    int getGold();

    virtual std::pair<int, int> move(int x, int y);
    virtual void attack(std::shared_ptr<Player> player);
    virtual void getStruckBy(std::shared_ptr<Shade> shade);
    virtual void getStruckBy(std::shared_ptr<Drow> drow);
    virtual void getStruckBy(std::shared_ptr<Vampire> vampire);
    virtual void getStruckBy(std::shared_ptr<Troll> troll);
    virtual void getStruckBy(std::shared_ptr<Goblin> goblin);

    // Keep purely virtual? or make simply virtual and implement a blank
    virtual void nextTurn() = 0;

};

#endif
