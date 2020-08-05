#include "character.h"

// should we forward declare these? Or keep just #include in header?
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"

class Player;

class Enemy : public Character {
    bool isHostile;
    int gold;

    public:
    Enemy(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position, bool hostile, int gold);

    void setHostile(bool hostile);
    bool getHostile();
    int getGold();

    virtual std::pair<int, int> move();
    virtual void attack(Player player);
    virtual void getStruckBy(Shade shade);
    virtual void getStruckBy(Drow drow);
    virtual void getStruckBy(Vampire vampire);
    virtual void getStruckBy(Troll troll);
    virtual void getStruckBy(Goblin goblin);

    // Keep purely virtual? or make simply virtual and implement a blank
    virtual void nextTurn() = 0;

};