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

Floor::Floor() {
    generateEnemies();
    generateGold();
    generatePotions();
}

void Floor::spawn(std::string type) {
    auto position = std::pair<int, int>(0, 0);
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

    else if (type == "Dragon Hoard") {
        goldPiles.push_back(std::make_shared<Gold>(position, 6));
        enemies.push_back(std::dynamic_pointer_cast<Enemy>(std::make_shared<Dragon>(position)));
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
        int random = rand() % 18;

        if (random < 4) { spawn("Human"); }
        else if (random < 7) { spawn("Dwarf"); }
        else if (random < 12) { spawn("Halfling"); }
        else if (random < 14) { spawn("Elf"); }
        else if (random < 16) { spawn("Orc"); }
        else { spawn("Merchant"); }
    }
}

void Floor::generateGold() {
    for (int i = 0; i < 10; i++) {
        int random = rand() % 8;

        if (random < 5) { spawn("Normal Hoard"); }
        else if (random < 6) { spawn("Dragon Hoard"); }
        else { spawn("Small Hoard"); }
    }
}

void Floor::generatePotions() {
    for (int i = 0; i < 10; i++) {
        int random = rand() % 6;

        if (random == 1) { spawn("RH"); }
        else if (random == 2) { spawn("BA"); }
        else if (random == 3) { spawn("BD"); }
        else if (random == 4) { spawn("PH"); }
        else if (random == 5) { spawn("WA"); }
        else { spawn("WD"); }
        
    }
}