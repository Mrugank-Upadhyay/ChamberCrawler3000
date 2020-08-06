#ifndef _ITEM_
#define _ITEM_

#include <string>
#include <utility>

class Player;

class Item {
    std::string type;
    std::string rep;
    std::pair<int, int> position;
  public:
    std::string & getType() const;
    std::string & getRep() const;
    std::pair<int, int> getPosition() const;
    void apply(Player p);
};

#endif
