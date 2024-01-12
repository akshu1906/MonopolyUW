#include "tuition.h"
#include "player.h"
#include "subject.h"
#include "observer.h"
#include "gamestate.h"

using namespace std;

Tuition::Tuition(int position, string name, string type): NonOwnable{position, name, type} {};

void Tuition::accept(Player& p) {
     // notifies view that the player has moved to this square
    GameState gs1{MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs1);
    notifyObservers();

     // notifies controller that the player can choose their method of payment for the tuition
    GameState gs2{MessageType::Tuition};
    setState(gs2);
    notifyObservers();
}
