#include "cell.h"
#include "enemy.h"
#include "enemy_headers.h"
#include "./items/gold.h"
#include "./items/potion_types/RHpotion.h"
#include "./items/potion_types/BApotion.h"
#include "./items/potion_types/BDpotion.h"
#include "./items/potion_types/PHpotion.h"
#include "./items/potion_types/WApotion.h"
#include "./items/potion_types/WDpotion.h"
#include "floor.h"
#include <iostream>

Floor::Floor(std::string floorString, int height, int width, bool generate) {
    
    generateCells(floorString, height, width);
    attachNeighbours();
    
    // If a text file is not supplied, we generate our own things
    if (generate) {
        generateGold();
        generateEnemies();
        generatePotions();    
    }
    
    else {
        attachDragons();
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

std::shared_ptr<Enemy> Floor::spawnEnemy(std::string type, std::pair<int, int> position) {
    std::shared_ptr<Enemy> enemy;
    if (type == "Human") {
        enemy = std::dynamic_pointer_cast<Enemy>(std::make_shared<Human>(position));
    }
    
    else if (type == "Dwarf") {
       enemy = std::dynamic_pointer_cast<Enemy>(std::make_shared<Dwarf>(position));
    }

    else if (type == "Elf") {
        enemy = std::dynamic_pointer_cast<Enemy>(std::make_shared<Elf>(position));
    }

    else if (type == "Orc") {
        enemy = std::dynamic_pointer_cast<Enemy>(std::make_shared<Orc>(position));
    }

    else if (type == "Merchant") {
        enemy = std::dynamic_pointer_cast<Enemy>(std::make_shared<Merchant>(position));
    }

    else if (type == "Dragon") {
        enemy = std::dynamic_pointer_cast<Enemy>(std::make_shared<Dragon>(position));
    }

    else if (type == "Halfling") {
        enemy = std::dynamic_pointer_cast<Enemy>(std::make_shared<Halfling>(position));
    }

    return enemy;
}


void Floor::spawnGold(std::string type, std::pair<int, int> position, bool generate) {
    if (type == "Small Hoard") {
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

        if (generate) {
            // generate random dx,dy as either -1, 0, or 1;
            int dx = (rand() % 3) - 1;
            int dy = (rand() % 3) - 1;
            auto pos = std::pair<int, int>(position.first + dx, position.second + dy);
            
            // if they are the same, or if the new position is not a Floor tile, or if it's occupied
            while (((dx == 0) && (dy == 0)) || (grid.at(pos)->getType() != "Floor") || (grid.at(pos)->getOccupied() == true)) {
                int dir = rand() % 2;
                (dir == 0) ? dx = ((rand() % 3) - 1) : dy = ((rand() % 3) - 1);
                pos = std::pair<int, int>(position.first + dx, position.second + dy);
            }

            // make a dragon randomly in a 1 block radius of hoard
            std::shared_ptr<Enemy> enemy;
            enemy = std::dynamic_pointer_cast<Enemy>(std::make_shared<Dragon>(pos, findCell(position).get()));
            enemies.push_back(enemy);
            grid.at(pos)->setCharacter(enemy);
            enemy->setCell(grid.at(pos).get());

        }
    }
}

void Floor::spawnPotion(std::string type, std::pair<int, int> position) {
    if (type == "RH") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<RHPotion>(position)));
    }

    else if (type == "BA") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<BAPotion>(position)));
    }

    else if (type == "BD") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<BDPotion>(position)));
    }

    else if (type == "PH") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<PHPotion>(position)));
    }

    else if (type == "WA") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<WAPotion>(position)));
    }

    else if (type == "WD") {
        potions.push_back(std::dynamic_pointer_cast<Potion>(std::make_shared<WDPotion>(position)));
    }
}

void Floor::generateEnemies() {

    for (int i = 0; i < 20; i++) {
        int randomEnemies = rand() % 18;
        auto position = randomFreeCell();
        std::shared_ptr<Enemy> enemy;

        if (randomEnemies < 4) { enemy = spawnEnemy("Human", position); }
        else if (randomEnemies < 7) { enemy = spawnEnemy("Dwarf", position); }
        else if (randomEnemies < 12) { enemy = spawnEnemy("Halfling", position); }
        else if (randomEnemies < 14) { enemy = spawnEnemy("Elf", position); }
        else if (randomEnemies < 16) { enemy = spawnEnemy("Orc", position); }
        else { enemy = spawnEnemy("Merchant", position); }

        grid.at(position)->setCharacter(enemy);
        enemy->setCell((grid.at(position).get()));
        enemies.push_back(enemy);
    }
}

void Floor::generateGold() {
    for (int i = 0; i < 10; i++) {
        int randomGold = rand() % 8;
        auto position = randomFreeCell();

        if (randomGold < 5) { spawnGold("Normal Hoard", position); }
        else if (randomGold < 6) { spawnGold("Dragon Hoard", position); }
        else { spawnGold("Small Hoard", position); }

        grid.at(position)->setItem(goldPiles.back());
    }
}

