#include "dragon.h"

// If attacked, make all future Dragons hostile!
Dragon::Dragon(std::pair<int, int> position)
    : Enemy{"Dragon", "D", 150, 20, 20, position, false, 6, false} {}

// Wanna have int x, and int y be the gold position, sort of as an anchor point
// then we have the drag go around in circles by picking a random direction
std::pair<int, int> Dragon::move(int x, int y) {

}

void Dragon::attack(std::shared_ptr<Player> player) {
    player->getStruckBy(std::make_shared<Dragon>(this));
}

void Dragon::nextTurn() {}
