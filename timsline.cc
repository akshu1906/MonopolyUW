#include "timsline.h"
#include "player.h"
#include "gamestate.h"
#include "observer.h"
#include "subject.h"

using namespace std;

TimsLine::TimsLine(int position, string name, string type): NonOwnable{position, name, type} {}


// Should not do anything for now. Logic is handled in controller/game?
void TimsLine::accept(Player& p) {
    // Notifies that the player has landed on the square
    GameState gs {MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();
}
