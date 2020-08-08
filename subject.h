#ifndef _SUBJECT_
#define _SUBJECT_

#include <vector>
#include <memory>

#include "observer.h"

class Player;
class Enemy;

class Subject {
  protected:
    std::vector<std::shared_ptr<Observer>> observers;
  public:
    Subject();
    virtual ~Subject();

    void attach(std::shared_ptr<Observer> observer);
    void detach(std::shared_ptr<Observer> observer);
    void notifyObservers();
    virtual std::shared_ptr<Player> getPlayer() = 0;
    virtual std::shared_ptr<Enemy> getEnemy() = 0;
};

#endif
