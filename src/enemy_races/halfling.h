#include "../enemy.h"

class Halfling : public Enemy {
    public:
        Halfling(std::pair<int, int> position);
        virtual std::string attack(std::shared_ptr<Player> player) override;
        virtual std::string getStruckBy(Shade * shade) override;
        virtual std::string getStruckBy(Drow * drow) override;
        virtual std::string getStruckBy(Vampire * vampire) override;
        virtual std::string getStruckBy(Troll * troll) override;
        virtual std::string getStruckBy(Goblin * goblin) override;
        virtual void nextTurn() override;
};
