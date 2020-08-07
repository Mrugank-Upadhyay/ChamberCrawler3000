#include "../enemy.h"

class Halfling : public Enemy {
    public:
        Halfling(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void getStruckBy(std::shared_ptr<Shade> shade) override;
        virtual void getStruckBy(std::shared_ptr<Drow> drow) override;
        virtual void getStruckBy(std::shared_ptr<Vampire> vampire) override;
        virtual void getStruckBy(std::shared_ptr<Troll> troll) override;
        virtual void getStruckBy(std::shared_ptr<Goblin> goblin) override;
        virtual void nextTurn() override;
};