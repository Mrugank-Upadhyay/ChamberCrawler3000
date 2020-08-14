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
    std::vector<Observer *> observers;
  public:
    Subject();
    virtual ~Subject();
    // std::vector<Observer *> getObservers();
    void attach(Observer * observer);
    void detach(Observer * observer);
    void notifyObservers();
};

#endif
