#ifndef _SHADE_
#define _SHADE_

#include "../player.h"

class Shade : public Player {
    public:
        Shade(std::pair<int, int> position);
        void attack(std::shared_ptr<Enemy> enemy) override;
};

#endif
