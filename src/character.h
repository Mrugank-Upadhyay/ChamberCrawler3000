#ifndef _CHARACTER_
#define _CHARACTER_

#include <string>
#include <map>
#include <cmath>


class Character {
    std::string race;
    std::string rep;
    int hp;
    int atk;
    int def;
    std::pair<int, int> position;

    protected:
        // add implementation
        int calculateDamage(int atk, int def);

    public:
        Character(std::string race, std::string rep, int hp, int atk, int def, std::pair<int, int> position);

        // Do we need to set Race or Rep?
        void setHP(int value);
        void setATK(int value);
        void setDEF(int value);
        void setPosition(std::pair<int, int> pos);

        std::string getRace();
        std::string getRep();
        int getHP();
        int getATK();
        int getDEF();
        std::pair<int, int> getPosition();

        virtual void nextTurn() = 0;

        virtual std::string info();
};

#endif
