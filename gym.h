#ifndef GYM_H
#define GYM_H

#include "ownable.h"
#include "dice.h"
#include <string>

class Gym: public Ownable {
    // Gym would need to roll a dice to determine fees
    Dice dice;
    int numOfOwners = 0;
    public:
        Gym(int position, std::string name, std::string block, std::string type, int cost);

        int getFees(int rolls);

        void addOwners(int numberOfOwners);

        void accept(Player& p) override;
};

#endif
