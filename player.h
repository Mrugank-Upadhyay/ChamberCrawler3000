#ifndef _PLAYER_
#define _PLAYER_

#include <vector>
#include <memory>

#include "character.h"
#include "item_FD.h"
#include "enemy_race_FD.h"

class Cell;
class Potion;
class Gold;

class Player: public Character {
    std::shared_ptr<Cell> cell;
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

    std::shared_ptr<Cell> getCell() const;
    void setCell(std::shared_ptr<Cell> cell);

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

    std::pair<int, int> move(std::shared_ptr<Cell> dest);

    virtual void applyItem(Potion * potion);
    virtual void applyItem(Gold * gold);

    virtual void attack(std::shared_ptr<Enemy> enemy) = 0;

    virtual void getStruckBy(Human * enemy);
    virtual void getStruckBy(Dwarf * enemy);
    virtual void getStruckBy(Elf * enemy);
    virtual void getStruckBy(Orc * enemy);
    virtual void getStruckBy(Dragon * enemy);
    virtual void getStruckBy(Merchant * enemy);
    virtual void getStruckBy(Halfling * enemy);

    virtual void nextTurn() = 0;
};

#endif
