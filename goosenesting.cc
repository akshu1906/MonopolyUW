#include "goosenesting.h"
#include "player.h"
#include "gamestate.h"
#include "observer.h"
#include "subject.h"
#include <iostream>
using namespace std;

GooseNesting::GooseNesting(int position, string name, string type): NonOwnable{position, name, type} {};

// Nothing happens yet! Just a print statement! It does notify the view that position has changed.
void GooseNesting::accept(Player& p) {
    // notify the view that the player has landed on this square
    // ...
    GameState gs {MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();
    
    cout << "You have been attacked by geese! Fortunately you know geese jujutsu!" << endl;
}
