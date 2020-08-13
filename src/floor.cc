#include "cell.h"
#include "enemy.h"
#include "./items/gold.h"
#include "./items/potion_types/RHpotion.h"
#include "./items/potion_types/BApotion.h"
#include "./items/potion_types/BDpotion.h"
#include "./items/potion_types/PHpotion.h"
#include "./items/potion_types/WApotion.h"
#include "./items/potion_types/WDpotion.h"
#include "floor.h"

Floor::Floor(std::string & floorString, int height, int width, bool generate) {
    
    generateCells(floorString, height, width);
    attachNeighbours();
    
    // If a text file is not supplied, we generate our own things
    if (generate) {
        generateGold();
        generateEnemies();
        generatePotions();    
    }
    

    
}

std::pair<int, int> Floor::randomFreeCell() {
    int randomCell;
    int length = floorCells.size();
    std::pair<int, int> position;

    while (1) {
        randomCell = rand() % length;
        if ((floorCells[randomCell]->getOccupied() == false) && (floorCells[randomCell]->getType() == "Floor")) {
            position = floorCells[randomCell]->getPosition();
            break;
        }
    }

    return position;
}

void Floor::spawn(std::string type, std::pair<int, int> position) {
    if (type == "Human") {
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Human>(position)));
    }
    
    else if (type == "Dwarf") {
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Dwarf>(position)));
    }

    else if (type == "Elf") {
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Elf>(position)));
    }

    else if (type == "Orc") {
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Orc>(position)));
    }

    else if (type == "Merchant") {
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Merchant>(position)));
    }
    
    else if (type == "Dragon") {
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Dragon>(position)));
    }

    else if (type == "Halfling") {
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Halfling>(position)));
    }

    else if (type == "Small Hoard") {
        goldPiles.push_back(std::make_shared<Gold>(position, 1));
    }

    else if (type == "Normal Hoard") {
        goldPiles.push_back(std::make_shared<Gold>(position, 2));
    }

    else if (type == "Merchant Hoard") {
        goldPiles.push_back(std::make_shared<Gold>(position, 4));
    }

    else if (type == "Dragon Hoard") {
        goldPiles.push_back(std::make_shared<Gold>(position, 6));
        goldPiles.back()->setCanPickUp(false);

        // generate random dx,dy as either -1, 0, or 1;
        int dx = (rand() % 3) - 1;
        int dy = (rand() % 3) - 1;
        auto pos = std::pair<int, int>(position.first + dx, position.second + dy);
        
        // if they are the same, or if the new position is not a Floor tile, or if it's occupied
        while (((dx == 0) && (dy == 0)) || (grid[pos]->getType() != "Floor") || (grid[pos]->getOccupied() == true)) {
            int dir = rand() % 2;
            (dir == 0) ? dx = ((rand() % 3) - 1) : dy = ((rand() % 3) - 1);
            pos = std::pair<int, int>(position.first + dx, position.second + dy);
        }

        // make a dragon randomly in a 1 block radius of hoard
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Dragon>(pos, goldPiles.back())));
    }

    else if (type == "RH") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<RHPotion>("P", position)));
    }

    else if (type == "BA") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<BAPotion>("P", position)));
    }

    else if (type == "BD") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<BDPotion>("P", position)));
    }

    else if (type == "PH") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<PHPotion>("P", position)));
    }

    else if (type == "WA") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<WAPotion>("P", position)));
    }

    else if (type == "WD") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<WDPotion>("P", position)));
    }

}

void Floor::generateEnemies() {

    for (int i = 0; i < 20; i++) {
        int randomEnemies = rand() % 18;
        auto position = randomFreeCell();

        if (randomEnemies < 4) { spawn("Human", position); }
        else if (randomEnemies < 7) { spawn("Dwarf", position); }
        else if (randomEnemies < 12) { spawn("Halfling", position); }
        else if (randomEnemies < 14) { spawn("Elf", position); }
        else if (randomEnemies < 16) { spawn("Orc", position); }
        else { spawn("Merchant", position); }

        grid[position]->setCharacter(enemies.back());
    }
}

void Floor::generateGold() {
    for (int i = 0; i < 10; i++) {
        int randomGold = rand() % 8;
        auto position = randomFreeCell();

        if (randomGold < 5) { spawn("Normal Hoard", position); }
        else if (randomGold < 6) { spawn("Dragon Hoard", position); }
        else { spawn("Small Hoard", position); }

        grid[position]->setItem(goldPiles.back());
    }
}

void Floor::generatePotions() {
    for (int i = 0; i < 10; i++) {
        int randomPotion = rand() % 6;
        auto position = randomFreeCell();

        if (randomPotion == 1) { spawn("RH", position); }
        else if (randomPotion == 2) { spawn("BA", position); }
        else if (randomPotion == 3) { spawn("BD", position); }
        else if (randomPotion == 4) { spawn("PH", position); }
        else if (randomPotion == 5) { spawn("WA", position); }
        else { spawn("WD", position); }

        grid[position]->setItem(potions.back());
    }
}

