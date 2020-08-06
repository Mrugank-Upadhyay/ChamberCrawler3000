#ifndef _HUMAN_
#define _HUMAN_

#include "../enemy.h"

class Human : public Enemy {
    public:
        Human(std::pair<int, int> position);
};

#endif
