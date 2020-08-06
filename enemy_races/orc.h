#ifndef _ORC_
#define _ORC_

#include "../enemy.h"

class Orc : public Enemy {
    public:
        Orc(std::pair<int, int> position);
};

#endif
