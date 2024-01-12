#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "ownable.h"
#include <string>

class Residence: public Ownable {
    int numOfOwners = 0;
    int rent[4];

    // calculates the rent owed
    int getRent();
    public:
        Residence(int position, std::string name, std::string block, std::string type, int cost, int oneRent, int twoRent, int threeRent, int fourRent);

        void accept(Player& p) override;

        void addOwners(int numberOfOwners);
};

#endif
