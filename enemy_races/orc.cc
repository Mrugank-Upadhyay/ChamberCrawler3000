#include "orc.h"

Orc::Orc(std::pair<int, int> position)
    : Enemy{"Orc", "O", 180, 30, 25, position, true, randomGold(), true} {}
