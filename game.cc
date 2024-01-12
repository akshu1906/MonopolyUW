#include "game.h"
#include "academic.h"
#include "collectosap.h"
#include "controller.h"
#include "view.h"
#include "player.h"
#include "slc.h"
#include "tuition.h"
#include "residence.h"
#include "needleshall.h"
#include "timsline.h"
#include "gym.h"
#include "goosenesting.h"
#include "gototims.h"
#include "coopfee.h"
#include "observer.h"
#include "subject.h"
#include "gamestate.h"
#include <iostream>
using namespace std;

void Game::init(Controller* c, View* v) {
    gameboard.emplace_back(make_shared<CollectOSAP>(0, "COLLECTOSAP", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(1, "AL", "Arts1", "ownable", 40, 50, 0, 2, 10, 30, 90, 160, 250));
    gameboard.emplace_back(make_shared<SLC>(2, "SLC", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(3, "ML", "Arts1", "ownable", 60, 50, 0, 4, 20, 60, 180, 320, 450));
    gameboard.emplace_back(make_shared<Tuition>(4, "TUITION", "nonownable"));
    gameboard.emplace_back(make_shared<Residence>(5, "MKV", "Residence", "ownable", 200, 25, 50, 100, 200));
    gameboard.emplace_back(make_shared<Academic>(6, "ECH", "Arts2", "ownable", 100, 50, 0, 6, 30, 90, 270, 400, 550));
    gameboard.emplace_back(make_shared<NeedlesHall>(7, "NEEDLESHALL", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(8, "PAS", "Arts2", "ownable", 100, 50, 0, 6, 30, 90, 270, 400, 550));
    gameboard.emplace_back(make_shared<Academic>(9, "HH", "Arts2", "ownable", 120, 50, 0, 8, 40, 100, 300, 450, 600));
    gameboard.emplace_back(make_shared<TimsLine>(10, "TIMSLINE", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(11, "RCH", "Eng", "ownable", 140, 100, 0, 10, 50, 150, 450, 625, 750));
    gameboard.emplace_back(make_shared<Gym>(12, "PAC", "Gym", "ownable", 150));
    gameboard.emplace_back(make_shared<Academic>(13, "DWE", "Eng", "ownable", 140, 100, 0, 10, 50, 150, 450, 625, 750));
    gameboard.emplace_back(make_shared<Academic>(14, "CPH", "Eng", "ownable", 160, 100, 0, 12, 60, 180, 500, 700, 900));
    gameboard.emplace_back(make_shared<Residence>(15, "UWP", "Residence", "ownable", 200, 25, 50, 100, 200));
    gameboard.emplace_back(make_shared<Academic>(16, "LHI", "Health", "ownable", 180, 100, 0, 14, 70, 200, 550, 750, 950));
    gameboard.emplace_back(make_shared<SLC>(17, "SLC", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(18, "BMH", "Health", "ownable", 180, 100, 0, 14, 70, 200, 550, 750, 950));
    gameboard.emplace_back(make_shared<Academic>(19, "OPT", "Health", "ownable", 200, 100, 0, 16, 80, 220, 600, 800, 1000));
    gameboard.emplace_back(make_shared<GooseNesting>(20, "GOOSENESTING", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(21, "EV1", "Env", "ownable", 220, 150, 0, 18, 90, 250, 700, 875, 1050));
    gameboard.emplace_back(make_shared<NeedlesHall>(22, "NEEDLESHALL", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(23, "EV2", "Env", "ownable", 220, 150, 0, 18, 90, 250, 700, 875, 1050));
    gameboard.emplace_back(make_shared<Academic>(24, "EV3", "Env", "ownable", 240, 150, 0, 20, 100, 300, 750, 925, 1100));
    gameboard.emplace_back(make_shared<Residence>(25, "V1", "Residence", "ownable", 200, 25, 50, 100, 200));
    gameboard.emplace_back(make_shared<Academic>(26, "PHYS", "Sci1", "ownable", 260, 150, 0, 22, 110, 330, 800, 975, 1150));
    gameboard.emplace_back(make_shared<Academic>(27, "B1", "Sci1", "ownable", 260, 150, 0, 22, 110, 330, 800, 975, 1150));
    gameboard.emplace_back(make_shared<Gym>(28, "CIF", "Gym", "ownable", 150));
    gameboard.emplace_back(make_shared<Academic>(29, "B2", "Sci1", "ownable", 280, 150, 0, 24, 120, 360, 850, 1025, 1200));
    gameboard.emplace_back(make_shared<GoToTims>(30, "GOTOTIMS", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(31, "EIT", "Sci2", "ownable", 300, 200, 0, 26, 130, 390, 900, 1100, 1275));
    gameboard.emplace_back(make_shared<Academic>(32, "ESC", "Sci2", "ownable", 300, 200, 0, 26, 130, 390, 900, 1100, 1275));
    gameboard.emplace_back(make_shared<SLC>(33, "SLC", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(34, "C2", "Sci2", "ownable", 320, 200, 0, 28, 150, 450, 1000, 1200, 1400));
    gameboard.emplace_back(make_shared<Residence>(35, "REV", "Residence", "ownable", 200, 25, 50, 100, 200));
    gameboard.emplace_back(make_shared<NeedlesHall>(36, "NEEDLESHALL", "nonownable"));
    gameboard.emplace_back(make_shared<Academic>(37, "MC", "Math", "ownable", 350, 200, 0, 35, 175, 500, 1100, 1300, 1500));
    gameboard.emplace_back(make_shared<CoopFee>(38, "COOPFEE", "nonownable", 150));
    gameboard.emplace_back(make_shared<Academic>(39, "DC", "Math", "ownable", 400, 200, 0, 50, 200, 600, 1400, 1700, 2000));
    for (size_t i = 0; i < gameboard.size(); i++) {
        gameboard[i]->attach(v);
        gameboard[i]->attach(c);
    }
}

int Game::roll() {
    return dice.roll();
}

void Game::disableRoll() {
    players[currentPlayer].disableRoll();
}

void Game::enableRoll() {
    players[currentPlayer].enableRoll();
}

// Add a player to the game
void Game::addPlayer(string name, char piece, int turn, int money, int rimCups) {
    players.emplace_back(Player{name, piece, turn, money, rimCups});
    numOfPlayers++;
}

void Game::payPlayerMoney(int whichPlayer, int amount) {
    players[whichPlayer].payMoney(amount);

}

void Game::gainPlayerMoney(int whichPlayer, int amount) {
    players[whichPlayer].gainMoney(amount);
}

void Game::setPlayerPosition(int whichPlayer, int position) {
    players[whichPlayer].setPosition(position);
}

void setBuildingOwner(int whichPlayer, int whichBuilding);

// Moves the player the number of moves
void Game::movePlayer(int moves) {
    if (moves > 0) {
        if ((getCurrentPosition() + moves) >= 40) {
            cout << "You collect 200$ from OSAP!" << endl;
            players[currentPlayer].gainMoney(200);
        }
        players[currentPlayer].advance(moves);
    } else {
        players[currentPlayer].back(moves);
    }
    int newSquare = getCurrentPosition();
    string squareName = gameboard[newSquare]->getName();
    if (squareName == "SLC" || squareName == "NEEDLESHALL") {
        if (rimCupsLeft > 0) {
            int probability = rand()% 100 + 1;
            if (probability == 1) {
                GameState gs {MessageType::NewMove, players[currentPlayer].getPiece(), newSquare, currentPlayer, squareName};
                setState(gs);
                notifyObservers();
                cout << "WHOOHOO! You won a Roll up the Rim Cup!" << endl;
                players[currentPlayer].receiveRimCup();
                return;
            }
        }
    } 
    gameboard[newSquare]->accept(players[currentPlayer]);
}

// Switches to the next player
void Game::nextPlayer() {
    currentPlayer++;
    if (currentPlayer >= numOfPlayers) {
        currentPlayer = 0;
    }
}

// Checks if the current player is in the DC Tims Line
bool Game::isInLine() {
    return players[currentPlayer].isInTims();
}

bool Game::isInLine(int whichPlayer) {
    return players[whichPlayer].isInTims();
}

// Moves the current player to the DC Tims Line
void Game::goToTimsLine() {
    players[currentPlayer].goToTimsLine();
    gameboard[10]->accept(players[currentPlayer]);
}

void Game::goToTimsLine(int whichPlayer) {
    players[whichPlayer].goToTimsLine();
}

void Game::outOfTimsLine() {
    players[currentPlayer].outOfTims();
}

void Game::outOfTimsLine(int whichPlayer) {
    players[whichPlayer].outOfTims();
}

void Game::goToOSAP() {
    players[currentPlayer].goToOSAP();
    gameboard[0]->accept(players[currentPlayer]);
    cout << "You collected 200$" << endl;
}

// Checks if the current player can roll
bool Game::canRoll() {
    return players[currentPlayer].canRollAgain();
}

// Removes a player from the player list

// // TO CHANGE
// void Game::dropout(int whichPlayer) {
//     players.erase(players.begin() + whichPlayer);
//     numOfPlayers--;
//     // other logic
// }

void Game::bankruptPlayer(int whichPlayer) {
    players[whichPlayer].goesBankrupt();
}

bool Game::isPlayerBankrupt(int whichPlayer) {
    return players[whichPlayer].stillInPlay();
}

// LineState Game::getLineState() {
//     return players[currentPlayer].getLineState();
// }

int Game::getTimsLineTurn() {
    return players[currentPlayer].getTimsLineTurn();
}

int Game::getTimsLineTurn(int whichPlayer) {
    return players[whichPlayer].getTimsLineTurn();
}

int Game::getRimCups(int whichPlayer) {
    return players[whichPlayer].getRimCups();
}

void Game::reduceRimCups() {
    players[currentPlayer].reduceRimCup();
}

void Game::setTimsLineTurn(int num) {
    players[currentPlayer].setTimsLineTurn(num);
}

void Game::setTimsLineTurn(int whichPlayer, int num) {
    players[whichPlayer].setTimsLineTurn(num);
}

int Game::getCost(int whichBuilding) {
    return gameboard[whichBuilding]->getCost();
}

// Returns the current player's position on the board
int Game::getCurrentPosition() {
    return players[currentPlayer].getPosition();
}

int Game::getPlayerPosition(int whichPlayer) {
    return players[whichPlayer].getPosition();
}

// Return the name of the current player's square on the board
string Game::getCurrentSquare() {
    int square = getCurrentPosition();
    return gameboard[square]->getName();
}

string Game::getSquare(int whichBuilding) {
    return gameboard[whichBuilding]->getName();
}

char Game::getPlayerPiece(int whichPlayer) {
    return players[whichPlayer].getPiece();
}

string Game::getPlayerName(int whichPlayer) {
    return players[whichPlayer].getName();
}

bool Game::checkMonopoly(int whichPlayer, int whichBuilding) {
    return players[whichPlayer].hasMonoply(gameboard[whichBuilding]->getBlock());
}

// Checks if the current square is an "ownable" square and has no owners
bool Game::propertyCanBeOwned() {
    int square = getCurrentPosition();
    if (gameboard[square]->getType() == "ownable") {
        return static_pointer_cast<Ownable>(gameboard[square])->getOwner() == ' ';
    }
    return false;
}

// Checks if a given building derives from the ownable class
bool Game::propertyIsOwnable(int whichBuilding) {
    return gameboard[whichBuilding]->getType() == "ownable";
}

// Checks if the current player has enough money to buy the current square
bool Game::canBuyProperty() {
    int square = getCurrentPosition();
    return getPlayerMoney(currentPlayer) >= gameboard[square]->getCost();
}

// Returns the amount of money that a player has
int Game::getPlayerMoney(int whichPlayer) {
    return players[whichPlayer].getMoney();
}

int Game::getPlayerNetworth(int whichPlayer) {
    return players[whichPlayer].getNetworth();
}

// The current player buys the property
void Game::buyProperty() {
    int currentSquare = getCurrentPosition();
    BoardState bs = gameboard[currentSquare]->getBoardState();
    players[currentPlayer].addBuilding(currentSquare, bs.name, bs.block, bs.cost);
    static_pointer_cast<Ownable>(gameboard[currentSquare])->setOwner(players[currentPlayer].getPiece());
    players[currentPlayer].payMoney(bs.cost);
    updateBlock(currentPlayer, gameboard[currentSquare]->getBlock());

    // notify view that current player has bought property
    GameState gs{MessageType::NewProperty, players[currentPlayer].getPiece(), currentSquare};
    setState(gs);
    notifyObservers();
}

// // A player buys the square number (IN PROGRESS DEBATABLE)
// void Game::buyProperty(int whichPlayer, int squareNumber) {
//     BoardState bs = gameboard[squareNumber]->getBoardState();
//     players[whichPlayer].addBuilding(squareNumber, bs.name, bs.block, bs.cost);


//     // notify view that player has bought property
    
// }

void Game::winAuction(int whichPlayer, int squareNumber, int bidAmount) {
    BoardState bs = gameboard[squareNumber]->getBoardState();
    players[whichPlayer].addBuilding(squareNumber, bs.name, bs.block, bs.cost);
    static_pointer_cast<Ownable>(gameboard[squareNumber])->setOwner(getPlayerPiece(whichPlayer));
    players[whichPlayer].payMoney(bidAmount);
    updateBlock(whichPlayer, gameboard[squareNumber]->getBlock());

    // notify view that current player has bought property
    GameState gs{MessageType::NewProperty, players[whichPlayer].getPiece(), squareNumber};
    setState(gs);
    notifyObservers();
}

void Game::resetBuilding(int whichBuilding) {
    auto o = dynamic_pointer_cast<Ownable>(gameboard[whichBuilding]);
    if (o) {
        if (o->isMortgaged()) {
            o->unmortgageProperty();
            GameState gs{MessageType::Unmortgage, gameboard[whichBuilding]->getPosition()};
            setState(gs);
            notifyObservers();

        }
        auto a = dynamic_pointer_cast<Academic>(gameboard[whichBuilding]);
        if (a) {
            if (a->getNumberOfImprovements() > 0) {
                a->resetImprovements();
                GameState gs2{MessageType::ResetImprovements, gameboard[whichBuilding]->getPosition()};
                setState(gs2);
                notifyObservers();
            }
        }   
    }
}

BoardState Game::getBuildingState(int whichBuilding) {
    return gameboard[whichBuilding]->getBoardState();
}

string Game::getBuildingName(int whichBuidling) {
    return gameboard[whichBuidling]->getName();
}

char Game::getBuildingOwner(int whichBuilding) {
    return static_pointer_cast<Ownable>(gameboard[whichBuilding])->getOwner();
}

// Returns the square number of a give building name
int Game::getBuildingIndex(string name) {
    for (int i = 0; i < 40; i++) {
        if (gameboard[i]->getName() == name) return i;
    }
    return -1;
}

 void Game::addPropertyToPlayer(int whichPlayer, int squareNumber) {
    BoardState bs = gameboard[squareNumber]->getBoardState();
    players[whichPlayer].addBuilding(bs.position, bs.name, bs.block, bs.cost);
    static_pointer_cast<Ownable>(gameboard[squareNumber])->setOwner(players[whichPlayer].getPiece());
    updateBlock(whichPlayer, bs.block);
    
    // notify view of the added building
    GameState gs{MessageType::NewProperty, players[whichPlayer].getPiece(), squareNumber};
    setState(gs);
    notifyObservers();

 }

void Game::setImprovements(int whichBuilding, int improvements) {
    static_pointer_cast<Academic>(gameboard[whichBuilding])->setImprovements(improvements);
}

void Game::getPlayerProperties(std::vector<int>& properties, int whichPlayer) {
    vector<int> tempProp;
    players[whichPlayer].returnAllProperties(tempProp);
    for (int p  : tempProp) {
        properties.emplace_back(p);
    }
}

// Checks if a player owns a building
bool Game::ownsProperty(int whichPlayer, int whichBuilding) {
    return static_pointer_cast<Ownable>(gameboard[whichBuilding])->getOwner() == players[whichPlayer].getPiece();
}

// Checks if the building is an academic building and if it has improvements
bool Game::hasImprovements(int whichBuilding) {
    if (isAcademic(whichBuilding)) {
        return static_pointer_cast<Academic>(gameboard[whichBuilding])->getNumberOfImprovements() > 0;
    } else {
        return false;
    }
}

// Returns true if the building is an academic building
bool Game::isAcademic(int whichBuilding) {
    auto a = dynamic_pointer_cast<Academic>(gameboard[whichBuilding]);
    if (a) {
        return true;
    } else {
        return false;
    }
}

bool Game::isMortgaged(int whichBuilding) {
    return static_pointer_cast<Ownable>(gameboard[whichBuilding])->isMortgaged();
}

int Game::getImprovements(int whichBuilding) {
    return static_pointer_cast<Academic>(gameboard[whichBuilding])->getNumberOfImprovements();
}

int Game::getImplementationCost(int whichBuilding) {
    return static_pointer_cast<Academic>(gameboard[whichBuilding])->getImprovementCost();
}


// For the trade prompt, check if a given building has improvements or any properties in the monopoly has improvements
bool Game::monopolyHasImprovements(int whichBuilding) {
    if (isAcademic(whichBuilding)) {
        if (hasImprovements(whichBuilding)) {
            return true;
        } else if (static_pointer_cast<Academic>(gameboard[whichBuilding])->isInMonopoly()) {
            string block = gameboard[whichBuilding]->getBlock();
            for (int i = 0; i < 40; i++) {
                if (gameboard[i]->getBlock() == block) {
                    if (hasImprovements(i)) return true;
                }
            }
            return false;
        } else {
            return false;
        }
    } else {
        return false;
    }

}

// void canBuyImprovement();


// Buy an improvement for a player's building
void Game::buyImprovement(int whichPlayer, int whichBuilding) {
    static_pointer_cast<Academic>(gameboard[whichBuilding])->addImprovement();
    int cost = getImplementationCost(whichBuilding);
    players[whichPlayer].payMoney(cost);

    // sends a notification
    GameState gs{MessageType::NewImprovement, gameboard[whichBuilding]->getPosition()};
    setState(gs);
    notifyObservers();
}

// Sell a player's building's improvement
void Game::sellImprovement(int whichPlayer, int whichBuilding) {
    static_pointer_cast<Academic>(gameboard[whichBuilding])->reduceImprovement();
    int halfCost = getImplementationCost(whichBuilding) / 2;
    players[whichPlayer].gainMoney(halfCost);

    // sends a notification
    GameState gs{MessageType::RemoveImprovement, gameboard[whichBuilding]->getPosition()};
    setState(gs);
    notifyObservers();
}


void Game::mortgage(int whichPlayer, int whichBuilding) {
    int sellBackPrice = getCost(whichBuilding) / 2;
    players[whichPlayer].gainMoney(sellBackPrice);
    static_pointer_cast<Ownable>(gameboard[whichBuilding])->mortgageProperty();
    
    GameState gs{MessageType::Mortgage, gameboard[whichBuilding]->getPosition()};
    setState(gs);
    notifyObservers();
}

void Game::setPropertyMortgaged(int whichBuilding) {
    static_pointer_cast<Ownable>(gameboard[whichBuilding])->mortgageProperty();
    
    GameState gs{MessageType::Mortgage, gameboard[whichBuilding]->getPosition()};
    setState(gs);
    notifyObservers();
}

void Game::unmortgage(int whichPlayer, int whichBuilding, bool immediate) {
    int fees;
    if (immediate) {
        fees = getCost(whichBuilding) / 2;
    } else {
        fees = (getCost(whichBuilding) * 3) / 5;
    }
    players[whichPlayer].payMoney(fees);
    static_pointer_cast<Ownable>(gameboard[whichBuilding])->unmortgageProperty();

    GameState gs{MessageType::Unmortgage, gameboard[whichBuilding]->getPosition()};
    setState(gs);
    notifyObservers();
}

// Updates the states of the squares of the same block
void Game::updateBlock(int whichPlayer, string block) {
    if (block == "Residence") {
        vector<int> positions;
        players[whichPlayer].returnBlockPos(positions, block);
        int len = static_cast<int>(positions.size());
        for (int p : positions) {
            static_pointer_cast<Residence>(gameboard[p])->addOwners(len);
        }
    } else if (block == "Gym") {
        vector<int> positions;
        players[whichPlayer].returnBlockPos(positions, block);
        int len = static_cast<int>(positions.size());
        for (int p : positions) {
            static_pointer_cast<Gym>(gameboard[p])->addOwners(len);
        }
    } else {
        vector<int> positions;
        players[whichPlayer].returnBlockPos(positions, block);
        if (positions.size() == 0) return;
        if (players[whichPlayer].hasMonoply(block)) {
            for (int p : positions) {
                static_pointer_cast<Academic>(gameboard[p])->changeMonopoly(true);
            }
        } else {
            for (int p : positions) {
                static_pointer_cast<Academic>(gameboard[p])->changeMonopoly(false);
            }
        }
    }

}

void Game::transferAssets(int fromWho, int toWho) {
    vector<int> propertiesToGive;
    players[fromWho].returnAllProperties(propertiesToGive);
    for (int p : propertiesToGive) {
        // logic for transfering
        BoardState bs = gameboard[p]->getBoardState();
        players[fromWho].removeBuilding(bs.name, bs.block, bs.cost);
        players[toWho].addBuilding(p, bs.name, bs.block, bs.cost);

        // Change owners
        static_pointer_cast<Ownable>(gameboard[p])->setOwner(players[toWho].getPiece());

        updateBlock(fromWho, bs.block);
        updateBlock(toWho, bs.block);

        GameState gs{MessageType::NewProperty, players[toWho].getPiece(), p};
        setState(gs);
        notifyObservers();
    }

    // logic for mortgaged properties
    for (int p : propertiesToGive) {
        if (isMortgaged(p)) {
            GameState gs{MessageType::ReceiveMortgage, players[toWho].getPiece(), p};
            setState(gs);
            notifyObservers();
        }
        if (isPlayerBankrupt(toWho)) {
            return;
        }
    }

}

void Game::trade(int fromWho, int toWho, int amountOffered, string buildingReceived) {
    int whichBuilding = getBuildingIndex(buildingReceived);
    BoardState bs = gameboard[whichBuilding]->getBoardState();
    players[fromWho].payMoney(amountOffered);
    players[toWho].gainMoney(amountOffered);
    players[toWho].removeBuilding(bs.name, bs.block, bs.cost);
    players[fromWho].addBuilding(whichBuilding, bs.name, bs.block, bs.cost);

    // Change owner
    static_pointer_cast<Ownable>(gameboard[whichBuilding])->setOwner(players[fromWho].getPiece());
    updateBlock(toWho, bs.block);
    updateBlock(fromWho, bs.block);

    // notify new building
    GameState gs{MessageType::NewProperty, players[fromWho].getPiece(), whichBuilding};
    setState(gs);
    notifyObservers();


    // if building is mortgaged prompt mortgage
    if (isMortgaged(whichBuilding)) {
        GameState gs{MessageType::ReceiveMortgage, players[fromWho].getPiece(), whichBuilding};
        setState(gs);
        notifyObservers();
    }
}

void Game::trade(int fromWho, int toWho, string buildingOffered, int amountReceived) {
    int whichBuilding = getBuildingIndex(buildingOffered);
    BoardState bs = gameboard[whichBuilding]->getBoardState();
    players[fromWho].gainMoney(amountReceived);
    players[toWho].payMoney(amountReceived);
    players[fromWho].removeBuilding(bs.name, bs.block, bs.cost);
    players[toWho].addBuilding(whichBuilding, bs.name, bs.block, bs.cost);

    // Change owner
    static_pointer_cast<Ownable>(gameboard[whichBuilding])->setOwner(players[toWho].getPiece());
    updateBlock(fromWho, bs.block);
    updateBlock(toWho, bs.block);
    // notify new building
    GameState gs{MessageType::NewProperty, players[toWho].getPiece(), whichBuilding};
    setState(gs);
    notifyObservers();



    // if building is mortgaged prompt mortgage
    if (isMortgaged(whichBuilding)) {
        GameState gs{MessageType::ReceiveMortgage, players[toWho].getPiece(), whichBuilding};
        setState(gs);
        notifyObservers();
    }
}

void Game::trade(int fromWho, int toWho, string buildingOffered, string buildingReceived) {
    int whichBuildingOffered = getBuildingIndex(buildingOffered);
    int whichBuildingReceived = getBuildingIndex(buildingReceived);
    BoardState bsOffered = gameboard[whichBuildingOffered]->getBoardState();
    BoardState bsReceived = gameboard[whichBuildingReceived]->getBoardState();
    players[fromWho].removeBuilding(bsOffered.name, bsOffered.block, bsOffered.cost);
    players[toWho].addBuilding(whichBuildingOffered, bsOffered.name, bsOffered.block, bsOffered.cost);
    players[toWho].removeBuilding(bsReceived.name, bsReceived.block, bsReceived.cost);
    players[fromWho].addBuilding(whichBuildingReceived, bsReceived.name, bsReceived.block, bsReceived.cost);


    // Change owners
    static_pointer_cast<Ownable>(gameboard[whichBuildingOffered])->setOwner(players[toWho].getPiece());
    static_pointer_cast<Ownable>(gameboard[whichBuildingReceived])->setOwner(players[fromWho].getPiece());
    updateBlock(fromWho, bsOffered.block);
    updateBlock(toWho, bsOffered.block);
    updateBlock(toWho, bsReceived.block);
    updateBlock(fromWho, bsReceived.block);


    // notify new building
    GameState gs{MessageType::NewProperty, players[toWho].getPiece(), whichBuildingOffered};
    setState(gs);
    notifyObservers();

    GameState gs2{MessageType::NewProperty, players[fromWho].getPiece(), whichBuildingReceived};
    setState(gs2);
    notifyObservers();

    // Logic if any of the buildings is mortgaged
    if (isMortgaged(whichBuildingReceived)) {
        GameState gs{MessageType::ReceiveMortgage, players[fromWho].getPiece(), whichBuildingReceived};
        setState(gs);
        notifyObservers();
    }
    if (isMortgaged(whichBuildingOffered)) {
        GameState gs{MessageType::ReceiveMortgage, players[toWho].getPiece(), whichBuildingOffered};
        setState(gs);
        notifyObservers();
    }
}

