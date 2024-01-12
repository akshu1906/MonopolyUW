#include "gototims.h"
#include "gamestate.h"
#include "observer.h"
#include "subject.h"

using namespace std;

GoToTims::GoToTims(int position, string name, string type): NonOwnable{position, name, type} {}


// Handles the logic of moving the player to the tims line
void GoToTims::accept(Player& p) {
    // notify the screen and controller that the player is now in line
    // ...
    GameState gs {MessageType::GoToTims};
    setState(gs);
    notifyObservers();
}
