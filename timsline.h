#ifndef TIMSLINE_H
#define TIMSLINE_H


#include "nonownable.h"
#include <string>

class Player;

class TimsLine: public NonOwnable {
    public:
        TimsLine(int position, std::string name, std::string type);

        void accept(Player& p) override;
};

#endif
