#ifndef GOOSENESTING_H
#define GOOSENESTING_H

#include "nonownable.h"

class Player;

class GooseNesting: public NonOwnable {
    public:
        GooseNesting(int position, std::string name, std::string type);

        void accept(Player& p) override;
};

#endif
