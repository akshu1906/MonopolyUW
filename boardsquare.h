#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include "subject.h"
#include "gamestate.h"
#include "observer.h"
#include <string>

class Player;

struct BoardState {
    int position;
    std::string name;
    std::string block;
    std::string type;
    int cost;
};

class BoardSquare: public Subject<GameState> {
    protected:
        int position;
        std::string name;
        std::string block;
        std::string type;
        int cost;
    public:
        BoardSquare(int position, std::string name, std::string block, std::string type, int cost);
        BoardSquare(int position, std::string name, std::string type);
        int getPosition();
        std::string getName();
        std::string getType();
        std::string getBlock();
        int getCost();
        BoardState getBoardState();
        void virtual accept(Player& p) = 0;
};

#endif
