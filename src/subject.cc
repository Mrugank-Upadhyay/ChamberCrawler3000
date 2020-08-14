#include "player.h"
#include "enemy.h"
#include "subject.h"

Subject::Subject() {}
Subject::~Subject() {}

// std::vector<std::shared_ptr<Observer>> Subject::getObservers() {
//   return observers;
// }

void Subject::attach(std::shared_ptr<Observer> observer) {
  observers.emplace_back(observer);
}

void Subject::detach(std::shared_ptr<Observer> observer) {
  for(auto it = observers.begin(); it != observers.end(); ++it) {
    if(*it == observer) {
      observers.erase(it);
      break;
    }
  }
}

void Subject::notifyObservers() {
  for(auto observer: observers) observer->notify(this);
}
