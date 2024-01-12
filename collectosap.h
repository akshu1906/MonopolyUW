#ifndef COLLECTOSAP_H
#define COLLECTOSAP_H

#include "nonownable.h"

class Player;

class CollectOSAP: public NonOwnable {
    public:
        CollectOSAP(int position, std::string name, std::string type);

        void accept(Player& p) override;
};

#endif
