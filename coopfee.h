#ifndef COOPFEE_H
#define COOPFEE_H

#include "nonownable.h"

class CoopFee: public NonOwnable {
    int fees;
    public:
        CoopFee(int position, std::string name, std::string type, int fees);
        void accept(Player& p) override;
};

#endif
