#include "item.h"

Item::Item(std::string type, std::string rep, std::pair<int, int> position)
    : type{type}, rep{rep}, position{position} {}

std::string & Item::getType() {
    return type;
}

std::string & Item::getRep() {
    return rep;
}

void Item::setRep(std::string & rep) {
    this->rep = rep;
}

std::pair<int, int> Item::getPosition() const {
    return position;
}
