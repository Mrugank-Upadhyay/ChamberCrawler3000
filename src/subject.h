#ifndef _SUBJECT_
#define _SUBJECT_

#include <vector>
#include <memory>

#include "observer.h"

class Player;
class Enemy;

class Subject {
  protected:
    // convert into raw pointer
    std::vector<std::shared_ptr<Observer>> observers;
  public:
    Subject();
    virtual ~Subject();
    // std::vector<std::shared_ptr<Observer>> getObservers();
    void attach(std::shared_ptr<Observer> observer);
    void detach(std::shared_ptr<Observer> observer);
    void notifyObservers();
};

#endif
