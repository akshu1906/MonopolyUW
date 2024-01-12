#ifndef SLC_H
#define SLC_H

#include "nonownable.h"
#include <string>

class Player;

class SLC: public NonOwnable {
    public:
        SLC(int position, std::string name, std::string type);

        void accept(Player& p) override;
};


#endif
