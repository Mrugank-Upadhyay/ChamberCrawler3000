#include "../enemy.h"

class Elf : public Enemy, std::enable_shared_from_this<Elf> {
    public:
        Elf(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void nextTurn() override;
};