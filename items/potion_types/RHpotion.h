#ifndef _RHPOTION_
#define _RHPOTION_

#include "../potion.h"

class RHPotion : public Potion {
    public:
        RHPotion(std::string rep, std::pair<int, int> position);
};

#endif
