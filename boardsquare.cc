#include "boardsquare.h"
using namespace std;

BoardSquare::BoardSquare(int position, string name, string block, string type, int cost): 
    position{position}, name{name}, block{block}, type{type}, cost{cost} {}

BoardSquare::BoardSquare(int position, string name, string type): 
    position{position}, name{name}, type{type}, cost{0} {}


int BoardSquare::getPosition() {
    return position;
}

string BoardSquare::getType() {
    return type;
}

string BoardSquare::getBlock() {
    return block;
}

string BoardSquare::getName() {
    return name;
}

int BoardSquare::getCost() {
    return cost;
}

BoardState BoardSquare::getBoardState() {
    return BoardState{position, name, block,type, cost};
}
