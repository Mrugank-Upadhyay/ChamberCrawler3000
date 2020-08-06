#ifndef _ITEM_
#define _ITEM_

#include <string>
#include <utility>
#include <memory>

class Player;

class Item {
    std::string type;
    std::string rep;
    std::pair<int, int> position;
  public:
    Item(std::string type, std::string rep, std::pair<int, int> position);

    std::string & getType() const;

    std::string & getRep() const;
    void setRep(std::string & rep);

    std::pair<int, int> getPosition() const;
    virtual void apply(Player p);
};

#endif
