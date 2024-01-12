#ifndef OWNABLE_H
#define OWNABLE_H

#include <string>
#include "boardsquare.h"

class Ownable: public BoardSquare {
    protected:
        char owner = ' ';
        bool mortgaged = false;
    public:
        Ownable(int position, std::string name, std::string block, std::string type, int cost);

        char getOwner();

        void setOwner(char owner);

        void virtual accept(Player& p) = 0;

        bool isMortgaged();

        void mortgageProperty();

        void unmortgageProperty();
};

#endif 