void Floor::generateCells(std::string & floorString, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto position = std::pair<int, int>(x, y);

            std::string cellRep = std::to_string(floorString[(y * width) + x]);
            std::string cellType;

            if (cellRep == "|" || cellRep == "-") { cellType = "Wall";}
            else if (cellRep == "+") {cellType = "Door";}
            else if (cellRep == "#") {cellType = "Passage";}
            else if (cellRep == ".") {cellType = "Floor";}
            else if (cellRep == " ") {cellType = "Abyss";}
            else if (cellRep == "\\") {cellType = "Exit";}
            else if (cellRep == "H") {
                cellType = "Floor";
                spawn("Human", position);
            }
            else if (cellRep == "W") {
                cellType = "Floor";
                spawn("Dwarf", position);
            }
            else if (cellRep == "E") {
                cellType = "Floor";
                spawn("Elf", position);
            }
            else if (cellRep == "O") {
                cellType = "Floor";
                spawn("Orc", position);
            }
            else if (cellRep == "M") {
                cellType = "Floor";
                spawn("Merchant", position);
            }
            else if (cellRep == "D") {
                cellType = "Floor";
                spawn("Dragon", position);
            }
            else if (cellRep == "L") {
                cellType = "Floor";
                spawn("Halfling", position);
            }
            else if (cellRep == "0") {
                cellType = "Floor";
                spawn("RH", position);
            }
            else if (cellRep == "1") {
                cellType = "Floor";
                spawn("BA", position);
            }
            else if (cellRep == "2") {
                cellType = "Floor";
                spawn("BD", position);
            }
            else if (cellRep == "3") {
                cellType = "Floor";
                spawn("PH", position);
            }
            else if (cellRep == "4") {
                cellType = "Floor";
                spawn("WA", position);
            }
            else if (cellRep == "5") {
                cellType = "Floor";
                spawn("WD", position);
            }
            else if (cellRep == "6") {
                cellType = "Floor";
                spawn("Normal Hoard", position);
            }
            else if (cellRep == "7") {
                cellType = "Floor";
                spawn("Small Hoard", position);
            }
            else if (cellRep == "8") {
                cellType = "Floor";
                spawn("Merchant Hoard", position);
            }
            else if (cellRep == "9") {
                cellType = "Floor";
                spawn("Dragon Hoard", position);
            }
            
            std::shared_ptr<Cell> cell = std::make_shared<Cell>(cellType, cellRep, position);
            grid[position] = cell;
            if ((cellType == "Floor") || (cellType == "Door") || (cellType == "Passage") || (cellType == "Exit")) {floorCells.push_back(cell);}

            if (isLetter(cellRep.front())) {
                cell->setCharacter(enemies.back());
            }
            
            else if (isNumber(cellRep.front())) {
                if (std::stoi(cellRep) < 6) { cell->setItem(potions.back()); }
                else { cell->setItem(goldPiles.back()); }
            }
        }
    }
}

bool Floor::isLetter(char c) {
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}

bool Floor::isNumber(char c) {
    if (c >= '0' && c <= '9') {
        return true;
    }
    return false;
}


void Floor::attachNeighbours() {
    for (auto cell : floorCells) {
        int x = cell->getPosition().first;
        int y = cell->getPosition().second;

        if ((!(grid[std::pair<int, int> (x - 1, y - 1)]->getType() == "Wall")) &&
            (!(grid[std::pair<int, int> (x - 1, y - 1)]->getType() == "Abyss"))) {
                cell->attach(grid[std::pair<int, int> (x - 1, y - 1)]);
        }

        else if ((!(grid[std::pair<int, int> (x, y - 1)]->getType() == "Wall")) &&
            (!(grid[std::pair<int, int> (x, y - 1)]->getType() == "Abyss"))) {
                cell->attach(grid[std::pair<int, int> (x, y - 1)]);
        }

        else if ((!(grid[std::pair<int, int> (x + 1, y - 1)]->getType() == "Wall")) &&
            (!(grid[std::pair<int, int> (x + 1, y - 1)]->getType() == "Abyss"))) {
                cell->attach(grid[std::pair<int, int> (x + 1, y - 1)]);
        }

        else if ((!(grid[std::pair<int, int> (x - 1, y)]->getType() == "Wall")) &&
            (!(grid[std::pair<int, int> (x - 1, y)]->getType() == "Abyss"))) {
                cell->attach(grid[std::pair<int, int> (x - 1, y)]);
        }

        else if ((!(grid[std::pair<int, int> (x + 1, y)]->getType() == "Wall")) &&
            (!(grid[std::pair<int, int> (x + 1, y)]->getType() == "Abyss"))) {
                cell->attach(grid[std::pair<int, int> (x + 1, y)]);
        }

        else if ((!(grid[std::pair<int, int> (x - 1, y + 1)]->getType() == "Wall")) &&
            (!(grid[std::pair<int, int> (x - 1, y + 1)]->getType() == "Abyss"))) {
                cell->attach(grid[std::pair<int, int> (x - 1, y + 1)]);
        }

        else if ((!(grid[std::pair<int, int> (x, y + 1)]->getType() == "Wall")) &&
            (!(grid[std::pair<int, int> (x, y + 1)]->getType() == "Abyss"))) {
                cell->attach(grid[std::pair<int, int> (x, y + 1)]);
        }

        else if ((!(grid[std::pair<int, int> (x + 1, y + 1)]->getType() == "Wall")) &&
            (!(grid[std::pair<int, int> (x + 1, y + 1)]->getType() == "Abyss"))) {
                cell->attach(grid[std::pair<int, int> (x + 1, y + 1)]);
        }
    }
}

void Floor::nextTurn() {

}

std::map<std::pair<int, int>, std::shared_ptr<Cell>> & Floor::getGrid() { return grid; }
std::shared_ptr<Cell> Floor::getExit() { return exit; }
std::vector<std::shared_ptr<Cell>> & Floor::getFloorCell() {
    return floorCells;
}
