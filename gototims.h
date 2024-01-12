#ifndef GOTOTIMS_H
#define GOTOTIMS_H

#include "nonownable.h"
#include "player.h"

class GoToTims: public NonOwnable {
    public:
        GoToTims(int position, std::string name, std::string type);
        void accept(Player& p) override;
};

#endif
