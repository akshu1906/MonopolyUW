#include "collectosap.h"
#include "player.h"
#include "gamestate.h"
#include "observer.h"
#include "subject.h"
#include <string>

using namespace std;


CollectOSAP::CollectOSAP(int position, string name, string type): NonOwnable{position, name, type} {};

// Shouldn't do anything for now. Logic for collecting osap is in game.h/cc
void CollectOSAP::accept(Player& p) {
    // notifies view that the player has moved to this square
    GameState gs {MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();
    return;
}
