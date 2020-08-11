#ifndef _CELL_
#define _CELL_

#include <string>

#include "subject.h"
#include "player.h"
#include "enemy.h"
#include "item.h"

class Cell: public Subject, public Observer {
    std::string type;
    std::string rep;
    std::pair<int, int> position;
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;
    std::shared_ptr<Item> item;
  public:
    Cell(std::string type,std::string rep,std::pair<int, int> position);
    std::string & getType();
    std::string & getRep();
    void setRep(std::string & rep);
    std::pair<int, int> getPosition();
    void setPosition(std::pair<int, int> position);
    virtual std::shared_ptr<Player> getPlayer() override;
    virtual std::shared_ptr<Enemy> getEnemy() override;
    void setCharacter(std::shared_ptr<Player> player);
    void setCharacter(std::shared_ptr<Enemy> enemy);
    std::shared_ptr<Item> getItem();
    void setItem(std::shared_ptr<Item> item);
    std::vector<std::shared_ptr<Observer>> & getObservers();

    std::string info();

    void notify(Subject * whoNotified) override;
};

#endif
