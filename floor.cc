#include "cell.h"
#include "enemy.h"
#include "./items/gold.h"
#include "./items/potion.h"
#include "floor.h"

Floor::Floor() {
    int random;

    for (int i = 0; i < 10; i++) {
        random = rand() % 18;

    }
}

void Floor::spawn(std::string type) {
    auto position = std::pair<int, int>(0, 0);
    if (type == "human") {
        enemies.push_back(std::make_shared<Human>(position));
    }
}