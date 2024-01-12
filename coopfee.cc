#include "coopfee.h"
#include "player.h"
#include "gamestate.h"
#include "observer.h"
#include "subject.h"
#include <iostream>

using namespace std;

CoopFee::CoopFee(int position, string name, string type, int fees): NonOwnable{position, name, type}, fees{fees} {};

// The player pays the fees to the bank
void CoopFee::accept(Player& p) {
    // notifies the view that the player has landed on this square
    // ...
    // notifies view that the player has moved to this square
    GameState gs {MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();
    
    if (p.getMoney() < fees) {
        // notify controller of possible bankruptcy
        GameState gs{MessageType::Bankruptcy, p.getPiece(), 'K', fees};
        setState(gs);
        notifyObservers();
    } else {
        cout << "You paid 150$ in coops fees to the school" << endl;
        p.payMoney(fees);
    }
}
