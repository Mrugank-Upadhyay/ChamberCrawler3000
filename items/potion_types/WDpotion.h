#ifndef _WDPOTION_
#define _WDPOTION_

#include "../potion.h"

class WDPotion : public Potion {
    public:
        WDPotion(std::string rep, std::pair<int, int> position);
};

#endif
