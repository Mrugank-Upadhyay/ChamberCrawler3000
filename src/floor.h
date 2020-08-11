#ifndef _FLOOR_
#define _FLOOR_

#include <map>
#include <vector>
#include <memory>

class Cell;
class Enemy;
class Gold;
class Potion;


class Floor {
    std::map<std::pair<int, int>, std::shared_ptr<Cell>> grid;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Potion>> potions;
    std::vector<std::shared_ptr<Gold>> goldPiles;
    std::shared_ptr<Cell> exit;
    void spawn(std::string type);

    public:
        Floor();
        void nextTurn(); 
};

#endif
