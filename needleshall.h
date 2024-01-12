#ifndef NEEDLESHALL_H
#define NEEDLESHALL_H
#include "nonownable.h"

class Player;

class NeedlesHall: public NonOwnable {
    public:
        NeedlesHall(int position, std::string name, std::string type);

        void accept(Player& p) override;
};

#endif
