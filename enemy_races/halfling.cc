#include "halfling.h"

Halfling::Halfling(std::pair<int, int> position) 
    : Enemy{"Halfling", "L", 100, 15, 20, position, true, randomGold(), true} {}
