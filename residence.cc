#include "residence.h"
#include "player.h"
#include <iostream>
#include "subject.h"
#include "observer.h"
#include "gamestate.h"
using namespace std;

Residence::Residence(int position, std::string name, std::string block, std::string type, int cost, int oneRent, int twoRent, int threeRent, int fourRent):
    Ownable{position, name, block, type, cost} {
        rent[0] = oneRent;
        rent[1] = twoRent;
        rent[2] = threeRent;
        rent[3] = fourRent;
}

// need to implement. Calculates the rent based on the conditions
int Residence::getRent() {
    return rent[numOfOwners - 1];
}

// logic that depends on the number of owners. Setting owners can be done through player
void Residence::accept(Player& p)  {
     // notifies view that the player has moved to this square
    GameState gs {MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();

    if (getOwner() == ' ') {
        // logic for prompting purchase
        GameState gs {MessageType::emptyOwnable, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
        setState(gs);
        notifyObservers();
    } else if (getOwner() != p.getPiece()) {
        if (isMortgaged()) return;
        int rentOwed = getRent();
        if (p.getMoney() < rentOwed) {
            // notify controller of possible bankruptcy
            // ...
            GameState gs{MessageType::Bankruptcy, p.getPiece(), 'K', rentOwed};
            setState(gs);
            notifyObservers();
        } else {
            p.payMoney(rentOwed);
            // maybe notify view, but this is easier
            cout << "You paid " << rentOwed << " to " << getOwner() << endl;
        }
    }    
}

void Residence::addOwners(int numberOfOwners) {
    numOfOwners = numberOfOwners;
}
