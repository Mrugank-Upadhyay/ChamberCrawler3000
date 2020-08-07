#ifndef _WAPOTION_
#define _WAPOTION_

#include "../potion.h"

class WAPotion : public Potion {
    public:
        WAPotion(std::string rep, std::pair<int, int> position);
};

#endif
