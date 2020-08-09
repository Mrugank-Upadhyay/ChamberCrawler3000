#include "../enemy.h"

class Elf : public Enemy {
    public:
        Elf(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};