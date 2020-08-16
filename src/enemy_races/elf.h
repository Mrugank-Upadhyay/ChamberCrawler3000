#include "../enemy.h"

class Elf : public Enemy {
    public:
        Elf(std::pair<int, int> position);
        virtual std::string attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};
