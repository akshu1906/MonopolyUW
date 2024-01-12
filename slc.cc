#include "slc.h"
#include "subject.h"
#include "observer.h"
#include "gamestate.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

SLC::SLC(int position, string name, string type): NonOwnable{position, name, type} {}


// Using the probabilities, moves the player to a square
void SLC::accept(Player& p) {
    // Notifies that view that player landed on SLC
    // notifies view that the player has moved to this square
    GameState gs {MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();


    // logic for moving players
    // srand (time(NULL));
    // int prob = rand()% 100 + 1;
	// if(prob == 1 && p.getRimCups() < 4){
	// 		cout << "WHOOHOO! You won a Roll up the Rim Cup!" << endl;
	// 		p.receiveRimCup();
	// 		return;	
	
    // logic for moving players
    int random = rand()% 24 + 1;
    if (random >= 1 && random <= 3){
        GameState gs {MessageType::SLCMove, p.getPiece(), -3, p.getTurn(), getName()};
        setState(gs);
        cout<< "You moved back 3 steps to ";
        notifyObservers();
    }
    else if (random <= 7) {
        GameState gs {MessageType::SLCMove, p.getPiece(), -2, p.getTurn(), getName()};
        setState(gs);
        cout<< "You moved back 2 steps to ";
        notifyObservers();

    }
    else if (random <= 11){
        GameState gs {MessageType::SLCMove, p.getPiece(), -1, p.getTurn(), getName()};
        setState(gs);
        cout<< "You moved back 1 step to ";
        notifyObservers();
    }
    else if (random <= 14){
        GameState gs {MessageType::SLCMove, p.getPiece(), 1, p.getTurn(), getName()};
        setState(gs);
        cout<< "You moved forward 1 step to ";
        notifyObservers();
    }
    else if (random <= 18){
        GameState gs {MessageType::SLCMove, p.getPiece(), 2, p.getTurn(), getName()};
        setState(gs);
        cout<< "You moved forward 2 steps to ";
        notifyObservers();
    }
    else if (random <= 22){
        GameState gs {MessageType::SLCMove, p.getPiece(), 3, p.getTurn(), getName()};
        setState(gs);
        cout<< "You moved forward 3 steps to ";
        notifyObservers();
    }
    else if (random == 23){
        GameState gs {MessageType::GoToTims};
        setState(gs);
        cout<< "You go to DC Tims line." << endl;
        notifyObservers();
    }
    else{
        GameState gs {MessageType::GoToOSAP};
        setState(gs);
        cout << "You advance to Collect OSAP." << endl;
        notifyObservers();
    }
    return;
}
