#ifndef _CHARACTER_
#define _CHARACTER_

#include <string>
#include <map>


class Character {
    std::string race;
    std::string rep;
    int health;
    int atk;
    int def;
    std::pair<int, int> position;

    public:
    Character(std::string race, std::string rep, int health, int atk, int def, std::pair<int, int> position);

    // Do we need to set Race or Rep?
    void setHealth(int value);
    void setAtk(int value);
    void setDef(int value);
    void setPosition(std::pair<int, int> pos);

    std::string getRace();
    std::string getRep();
    int getHealth();
    int getAtk();
    int getDef();
    std::pair<int, int> getPosition();

    virtual void nextTurn() = 0;
};

#endif
