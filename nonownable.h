#ifndef NONOWNABLE_H
#define NONOWNABLE_H
#include "boardsquare.h"
#include <string>

class Player;

class NonOwnable: public BoardSquare {
    public:
        NonOwnable(int position, std::string name, std::string type);
        void virtual accept(Player& p) = 0;
};

#endif 
