#include "gym.h"
#include "player.h"
#include <iostream>
#include "subject.h"
#include "observer.h"
#include "gamestate.h"
using namespace std;

Gym::Gym(int position, std::string name, std::string block, std::string type, int cost):
    Ownable{position, name, block, type, cost} {}

int Gym::getFees(int rolls) {
    if (numOfOwners == 1) {
        return rolls * 4;
    } else {
        return rolls * 10;
    }
}

// logic that rolls a dice and determines the fees that a player has to pay
void Gym::accept(Player& p)  {
    // notify the view that the player has landed here
    // ...
     // notifies view that the player has moved to this square
    GameState gs {MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();

    if (getOwner() == ' ') {
        // no one owns the square
        GameState gs {MessageType::emptyOwnable, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
        setState(gs);
        notifyObservers();
    } else if (getOwner() != p.getPiece()) {
        if (isMortgaged()) return;
        int roll1 = dice.roll();
        int roll2 = dice.roll();
        cout << "You rolled a " << roll1 << " and a " << roll2 << endl;
        int feesOwed = getFees(roll1 + roll2);

        if (p.getMoney() < feesOwed) {
            // notify the controller of a possible bankruptcy
            GameState gs{MessageType::Bankruptcy, p.getPiece(), getOwner(), feesOwed};
            setState(gs);
            notifyObservers();
        } else {
            p.payMoney(feesOwed);
            GameState gs{MessageType::Payment, p.getPiece(), getOwner(), feesOwed};
            setState(gs);
            notifyObservers();
            
        }
    } 
}

void Gym::addOwners(int numberOfOwners) {
    numOfOwners = numberOfOwners;
}