void Floor::generatePotions() {
    for (int i = 0; i < 10; i++) {
        int randomPotion = rand() % 6;
        auto position = randomFreeCell();

        if (randomPotion == 1) { spawnPotion("RH", position); }
        else if (randomPotion == 2) { spawnPotion("BA", position); }
        else if (randomPotion == 3) { spawnPotion("BD", position); }
        else if (randomPotion == 4) { spawnPotion("PH", position); }
        else if (randomPotion == 5) { spawnPotion("WA", position); }
        else { spawnPotion("WD", position); }

        grid.at(position)->setItem(potions.back());
    }
}

void Floor::generateCells(std::string floorString, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto position = std::pair<int, int>(x, y);
            int index = (y * width) + x;
            std::string cellRep;
            cellRep.push_back(floorString.at(index));
            std::string cellType;
            std::shared_ptr<Enemy> enemy = nullptr;

            if ((cellRep == "|") || (cellRep == "-")) { cellType = "Wall";}
            else if (cellRep == "+") {cellType = "Door";}
            else if (cellRep == "#") {cellType = "Passage";}
            else if (cellRep == ".") {cellType = "Floor";}
            else if (cellRep == " ") {cellType = "Abyss";}
            else if (cellRep == "\\") {cellType = "Exit";}
            else if (cellRep == "@") {
                cellType = "Floor";
                std::shared_ptr<Cell> cell = std::make_shared<Cell>(cellType, ".", position);
                grid[position] = cell;
                floorCells.push_back(cell);
                continue;
            }
            
            else if (cellRep == "H") {
                cellType = "Floor";
                enemy = spawnEnemy("Human", position);
            }
            else if (cellRep == "W") {
                cellType = "Floor";
                enemy = spawnEnemy("Dwarf", position);
            }
            else if (cellRep == "E") {
                cellType = "Floor";
                enemy = spawnEnemy("Elf", position);
            }
            else if (cellRep == "O") {
                cellType = "Floor";
                enemy = spawnEnemy("Orc", position);
            }
            else if (cellRep == "M") {
                cellType = "Floor";
                enemy = spawnEnemy("Merchant", position);
            }
            else if (cellRep == "D") {
                cellType = "Floor";
                enemy = spawnEnemy("Dragon", position);
            }
            else if (cellRep == "L") {
                cellType = "Floor";
                enemy = spawnEnemy("Halfling", position);
            }
            else if (cellRep == "0") {
                cellType = "Floor";
                spawnPotion("RH", position);
            }
            else if (cellRep == "1") {
                cellType = "Floor";
                spawnPotion("BA", position);
            }
            else if (cellRep == "2") {
                cellType = "Floor";
                spawnPotion("BD", position);
            }
            else if (cellRep == "3") {
                cellType = "Floor";
                spawnPotion("PH", position);
            }
            else if (cellRep == "4") {
                cellType = "Floor";
                spawnPotion("WA", position);
            }
            else if (cellRep == "5") {
                cellType = "Floor";
                spawnPotion("WD", position);
            }
            else if (cellRep == "6") {
                cellType = "Floor";
                spawnGold("Normal Hoard", position);
            }
            else if (cellRep == "7") {
                cellType = "Floor";
                spawnGold("Small Hoard", position);
            }
            else if (cellRep == "8") {
                cellType = "Floor";
                spawnGold("Merchant Hoard", position);
            }
            else if (cellRep == "9") {
                cellType = "Floor";
                spawnGold("Dragon Hoard", position, false);
            }
            
            std::shared_ptr<Cell> cell = std::make_shared<Cell>(cellType, cellRep, position);
            grid[position] = cell;

            if (enemy != nullptr) {
                enemy->setCell(cell.get());
                enemies.push_back(enemy);
            }

            if ((cellType == "Floor") || (cellType == "Door") || (cellType == "Passage") || (cellType == "Exit")) {floorCells.push_back(cell);}
            if (cellType == "Exit") {
                exit = cell;
            }
            if (isLetter(cellRep.front())) {
                cell->setCharacter(enemies.back());
            }
            
            else if (isNumber(cellRep.front())) {
                if (std::stoi(cellRep) < 6) { cell->setItem(potions.back()); }
                else { 
                    auto goldItem = goldPiles.back();
                    cell->setItem(std::dynamic_pointer_cast<Item>(goldItem)); 
                }
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

std::shared_ptr<Cell> Floor::findCell(std::pair<int, int> position) {
    for (auto cell : floorCells) {
        if (cell->getPosition() == position) {
            return cell;
        }
    }

    return nullptr;
}

void Floor::attachDragons() {
    std::vector<std::shared_ptr<Dragon>> dragons;
    for (auto enemy : enemies) {
        if (enemy->getRace() == "Dragon") { dragons.push_back(std::dynamic_pointer_cast<Dragon>(enemy)); }
    }

    for (auto dragon : dragons) {
        for (auto neighbour : findCell(dragon->getPosition())->getObservers()) {
            auto neighbourCell = dynamic_cast<Cell *>(neighbour);
            if ((neighbourCell->getItem() != nullptr) && (neighbourCell->getItem()->getType() == "Gold")) {
                dragon->setGoldCell(neighbourCell);
                break;
            }
        }
    }
}

void Floor::attachNeighbours() {
    for (auto cell : floorCells) {
        int x = cell->getPosition().first;
        int y = cell->getPosition().second;

        int count = 0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if ((dx == 0) && (dy == 0)) { continue; }

                auto newpos = std::pair<int, int>(x + dx, y + dy);
                if ((grid.at(newpos)->getType() != "Wall") && 
                    (grid.at(newpos)->getType() != "Abyss")) {
                        cell->attach(grid.at(newpos).get());
                        count++;
                }
            }
        }

        //std::cout << "(" << cell->getPosition().first << "," << cell->getPosition().second << ") : count =" << count << ", length =  " << cell->getObservers().size() << std::endl;
    }
}


