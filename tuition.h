#ifndef TUITION_H
#define TUITION_H
#include "nonownable.h"

class Player;

class Tuition: public NonOwnable {
    public:
        Tuition(int position, std::string name, std::string type);
        void accept(Player& p) override;
};

#endif
