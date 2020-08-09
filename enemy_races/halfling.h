#include "../enemy.h"

class Halfling : public Enemy, std::enable_shared_from_this<Halfling> {
    public:
        Halfling(std::pair<int, int> position);
        virtual void attack(std::shared_ptr<Player> player) override;
        virtual void getStruckBy(Shade * shade) override;
        virtual void getStruckBy(Drow * drow) override;
        virtual void getStruckBy(Vampire * vampire) override;
        virtual void getStruckBy(Troll * troll) override;
        virtual void getStruckBy(Goblin * goblin) override;
        virtual void nextTurn() override;
};