void Floor::removeEnemy(std::shared_ptr<Enemy> enemy) {
    int length = enemies.size();
    for (int i = 0; i < length; i++) {
        if (enemies.at(i)->getPosition() == enemy->getPosition()) {
            enemies.erase(enemies.begin() + i);
            break;
        }
    }
}

std::string Floor::nextTurn() {

    // Fix double attack 
    // fix attack and then move
    std::string message = "";
    // std::cout << "NEXT TURN CALLED" << std::endl;
    for (auto cell : grid) {
        if (cell.second->getPlayer() != nullptr) {
            cell.second->getPlayer()->nextTurn();
        }

        // REMOVE DEAD ENEMIES
        // make sure print is correct so the moment they hit 0 or less, they get cleared.
        else if (cell.second->getEnemy() != nullptr) {
            auto observers = (cell.second)->getObservers();

            if (cell.second->getEnemy()->getHP() <= 0) {
                auto enemy = cell.second->getEnemy();
                std::string race = enemy->getRace();
                cell.second->setNullCharacter();
                
                if (race == "Human") {
                    int len = observers.size();
                    std::vector<int> unOccupied;
                    
                    for(int i = 0; i < len; i++) {
                        auto obsCell = dynamic_cast<Cell *>(observers.at(i));
                        if((!obsCell->getOccupied()) && (obsCell->getType() != "Door")) {
                            unOccupied.push_back(i);
                        }
                    }
                    
                    // REMOVE COUT
                    std::cout << std::to_string(unOccupied.size()) << std::endl;;

                    if(unOccupied.size() > 1) {
                        int chosen = rand() % unOccupied.size();
                        auto chosenCell = dynamic_cast<Cell *>(observers.at(unOccupied.at(chosen)));
                        auto position = chosenCell->getPosition();
                        auto goldItem = std::make_shared<Gold>(position, 2);
                        chosenCell->setItem(goldItem);

                        unOccupied.erase(unOccupied.begin() + chosen);
                        
                        chosen = rand() % unOccupied.size();
                        chosenCell = dynamic_cast<Cell *>(observers.at(unOccupied.at(chosen)));
                        position = chosenCell->getPosition();
                        goldItem = std::make_shared<Gold>(position, 2);
                        chosenCell->setItem(goldItem);
                    }
                    else {
                        auto goldItem = std::make_shared<Gold>(cell.second->getPosition(), 4);
                        cell.second->setItem(goldItem);
                    }
                }

                else if (race == "Dragon") {
                    auto dragon = std::dynamic_pointer_cast<Dragon>(enemy);
                    std::dynamic_pointer_cast<Gold>(dragon->getGoldCell()->getItem())->setCanPickUp(true);
                }

                else if (race == "Merchant") {
                    cell.second->setItem(std::make_shared<Gold>(cell.second->getPosition(), 4));
                }

                removeEnemy(enemy);
            }

            else {
                bool attacked = false;

                for (auto obs: observers) {
                    auto obsCell = dynamic_cast<Cell *>(obs);
                    if (obsCell->getPlayer() != nullptr && cell.second->getEnemy()->getHostile()) {
                        message += cell.second->getEnemy()->attack(obsCell->getPlayer());
                        attacked = true;
                        break;     
                    }
                }

                if ((!cell.second->getEnemy()->getStopped()) && (attacked == false)) {
                    cell.second->getEnemy()->move();
                }
            }
        }
    }
    for(auto enemy: enemies) {
      enemy->resetMoved();
    }

    return message;
}

std::map<std::pair<int, int>, std::shared_ptr<Cell>> & Floor::getGrid() { return grid; }
std::shared_ptr<Cell> Floor::getExit() { return exit; }
std::vector<std::shared_ptr<Cell>> & Floor::getFloorCell() {
    return floorCells;
}
