#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <memory>

#include "character.h"

class Cell;

class Enemy;
class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Dragon;
class Halfling;

class Item;
class Potion;
class Gold;

class Player: public Character {
    Cell * cell;
    int gold;
    int maxHP;
    int tmpATK;
    int tmpDEF;
    bool turnFinished;
    std::vector<std::shared_ptr<Item>> bag;
    bool bagActive;
  public:
    Player(std::string race, int hp, int atk, int def,
    std::pair<int, int> position, int gold, int maxHP);

    Cell * getCell() const;
    void setCell(Cell * cell);

    int getGold() const;
    void addGold(int gold);

    int getMaxHP() const;
    void setMaxHP(int maxHP);

    int getTmpATK() const;
    void setTmpATK(int tmpATK);

    int getTmpDEF() const;
    void setTmpDEF(int tmpDEF);

    bool isTurnFinished() const;
    void setTurnedFinished(bool turnFinished);

    std::vector<std::shared_ptr<Item>> getBag();
    void addToBag(std::shared_ptr<Item> item);
    void removeFromBag(int item);
    bool isBagActive() const;
    void setBagActive(bool bagActive);

    std::pair<int, int> move(std::pair<int, int> position);

    virtual void applyItem(Potion * potion);
    virtual void applyItem(Gold * gold);

    virtual std::string attack(std::shared_ptr<Enemy> enemy) = 0;

    virtual std::string getStruckBy(Human * enemy);
    virtual std::string getStruckBy(Dwarf * enemy);
    virtual std::string getStruckBy(Elf * enemy);
    virtual std::string getStruckBy(Orc * enemy);
    virtual std::string getStruckBy(Dragon * enemy);
    virtual std::string getStruckBy(Merchant * enemy);
    virtual std::string getStruckBy(Halfling * enemy);

    virtual void nextTurn() override;
};

#endif
