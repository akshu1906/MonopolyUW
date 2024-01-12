#include "needleshall.h"
#include "player.h"
#include "gamestate.h"
#include "observer.h"
#include "subject.h"
#include <iostream>
using namespace std;

NeedlesHall::NeedlesHall(int position, string name, string type): NonOwnable{position, name, type} {};


// some logic to give player money according to the probabilities
void NeedlesHall::accept(Player& p) {
    // Notifies the view that the player has landed here
    GameState gs {MessageType::NewMove, p.getPiece(), p.getPosition(), p.getTurn(), getName()};
    setState(gs);
    notifyObservers();
    
    int random = rand()% 18 + 1;
    if(random == 1){
        if (p.getMoney() < 200) {
            // notify of bankruptcy
            GameState gs{MessageType::Bankruptcy, p.getPiece(), 'K', 200};
            setState(gs);
            notifyObservers();

        } else {
            cout<<"You lose $200." <<endl;
            p.payMoney(200);
        }
    } else if (random <= 3){
        if (p.getMoney() < 100) {
            // notify of bankruptcy
            GameState gs{MessageType::Bankruptcy, p.getPiece(), 'K', 100};
            setState(gs);
            notifyObservers();
        } else {
            cout<<"you lose $100." <<endl;
            p.payMoney(100);
        }
    } else if (random <= 6){
        if (p.getMoney() < 50) {
            // notify of bankruptcy
            GameState gs{MessageType::Bankruptcy, p.getPiece(), 'K', 50};
            setState(gs);
            notifyObservers();
        } else {
            cout<<"you lose $50." <<endl;
            p.payMoney(50);
        }
    } else if (random <= 12){
        cout<<"you gain $25." <<endl;
        p.gainMoney(25);
    } else if (random <= 15){
        cout<<"you gain $50." <<endl;
        p.gainMoney(50);
    } else if (random <= 17){
        cout<<"you gain $100." <<endl;
        p.gainMoney(100);
    } else{
        cout<<"you gain $200." <<endl;
        p.gainMoney(200);
    }
}
