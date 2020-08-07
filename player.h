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
    std::shared_ptr<Cell>  cell;
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

    std::shared_ptr<Cell>  getCell() const;
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

    std::pair<int, int> move(int x, int y);

    virtual void applyItem(std::shared_ptr<Potion> potion);
    virtual void applyItem(std::shared_ptr<Gold> gold);

    virtual void attack(std::shared_ptr<Enemy> enemy) = 0;

    virtual void getStruckBy(std::shared_ptr<Human> enemy);
    virtual void getStruckBy(std::shared_ptr<Dwarf> enemy);
    virtual void getStruckBy(std::shared_ptr<Elf> enemy);
    virtual void getStruckBy(std::shared_ptr<Orc> enemy);
    virtual void getStruckBy(std::shared_ptr<Dragon> enemy);
    virtual void getStruckBy(std::shared_ptr<Merchant> enemy);
    virtual void getStruckBy(std::shared_ptr<Halfling> enemy);

    virtual void nextTurn() = 0;
};

#endif
