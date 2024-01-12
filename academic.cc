#include "academic.h"
#include "boardsquare.h"
#include "ownable.h"
#include "player.h"
#include "subject.h"
#include "observer.h"
#include "gamestate.h"
#include <iostream>
using namespace std;

Academic::Academic(int position, string name, string block, string type, int cost, int implCost, int numOfImprovements,
            int baseTuition, int oneImplTuition, int twoImplTuition, int threeImplTuition,
            int fourImplTuition, int fiveImplTuition):
            Ownable{position, name, block, type, cost}, implCost{implCost}, numOfImprovements{numOfImprovements} {
                tuitions[0] = baseTuition;
                tuitions[1] = oneImplTuition;
                tuitions[2] = twoImplTuition;
                tuitions[3] = threeImplTuition;
                tuitions[4] = fourImplTuition;
                tuitions[5] = fiveImplTuition;
            }

// need to implement. Calculates the tuition owed
int Academic::getTuition() {
    if (numOfImprovements == 0) {
        if (inMonopoly) {
            return tuitions[0] * 2;
        } else {
            return tuitions[0];
        }
    }
    return tuitions[numOfImprovements];
}

int Academic::getNumberOfImprovements() {
    return numOfImprovements;
}

int Academic::getImprovementCost() {
    return implCost;
}

bool Academic::isInMonopoly() {
    return inMonopoly;
}

// bool Academic::isMortgaged() {
//     return mortgaged;
// }

// void Academic::mortgageProperty() {
//     mortgaged = true;
// }

// void Academic::unmortgageProperty() {
//     mortgaged = false;
// }

void Academic::changeMonopoly(bool b) {
    inMonopoly = b;
}

void Academic::accept(Player& p) {
    // notifies view that the player has moved to this square
    GameState gs{MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();

    if (getOwner() == ' ') {
        // send notification to prompt purchase 
        GameState gs {MessageType::emptyOwnable, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
        setState(gs);
        notifyObservers();

    } else if (getOwner() != p.getPiece()) {
        if (mortgaged) return;
        int tuitionOwed = getTuition();
        if (p.getMoney() < tuitionOwed) {
            GameState gs{MessageType::Bankruptcy, p.getPiece(), getOwner(), tuitionOwed};
            setState(gs);
            notifyObservers();
        } else {
            p.payMoney(tuitionOwed);
            // maybe notify view, but this is easier
            GameState gs{MessageType::Payment, p.getPiece(), getOwner(), tuitionOwed};
            setState(gs);
            notifyObservers();
        }
    }
}

// handles the logic of adding improvements for this square 
void Academic::addImprovement() {
    numOfImprovements++;
}

void Academic::setImprovements(int num) {
    numOfImprovements = num;
}

void Academic::reduceImprovement() {
    numOfImprovements--;
}

void Academic::resetImprovements() {
    numOfImprovements = 0;
}
