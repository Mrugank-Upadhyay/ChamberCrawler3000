#ifndef _CELL_
#define _CELL_

#include <string>

#include "subject.h"
#include "observer.h"
#include "character.h"
#include "item.h"

class Cell: public Subject, public Observer {
    std::string type;
    std::string rep;
    std::pair<int, int> position;
    std::shared_ptr<Character> character;
    std::shared_ptr<Item> item;
  public:
    Cell(std::string type,std::string rep,std::pair<int, int> position);
    std::string & getType();
    std::string & getRep();
    void setRep(std::string & rep);
    std::pair<int, int> getPosition();
    void setPosition(std::pair<int, int> position);
    std::shared_ptr<Character> getCharacter();
    void setCharacter(std::shared_ptr<Character> character);
    std::shared_ptr<Item> getItem();
    void setItem(std::shared_ptr<Item> item);
    std::vector<std::shared_ptr<Observer>> & getObservers();

    void notify(std::shared_ptr<Subject> whoNotified);
};

#endif
