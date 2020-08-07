#ifndef _SUBJECT_
#define _SUBJECT_

#include <vector>
#include <memory>

#include "observer.h"

class Subject {
  protected:
    std::vector<std::shared_ptr<Observer>> observers;
  public:
    Subject();
    virtual ~Subject();

    void attach(std::shared_ptr<Observer> observer);
    void detach(std::shared_ptr<Observer> observer);

    void notifyObservers();
};

#endif
