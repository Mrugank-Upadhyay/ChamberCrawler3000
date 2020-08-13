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
    std::vector<std::shared_ptr<Cell>> floorCells;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Potion>> potions;
    std::vector<std::shared_ptr<Gold>> goldPiles;
    std::shared_ptr<Cell> exit;
    void spawn(std::string type, std::pair<int, int> position);
    void generateEnemies();
    void generateGold();
    void generatePotions();
    void generateCells(std::string & floorString, int height, int width);
    void createSpawns(std::string & floorString, int height, int width);
    bool isLetter(char c);
    bool isNumber(char c);
    std::pair<int, int> randomFreeCell();
    void attachNeighbours();

    public:
        Floor(std::string & floorString, int height, int width, bool generate);
        void nextTurn(); 
        std::map<std::pair<int, int>, std::shared_ptr<Cell>> & getGrid();
};

#endif
