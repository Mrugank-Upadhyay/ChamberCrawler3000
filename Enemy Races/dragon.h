#ifndef _DRAGON_
#define _DRAGON_

#include "../enemy.h"

class Dragon : public Enemy {
    public:
        Dragon(std::pair<int, int> position);
        std::pair<int, int> move(int x, int y);
};

#endif
