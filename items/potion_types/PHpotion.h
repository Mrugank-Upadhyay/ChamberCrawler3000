#ifndef _PHPOTION_
#define _PHPOTION_

#include "../potion.h"

class PHPotion : public Potion {
    public:
        PHPotion(std::string rep, std::pair<int, int> position);
};

#endif
