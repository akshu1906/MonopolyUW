#include "ownable.h"
using namespace std;

void Ownable::setOwner(char owner) {
    this->owner = owner;
}

char Ownable::getOwner() {
    return owner;
}

Ownable::Ownable(int position, string name, string block, string type, int cost):
    BoardSquare{position, name, block, type, cost} {}


bool Ownable::isMortgaged() {
    return mortgaged;
}

void Ownable::mortgageProperty() {
    mortgaged = true;
}

void Ownable::unmortgageProperty() {
    mortgaged = false;
}
