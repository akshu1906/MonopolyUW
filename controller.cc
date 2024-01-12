#include "controller.h"
#include "game.h"
#include "view.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

// print player selection choices
void Controller::printPlayers() {
    int rows = 5;
    int columns = 100;
    ifstream file;
    file.open("playerselection.txt");
    char c;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            file.get(c);
            cout << c;
        }
        cout << endl;
    }
    file.close();
}

// initializes the controller by creating the view and the game
void Controller::launch(bool testing, bool loading, string savefile) {
    view.init();
    g.init(this, &view);
    this->testing = testing;
    g.attach(this);
    g.attach(&view);
    if (loading) {
        loadGame(savefile);
    } else {
        selectPlayers();
    }
    view.printBoard();
    play();
}


// starts the game. Expects players' inputs (commands)
void Controller::play() {
    // cout << "Enter i to receive list of commands" << endl;
    while (!gameIsWon) {
        try {  
            // if player is in line prompt them
            if (g.isInLine()) {
                cout << "You are in the DC Tims Line" << endl;
                cout << "As a reminder, you can either roll, pay 50$ [pay] or use a Roll Up the Rim cup [use] to get out" << endl;
            }
            string cmdline;
            cout << names[turn] << ", please enter a command:" << endl;  
            getline(cin >> ws, cmdline);
            string cmd;
            istringstream iss{cmdline};
            iss.exceptions(ios::failbit);
            iss >> cmd;
            if (cmd == "roll") {
                if (g.canRoll()) {
                    int move1;
                    int move2;
                    // logic for testing mode
                    if (testing) {
                        try {
                            iss >> move1;
                            iss >> move2;
                        } catch (...) {
                            move1 = g.roll();
                            move2 = g.roll();
                        }
                        if (move1 < 0 || move2 < 0) {
                            throw invalidInput{};
                        }
                    } else {
                        move1 = g.roll();
                        move2 = g.roll();
                    }
                    cout << "You have rolled a " << move1 << " and a " << move2 << endl;
                    // if player is not in tims line
                    if (!g.isInLine()) {
                        if (move1 == move2) {
                            numOfDoubles++;
                            if (numOfDoubles == 3) {
                                // logic to send player to the line;
                                cout << "You have rolled 3 doubles! Please advance to the DC Tims Line!" << endl;
                                g.goToTimsLine();
                                g.disableRoll();
                                continue;
                            }
                        } else {
                            g.disableRoll();
                        }
                        g.movePlayer(move1 + move2);
                    // player is in tims line
                    } else if (g.isInLine()) {
                        if (move1 == move2) {
                            cout << "Congratulations! You have rolled a double! You are now out of the DC Tims Line!" << endl;
                            g.setTimsLineTurn(0);
                            g.outOfTimsLine();
                            g.disableRoll();
                            g.movePlayer(move1 + move2);
                        } else {
                            g.disableRoll();
                            if (g.getTimsLineTurn() == 2) {
                                g.setTimsLineTurn(3);
                                cout << "You did not roll a double! As this is your third turn, you must pay 50$ or use a Roll up the Rim Cup" << endl;
                                lastLineTurnDice = (move1 + move2);
                                lastLineTurn = true;
                                if (g.getRimCups(turn) == 0 && g.getPlayerMoney(turn) < 50) {
                                    cout << "You do not have enough money to pay your way out or have a Roll up the Rim Cup" << endl;
                                    cout << "You must pay 50$" << endl;
                                    // bankruptcy
                                    promptBankruptcy(turn, 'C', 50);
                                    lastLineTurn = false;
                                }
                            } else {
                                g.setTimsLineTurn(g.getTimsLineTurn() + 1);
                                cout << "You did not roll a double! You remain in the DC Tims Line" << endl;
                            }
                        }
                    }
                } else {
                    cout << "You are unable to roll the dice anymore in this turn!" << endl;
                }
            } else if (cmd == "next") {
                if (g.getTimsLineTurn() == 3) {
                    cout << "You can not end turn! You must pay 50$ or use a Roll up the Rim Cup" << endl;
                // if player can't roll ...
                } else if (!g.canRoll()) {
                    nextPlayer();
                } else {
                    cout << "You can still roll!" << endl;
                }
            } else if (cmd == "trade") {
                string name;
                string give;
                string receive;
                iss >> name;
                iss >> give;
                iss >> receive;
                promptTrade(turn, name, give, receive);
                
            } else if (cmd == "improve") {
                string property;
                iss >> property;

                int buildingIndex = g.getBuildingIndex(property);

                string buyOrSell;
                iss >> buyOrSell;

                if (buyOrSell == "buy") {
                    buyImprovementPrompt(turn, buildingIndex);
                } else if (buyOrSell == "sell") {
                    sellImprovementPrompt(turn, buildingIndex);
                } else {
                    cout << "Invalid command! Please try again!" << endl;
                }
            } else if (cmd == "mortgage") {
                string property;
                iss >> property;
                int buildingIndex = g.getBuildingIndex(property);
                mortgagePrompt(turn, buildingIndex);
            } else if (cmd == "unmortgage") {
                string property;
                iss >> property;
                int buildingIndex = g.getBuildingIndex(property);
                unmortgagePrompt(turn, buildingIndex, false);
            } else if (cmd == "assets") {
                displayAssets(turn);

            } else if (cmd == "all") {
                displayAll();
            } else if (cmd == "save") {
                string savefile;
                iss >> savefile;
                saveGame(savefile);
                cout << "You have successfully saved the game!" << endl;

            } else if (cmd == "pay" && g.isInLine()) {
                if (g.getPlayerMoney(turn) < 50) {
                    cout << "You do not have enough money to pay to get ahead of the line!" << endl;
                } else {
                    cout << "You paid 50$ to get out!" << endl;
                    g.payPlayerMoney(turn, 50);
                    // logic to make player not in line anymore
                    g.outOfTimsLine();
                    g.setTimsLineTurn(0);
                    if (lastLineTurn) {
                        cout << "You will move " << lastLineTurnDice << " squares due to your last dice roll!" << endl;
                        g.movePlayer(lastLineTurnDice);
                        lastLineTurn = false;
                    }
                }
            } else if (cmd == "use" && g.isInLine()) {
                if (g.getRimCups(turn) > 0) {
                    cout << "You have used a Roll Up the Rim cup to get out!" << endl;
                    // logic to reducing the cups;
                    g.reduceRimCups();
                    // logic to make player not in line anymore;
                    g.outOfTimsLine();
                    g.setTimsLineTurn(0);
                    if (lastLineTurn) {
                        cout << "You will move " << lastLineTurnDice << " squares due to your last dice roll!" << endl;
                        g.movePlayer(lastLineTurnDice);
                        lastLineTurn = false;
                    }
                } else {
                    cout << "You do not have a Roll Up the Rim cup!" << endl;
                }

            } else {
                cout << "Invalid command! Please try again!" << endl;
            }
        } catch (...) {
            cout << "Invalid command! Try again!" << endl;
            if (cin.eof()) throw endOfFileError{};
        }
    }
}

void Controller::nextPlayer() {
    int newTurn = turn;
    for (int i = 0; i < numOfPlayers; i++) {
        g.nextPlayer();
        newTurn = newTurn + 1;
        if (newTurn >= numOfPlayers) newTurn = 0;
        if (!g.isPlayerBankrupt(newTurn)) {  
            turn = newTurn;
            break;
        }
    }
    g.enableRoll();
    numOfDoubles = 0; 
}

// player selection menu at the beginning of the game
void Controller::selectPlayers() {
    vector<char> alreadyChosen;
    cin.exceptions(ios::eofbit|ios::failbit);
    int numOfPlayers;
    cout << "Please enter the number of players:" << endl;
    while (true) {
        try {
            string input;
            getline(cin >> ws, input);
            istringstream iss{input};
            iss.exceptions(ios::failbit);
            iss >> numOfPlayers;
            if (numOfPlayers < 2 || numOfPlayers > 6) {
                throw invalidInput{};
            }
            this->numOfPlayers = numOfPlayers;
            numOfPlayersLeft = numOfPlayers;
            int turn = 0;
            while (true) {
                if (turn == numOfPlayers) break;
                int playerNo = turn + 1;
                cout << "Player " << playerNo << ", please type in your name:" << endl;
                string name;
                getline(cin >> ws, name);
                for (size_t i = 0; i < names.size(); i++) {
                    if (names[i] == name) {
                        continue;
                    }
                }
                while (true) {
                    try {
                        names.push_back(name);
                        cout << names[turn] << ", please select one of the following pieces:" << endl;
                        printPlayers();
                        string piece;
                        getline(cin >> ws, piece);
                        istringstream issP{piece};
                        iss.exceptions(ios::failbit);
                        char c;
                        issP >> c;
                        char d = toupper(c);
                        for (size_t i = 0; i < alreadyChosen.size(); i++) {
                            if (d == alreadyChosen[i]) {
                                throw invalidInput{};
                            }
                        }
                        if (d == 'G') {
                            g.addPlayer(names[turn], 'G', turn, 1500, 0);
                        } else if (d == 'B') {
                            g.addPlayer(names[turn], 'B', turn, 1500, 0);
                        } else if (d == 'D') {
                            g.addPlayer(names[turn], 'D', turn, 1500, 0);
                        } else if (d == 'P') {
                            g.addPlayer(names[turn], 'P', turn, 1500, 0);
                        } else if (d == 'S') {
                            g.addPlayer(names[turn], 'S', turn, 1500, 0);
                        } else if (d == '$') {
                            g.addPlayer(names[turn], '$', turn, 1500, 0);
                        } else if (d == 'L') {
                            g.addPlayer(names[turn], 'L', turn, 1500, 0);
                        } else if (d == 'T') {
                            g.addPlayer(names[turn], 'T', turn, 1500, 0);
                        } else {
                            throw invalidInput{};
                        }
                        turn++;
                        players.emplace_back(d);
                        alreadyChosen.emplace_back(d);
                        view.addPlayer(d, 0);
                        break;
                    } catch(ios::failure &) {
                        cerr << "Invalid piece! Please try again!" << endl;
                        if (cin.eof()) throw endOfFileError{};
                    } catch (invalidInput&) {
                        cerr << "Invalid piece/name or already chosen! Please try again!" << endl;
                    } catch (...) {
                        cerr << "Invalid input! Please try again" << endl;
                    }
                }
            }
            break;
        } catch (ios::failure &) {
            cerr << "Invalid number! Please try again!" << endl;
            if (cin.eof()) throw endOfFileError{};
        } catch (invalidInput&) {
            cerr << "Invalid number of players! Please try again!" << endl;
        }
        cout << "Please enter the number of players:" << endl;
    }
}

// Asks the player if they want to purchase the property they landed on
void Controller::promptPurchase(string squareName, int squareNumber) {
    if (!g.canBuyProperty()) {
        cout << "You don't have enough money to buy this property!" << endl;
        auction(turn, squareName, squareNumber);
        return;
    }
    int cost = g.getCost(squareNumber);
    cout << "This property costs " << cost << "$" << endl;
    while (true) {
        cout << "Would you like to purchase this property? [y/n/assets/all]" << endl;
        string response;
        getline(cin >> ws, response);
        if (response == "y") {
            cout << "Success! You have bought " << squareName << " for " << cost << "$" << endl; 
            g.buyProperty();
            view.printBoard();
            break;
        } else if (response == "n") {
            auction(turn, squareName, squareNumber);
            break;
        } else if (response == "assets") {
            displayAssets(turn);
        } else if (response == "all") {
            displayAll();
        } else {
            cout << "Invalid command! Please type one of [y/n/assets/all]" << endl;
        }
    }
}

// Auction screen if a player refuses to buy a property
void Controller::auction(int whoToStart, string squareName, int squareNumber) {
    bool bidders[numOfPlayers];
    for (int i = 0; i < numOfPlayers; i++) {
        if (g.isPlayerBankrupt(i)) {
            bidders[i] = false;
        } else {
            bidders[i] = true;
        }
    }
    int highestBid = 0;
    int highestBidder = 0;
    int currentBidder = whoToStart;
    int biddersLeft = numOfPlayersLeft;
      
    cout << "Let the auction begin for " << squareName << "!" << endl;
    while (biddersLeft > 1) {
        if (bidders[currentBidder] == false) {
            currentBidder++;
            if (currentBidder >= numOfPlayers) currentBidder = 0;
            continue;
        }
        while (true) {
            cout << names[currentBidder] << ", would you like to bid or withdraw [b/w] or show assets [assets/all]?" << endl;
            string cmd;
            getline(cin >> ws, cmd);
            if (cmd == "b") {
                cout << "The current bid is " << highestBid << "$" << endl;
                cout << "How much would you like to bid?" << endl;
                string bid;
                getline(cin >> ws, bid);
                istringstream issB{bid};
                int bidAmount;
                if (issB >> bidAmount) {
                    // implement a getMoney method for any player
                    if (bidAmount > g.getPlayerMoney(currentBidder)) {
                        cout << "Your bid exceeds the amount of money you have! Please try again!" << endl;
                    } else if (bidAmount <= highestBid) {
                        cout << "Your bid is less than the current highest bid! Please try again!" << endl;
                    } else {
                        cout << "You are now the highest bidder!" << endl;
                        highestBid = bidAmount;
                        highestBidder = currentBidder;
                        currentBidder++;
                        if (currentBidder >= numOfPlayers) currentBidder = 0;
                        break;
                    }
                } else {
                    cout << "Please enter a valid number!" << endl;
                }
            } else if (cmd == "w") {
                cout << "You have withdrawn from the bid!" << endl;;
                bidders[currentBidder] = false;
                biddersLeft--;
                currentBidder++;
                if (currentBidder >= numOfPlayers) currentBidder = 0;
                if (highestBid == 0) {
                    for (int i = 0; i < numOfPlayers; i++) {
                        if (g.isPlayerBankrupt(currentBidder)) {
                            currentBidder++;
                            if (currentBidder >= numOfPlayers) currentBidder = 0;
                        } else {
                            highestBidder = currentBidder;
                            break;
                        }
                    }
                } 
                break;
            } else if (cmd == "assets") {
                // implement a display assets for any player
                displayAssets(currentBidder);
            } else if (cmd == "all") {
                displayAll();
            } else {
                cout << "Please enter a valid command!" << endl;
            }
        }
    } 
    cout << "Congratulations " << names[highestBidder] << ", you have won " << squareName << " for " << highestBid << "$!" << endl;
    // implement a winning auction method
    g.winAuction(highestBidder, squareNumber, highestBid);   
    view.printBoard();
}

void Controller::promptTrade(int fromWho, string name, string give, string receive) {
    // check for valid name
    int playerIndex = -1;
    for (size_t i  = 0; i < names.size(); i++) {
        if (name == names[i]) playerIndex = static_cast<int>(i);
    }
    if (playerIndex == -1) {
        cout << "Please enter a valid name!" << endl;
        return;
    } else if (g.isPlayerBankrupt(playerIndex)) {
        cout << "This player is bankrupt, you can not trade with them!" << endl;
        return; 
    } else {
        // cannot trade with oneself
        if (names[playerIndex] == names[fromWho]) {
            cout << "You can not trade with yourself!" << endl;
            return;
        }
    }
    // Checking if give or receive are money amounts
    int moneyGiven;
    int moneyToReceive;
    bool hasGivenMoney = false;
    bool willReceiveMoney = false;
    istringstream giveS{give};
    istringstream receiveS{receive};
    if (giveS >> moneyGiven) {
        hasGivenMoney = true;
    }
    if (receiveS >> moneyToReceive) {
        willReceiveMoney = true;
    }
    // Checking if both give and receive are money
    if (hasGivenMoney && willReceiveMoney) {
        cout << "You can not trade money for money!" << endl;
        return;
    }

    // Offering money for building
    if (hasGivenMoney) {
        if (moneyGiven > g.getPlayerMoney(fromWho)) {
            cout << "You do not have enough money for this trade!" << endl;
            return;
        }
        int buildingIndex = g.getBuildingIndex(receive);
        if (buildingIndex == -1) {
            cout << "The building does not exist!" << endl;
            return;
        } else if (!g.propertyIsOwnable(buildingIndex)) {
            cout << "This building can not be traded! It is non ownable!" << endl;
            return;
        } else if (!g.ownsProperty(playerIndex, buildingIndex)) {
            cout << name << " does not own this building!" << endl;
            return;
        } else if (g.monopolyHasImprovements(buildingIndex)) {
            cout << "The building can not be traded! It has improvements or the monopoly has improvements!" << endl;
            return;
        } else {
            cout << name << ", you have received a trade offer!" << endl;
            cout << names[fromWho] <<  " offers you " << moneyGiven << "$ to buy your " << receive << endl;
            while(true) {
                try {
                    cout << "You can [accept]/[reject]/[assets]/[all]!" << endl;
                    cin.exceptions(ios::failbit|ios::failbit);
                    string command;
                    getline(cin >> ws, command);
                    if(command == "reject"){
                        cout << "Trade is rejected!" << endl;
                        return;
                    } else if(command == "assets"){
                        // display assets
                        displayAssets(playerIndex);
                    } else if (command == "all") {
                        displayAll();
                    } else if(command == "accept"){
                        // logic for accepting the offer
                        cout << name << " has accepted the offer!" << endl;
                        g.trade(fromWho, playerIndex, moneyGiven, receive);
                        view.printBoard();
                        return;
                    } else{
                        cout << "Invalid command!" << endl;
                    }
                } catch (...) {
                    cout << "Invalid command!" << endl;
                    if (cin.eof()) throw endOfFileError{};
                }
            }
        }
    // Offering building for money
    } else if (willReceiveMoney) {
        if (willReceiveMoney > g.getPlayerMoney(playerIndex)) {
            cout << name << " does not have enough money for this trade!" << endl;
            return;
        }
        int buildingIndex = g.getBuildingIndex(give);
        if (buildingIndex == -1) {
            cout << "The building does not exist!" << endl;
            return;
        } else if (!g.propertyIsOwnable(buildingIndex)) {
            cout << "This building can not be traded! It is non ownable!" << endl;
            return;
        } else if (!g.ownsProperty(fromWho, buildingIndex)) {
            cout << "You do not own this building!" << endl;
            return;
        } else if (g.monopolyHasImprovements(buildingIndex)) {
            cout << "The building can not be traded! It has improvements or the monopoly has improvements!" << endl;
            return;
        } else {
            cout << name << ", you have received a trade offer!" << endl;
            cout << names[fromWho] <<  " offers you their " << give << " for " << moneyToReceive << "$" << endl;
            while(true) {
                try {
                    cout << "You can [accept]/[reject]/[assets]/[all]!" << endl;
                    cin.exceptions(ios::failbit|ios::failbit);
                    string command;
                    getline(cin >> ws, command);
                    if (command == "reject"){
                        cout << "Trade is rejected!" << endl;
                        return;
                    } else if(command == "assets"){
                        // display assets
                        displayAssets(playerIndex);
                    } else if (command == "all") {
                        displayAll();
                    } else if(command == "accept"){
                        // logic for accepting the offer
                        cout << name << " has accepted the offer!" << endl;
                        g.trade(fromWho, playerIndex, give, moneyToReceive);
                        view.printBoard();
                        return;
                    } else {
                        cout << "Invalid command!" << endl;
                    }
                } catch (...) {
                    cout << "Invalid command!" << endl;
                    if (cin.eof()) throw endOfFileError{};
                }
            }
        }
    // Offering building for building
    } else {
        int giveBuildingIndex = g.getBuildingIndex(give);
        int receiveBuildingIndex = g.getBuildingIndex(receive);
        if (giveBuildingIndex == -1) {
            cout << "The building you are offering does not exist!" << endl;
            return;
        } else if (receiveBuildingIndex == -1) {
            cout << "The building you are seeking does not exist!" << endl;
            return;
        } else if (!g.propertyIsOwnable(receiveBuildingIndex)) {
            cout << "The building you are offering can not be traded! It is non ownable!" << endl;
            return;
        } else if (!g.propertyIsOwnable(giveBuildingIndex)) {
            cout << "The building you are seeking can not be traded! It is non ownable!" << endl;
            return;
        } else if (!g.ownsProperty(fromWho, giveBuildingIndex)) {
            cout << "You do not own this building!" << endl;
        } else if (!g.ownsProperty(playerIndex, receiveBuildingIndex)) {
            cout << name << " does not own the building" << endl;
        } else if (g.monopolyHasImprovements(giveBuildingIndex)) {
            cout << "The building you are offering can not be traded! It has improvements or the monopoly has improvements!" << endl;
        } else if (g.monopolyHasImprovements(receiveBuildingIndex)) {
            cout << "The building you are seeking can not be traded! It has improvements or the monopoly has improvements!" << endl;
        } else {
            cout << name << ", you have received a trade offer!" << endl;
            cout << names[fromWho] <<  " offers you their " << give << " for your " << receive << endl;
            while(true) {
                try {
                    cout << "You can [accept]/[reject]/[assets]/[all]:" << endl;
                    cin.exceptions(ios::failbit|ios::failbit);
                    string command;
                    getline(cin >> ws, command);
                    if(command == "reject"){
                        cout << "Trade is rejected!" << endl;
                        return;
                    } else if(command == "assets") {
                        // display assets
                        displayAssets(playerIndex);
                    } else if (command == "all") {
                        displayAll();
                    } else if(command == "accept"){
                        // logic for accepting the offer
                        cout << name << " has accepted the offer!" << endl;
                        g.trade(fromWho, playerIndex, give, receive);
                        view.printBoard();
                        return;
                    } else {
                        cout << "Invalid command!" << endl;
                    }
                } catch (...) {
                    cout << "Invalid command!" << endl;
                    if (cin.eof()) throw endOfFileError{};
                }
            }
        }
    }
}


int Controller::getPlayerIndex(char who) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i] == who) return static_cast<int>(i);
    }
    return -1;
}

int Controller::getPlayerIndexName(string name) {
    for (size_t i = 0; i < names.size(); i++) {
        if (names[i] == name) return static_cast<int>(i);
    }
    return -1;
}
 
void Controller::promptBankruptcy(int whichPlayer, char toWho, int feesOwed) {
    cout << names[whichPlayer] << ", you owe more money than you currently possess!" << endl;
    int playerIndex = getPlayerIndex(toWho);
    string target;
    if (toWho == 'K' || toWho == 'C') {
        target = "the School";
    } else {
        target = names[playerIndex];
    }
    cout << names[whichPlayer] << ", you currently owe " << feesOwed << "$ to " << target << "!" << endl;
    while (g.getPlayerMoney(whichPlayer) < feesOwed) {
        try {
            cout << "You can declare bankruptcy [bankrupt] or attempt to [trade]/[mortgage]/[improve]/[assets]/[all]" << endl;
            string cmdline;
            getline(cin >> ws, cmdline);
            istringstream iss{cmdline};
            iss.exceptions(ios::failbit);
            string cmd;
            iss >> cmd;
            if (cmd == "bankrupt") {
                // logic for declaring bankruptcy
                dropout(whichPlayer, playerIndex);
                return;
            } else if (cmd == "trade") {
                string name;
                string give;
                string receive;
                iss >> name;
                iss >> give;
                iss >> receive;
                promptTrade(turn, name, give, receive);
            } else if (cmd == "mortgage") {
                string property;
                iss >> property;

                int buildingIndex = g.getBuildingIndex(property);

                mortgagePrompt(whichPlayer, buildingIndex);
            } else if (cmd == "improve") {
                string property;
                iss >> property;

                int buildingIndex = g.getBuildingIndex(property);

                string buyOrSell;
                iss >> buyOrSell;

                if (buyOrSell == "buy") {
                    buyImprovementPrompt(whichPlayer, buildingIndex);
                } else if (buyOrSell == "sell") {
                    sellImprovementPrompt(whichPlayer, buildingIndex);
                } else {
                    cout << "Invalid command! Please try again!" << endl;
                }
            } else if (cmd == "assets") {
                displayAssets(whichPlayer);
                // display assets
            } else if (cmd == "all") {
                displayAll();
                // display all
            } else {
                cout << "Invalid command! Please try again!" << endl;
            }
        } catch (ios::failure &) {
            cerr << "Invalid command! Please try again!" << endl;
            if (cin.eof()) throw endOfFileError{};
        }
    }
    cout << names[whichPlayer] << ", you now have enough money to pay your debts!" << endl;
    g.payPlayerMoney(whichPlayer, feesOwed);
    if (toWho == 'C') {
        // pay out of jail
        cout << "You have paid 50$ to get out of jail!" << endl;
        g.outOfTimsLine();
        g.setTimsLineTurn(whichPlayer, 0);
        cout << "You will move " << lastLineTurnDice << " squares due to your last dice roll!" << endl;
        lastLineTurn = false;
        g.movePlayer(lastLineTurnDice);
    } else if (toWho == 'K') {
        // pay for all other bank dues
        cout << "You have paid " << feesOwed << " $ to " << target << endl;
    } else {
        // owes a player
        cout << "You have paid " << feesOwed << " $ to " << target << endl;
    }

}

void Controller::buyImprovementPrompt(int whichPlayer, int whichBuilding) {
    if (whichBuilding == -1) {
        cout << "This building does not exist! Try again!" << endl;
    } else if (!g.isAcademic(whichBuilding)) {
        cout << "This building is not an academic building! You can not buy improvements!" << endl;
    } else if (!g.ownsProperty(whichPlayer, whichBuilding)) {
        cout << "You do not own this building!" << endl;
    } else if (!g.checkMonopoly(whichPlayer, whichBuilding)) {
        cout << "You do not own the monopoly of this building! You can not buy improvements" << endl;
    } else if (g.isMortgaged(whichBuilding)) {
        cout << "This property is mortgaged. You can not buy improvements!" << endl;
    } else if (g.getImprovements(whichBuilding) == 5) {
        cout << "You can not improve further this building!" << endl;
    } else if (g.getPlayerMoney(whichPlayer) < g.getImplementationCost(whichBuilding)) {
        cout << "You do not have enough money to buy improvements!" << endl;
    } else {
        g.buyImprovement(whichPlayer, whichBuilding);
        cout << "You have successfully bought an improvement!" << endl;
        view.printBoard();
    }

}

void Controller::sellImprovementPrompt(int whichPlayer, int whichBuilding) {
    if (whichBuilding == -1) {
        cout << "This building does not exist! Try again!" << endl;
    } else if (!g.isAcademic(whichBuilding)) {
        cout << "This building is not an academic building! You can not sell improvements!" << endl;
    } else if (!g.ownsProperty(whichPlayer, whichBuilding)) {
        cout << "You do not own this building!" << endl;
    } else if (!g.hasImprovements(whichBuilding)) {
        cout << "This building does not have improvements! You can not sell imaginary improvements!" << endl;
    } else {
        g.sellImprovement(whichPlayer, whichBuilding);
        cout << "You have successfully sold an improvement!" << endl;
        view.printBoard();
    }
}

void Controller::mortgagePrompt(int whichPlayer, int whichBuilding) {
    if (whichBuilding == -1) {
        cout << "This building does not exist! Try again!" << endl;
    } else if (!g.propertyIsOwnable(whichBuilding)) {
        cout << "This building is not an ownable building! You can not mortgage it!" << endl;
    } else if (!g.ownsProperty(whichPlayer, whichBuilding)) {
        cout << "You do not own this building!" << endl;
    } else if (g.hasImprovements(whichBuilding)) {
        cout << "This building has improvements! Please sell them before attempting to mortgage it!" << endl;
    } else if (g.isMortgaged(whichBuilding)) {
        cout << "This property is already mortgaged!" << endl;
    } else {
        g.mortgage(whichPlayer, whichBuilding);
        cout << "You have mortgaged this property!" << endl;
        view.printBoard();
    }  
}

void Controller::unmortgagePrompt(int whichPlayer, int whichBuilding, bool immediate) {
    if (whichBuilding == -1) {
        cout << "This building does not exist! Try again!" << endl;
    } else if (!g.propertyIsOwnable(whichBuilding)) {
        cout << "This building is not an ownable building! You can not unmortgage it!" << endl;
    } else if (!g.ownsProperty(whichPlayer, whichBuilding)) {
        cout << "You do not own this building!" << endl;
    } else if (!g.isMortgaged(whichBuilding)) {
        cout << "This property is not mortgaged! You can not umortgage it" << endl;
    } else {
        // check if player has enough money to buy back the building
        // ...
        int fees;
        if (immediate) {
            fees = g.getCost(whichBuilding) / 2;
        } else {
            fees = (g.getCost(whichBuilding) * 3) / 5;
        }
        if (g.getPlayerMoney(whichPlayer) < fees) {
            cout << "You do not have enough money to unmortgage the property" << endl;
        } else {
            g.unmortgage(whichPlayer, whichBuilding, immediate);
            cout << "You have unmortgaged this property!" << endl;
            view.printBoard();
        }
    }  
}

void Controller::dropout(int whichPlayer, int toWho) {
    numOfPlayersLeft--;
    g.bankruptPlayer(whichPlayer);
    char playerPiece = g.getPlayerPiece(whichPlayer);
    view.removePlayer(playerPiece);
    cout << names[whichPlayer] << " has dropped out of the game! Booo!" << endl;

    // checking if someone won the game
    if (numOfPlayersLeft == 1) {
        string winner;
        for (int i = 0; i < numOfPlayers; i++) {
            if (!g.isPlayerBankrupt(i)) winner = g.getPlayerName(i);
        }
        if (winner == "") {
            cout << "Error for winner!" << endl;
        }
        cout << winner << " has won the game! Congratulations" << endl;
        gameIsWon = true;
    } else {
        // Auctions
        if (toWho == -1) {
            cout << "An auction will be held for " << names[whichPlayer] << "'s properties" << endl;
            // auction off the player's properties
            vector<int> auctionedProperties;
            g.getPlayerProperties(auctionedProperties, whichPlayer);
            for (int p : auctionedProperties) {
                g.resetBuilding(p);
                string squareName = g.getSquare(p);
                auction(whichPlayer, squareName, p);
            }
        } else {
            cout << names[whichPlayer] << "'s assets will be transferred to " << names[toWho] << "!" << endl;
            // transfer assets to the player that is owed
            g.transferAssets(whichPlayer, toWho);
            view.printBoard();
        }
        nextPlayer();
    }
    
}

void Controller::promptTuition() {
    cout << "Woud like you to pay 300$[1] or 10\% of your networth[2]?" << endl;
    while (true) {
        try {
            string cmd;
            getline(cin >> ws, cmd);
            cin.exceptions(ios::failbit|ios::failbit);
            if (cmd == "1") {
                if (g.getPlayerMoney(turn) < 300) {
                    promptBankruptcy(turn, 'K', 300);
                } else {
                    cout << "You paid 300$ to the school!" << endl;
                    g.payPlayerMoney(turn, 300);
                }
                break;
            } else if (cmd == "2") {
                int networth = g.getPlayerNetworth(turn);
                int fees = 0.1 * networth;
                if (g.getPlayerMoney(turn) < fees) {
                    promptBankruptcy(turn, 'K', fees);
                } else {
                    cout << "You paid " << fees << "$ to the School!" << endl;
                    g.payPlayerMoney(turn, fees);
                }
                break;
            } else {
                cout << "Invalid command. Please try one of [1] for 300$, [2] for 10\%" << endl;
            }
        } catch (...) {
            cout << "Invalid command!" << endl;
            if (cin.eof()) throw endOfFileError{};
        }
    } 

}

void Controller::promptMortgageReceived(int whichPlayer, int whichBuilding) {
    cout << names[whichPlayer] << ", you have received a mortgaged property" << endl;
    cout << "You must pay immediately 10\% of the original price" << endl;
    int fees = g.getCost(whichBuilding) / 10;
    if (g.getPlayerMoney(whichPlayer) < fees) {
        // prompt bankruptcy
        promptBankruptcy(whichPlayer, 'K', fees);
    } else {
        cout << "You paid " << fees << "$ to the School" << endl;
        g.payPlayerMoney(whichPlayer, fees);
        while (true) {
            try {
                cout << "Do you wish to unmortgage the building immediately [1] or wait for later [2] or display assets [assets/all]?" << endl;
                string cmd;
                getline(cin >> ws, cmd);
                cin.exceptions(ios::failbit|ios::failbit);
                if (cmd == "1") {
                    unmortgagePrompt(whichPlayer, whichBuilding, true);
                    return;
                } else if (cmd == "2") {
                    // Do nothing for now
                    return;
                } else if (cmd == "assets") {
                    displayAssets(whichPlayer);
                } else if (cmd == "all") {
                    displayAll();
                } else {
                    cout << "Invalid command! Try again!" << endl;
                }
            } catch (...) {
                cout << "Invalid command!" << endl;
                if (cin.eof()) throw endOfFileError{};
            }
        }
    }
}


void Controller::displayAssets(int whichPlayer) {
    cout << "Cash Balance: " << g.getPlayerMoney(whichPlayer) << endl;
    cout << "Networth: " << g.getPlayerNetworth(whichPlayer) << endl;
    cout << "Roll Up The Rim Cups: "  << g.getRimCups(whichPlayer) << endl;
    vector<int> playerProperties;
    g.getPlayerProperties(playerProperties, whichPlayer);
    if (playerProperties.size() > 0) {
        cout << "Properties(Name, Block, Improvements, Mortgage Status): " << endl;
        for (int p : playerProperties) {
            cout << "-";
            BoardState bs = g.getBuildingState(p);
            cout << bs.name << " ";
            cout << bs.block << " ";
            if (g.isAcademic(p)) {
                cout << g.getImprovements(p) << " ";
            } else {
                cout << 0 << " ";
            }
            bool mortgageStatus = g.isMortgaged(p);
            if (mortgageStatus) {
                cout << "mortgaged" << endl;
            } else {
                cout << "unmortgaged" << endl;
            }
        }
    }
}


void Controller::displayAll() {
    for (int i = 0; i < numOfPlayers; i++) {
        if (!g.isPlayerBankrupt(i)) {
            cout << names[i] << "'s assets:" << endl;
            displayAssets(i);
            cout << endl;
        } 
    }
}


void Controller::loadGame(string file) {
    ifstream savefile{file};

    if (savefile.is_open()) {
        try {
            string playerNumbers;
            getline(savefile, playerNumbers);
            istringstream iss{playerNumbers};
            iss >> numOfPlayers;
            numOfPlayersLeft = numOfPlayers;
            for (int i = 0; i < numOfPlayers; i++) {
                string player;
                getline(savefile, player);
                istringstream iss{player};
                string playerName;
                iss >> playerName;
                char playerPiece;
                iss >> playerPiece;
                int numOfCups;
                iss >> numOfCups;
                int money;
                iss >> money;
                int position;
                iss >> position;
                g.addPlayer(playerName, playerPiece, i, money, numOfCups);
                g.setPlayerPosition(i, position);
                view.addPlayer(playerPiece, position);
                players.push_back(playerPiece);
                names.push_back(playerName);
                if (position == 10) {
                    int inLine;
                    iss >> inLine;
                    if (inLine == 1) {
                        g.goToTimsLine(i);
                        int turns;
                        iss >> turns;
                        g.setTimsLineTurn(i, turns);
                    }
                }
            }
            for (int i = 0; i < 28; i++) {
                string building;
                getline(savefile, building);
                istringstream issB{building};
                string propertyName;
                string ownerName;
                issB >> propertyName;
                issB >> ownerName;
                if (ownerName != "BANK") {
                    int playerNumber = getPlayerIndexName(ownerName);
                    int buildingNumber = g.getBuildingIndex(propertyName);
                    g.addPropertyToPlayer(playerNumber, buildingNumber);
                    int improvementNumber;
                    issB >> improvementNumber;
                    if (improvementNumber == -1) {
                        g.setPropertyMortgaged(buildingNumber);
                    } else if (improvementNumber >= 0 && improvementNumber <= 5) {
                        if (g.isAcademic(buildingNumber)) {
                            g.setImprovements(buildingNumber, improvementNumber);
                            view.setImprovements(buildingNumber, improvementNumber);
                        }
                    } else {
                        throw invalidInput{};
                    }
                }       
            }
            cout << "Read success!" << endl;
        } catch (...) {
            throw invalidFile{};
        }            
    }

}

void Controller::saveGame(string file) {
    ofstream newFile{file};
    newFile << numOfPlayersLeft << endl;

    for (int i = 0; i < numOfPlayers; i++) {
        if (!g.isPlayerBankrupt(i)) {
            newFile << g.getPlayerName(i) << " ";
            newFile << g.getPlayerPiece(i) << " ";
            newFile << g.getRimCups(i) << " ";
            newFile << g.getPlayerMoney(i) << " ";
            newFile << g.getPlayerPosition(i);
            if (g.getPlayerPosition(i) == 10) {
                if (g.isInLine(i)) {
                    newFile << " " << 1 << " " << g.getTimsLineTurn(i) << endl;
                } else {
                    newFile << " " << 0 << endl;
                }
            } else {
                newFile << endl;
            } 
        }
    }
    for (int i = 0; i < 40; i++) {
        if (g.propertyIsOwnable(i)) {
            newFile << g.getBuildingName(i) << " ";
            char owner = g.getBuildingOwner(i);
            if (owner == ' ') {
                newFile << "BANK" << " ";
            } else {
                int player = getPlayerIndex(owner);
                newFile << names[player] << " ";
            }
            if (g.isMortgaged(i)) {
                newFile << -1 << endl;
            } else if (g.isAcademic(i)) {
                newFile << g.getImprovements(i) << endl;
            } else {
                newFile << 0 << endl;
            }
        }
    } 
}

// Controller's method to deal with notifications sent either from Game or individual BoardSquare
void Controller::notify(Subject<GameState>& whoFrom) {
    GameState state = whoFrom.getState();
    if (state.type == MessageType::Tuition) {
        promptTuition();
    } else if (state.type == MessageType::SLCMove) {
        int newSquare = g.getCurrentPosition() + state.position;
        if (newSquare >= 40) {
            newSquare = newSquare - 40;
        } else if (newSquare < 0) {
            newSquare = 40 + newSquare;
        }
        cout << g.getSquare(newSquare) << "!" << endl;
        g.movePlayer(state.position);
    } else if (state.type == MessageType::emptyOwnable) {
        // logic for landing on an empty square
        promptPurchase(state.squareName, state.position);
    // logic for paying tuition on someone's property
    } else if (state.type == MessageType::Payment) {
        int playerIndex = getPlayerIndex(state.target);
        cout << "You paid " << state.owed << "$ to " << names[playerIndex] << endl;
        g.gainPlayerMoney(playerIndex, state.owed);
    } else if (state.type == MessageType::Bankruptcy) {
        int playerIndex = getPlayerIndex(state.player);
        promptBankruptcy(playerIndex, state.target, state.owed);
    } else if (state.type == MessageType::GoToOSAP) {
        g.goToOSAP();
    } else if (state.type == MessageType::GoToTims) {
        g.disableRoll();
        g.goToTimsLine();
    } else if (state.type == MessageType::ReceiveMortgage) {
        int p = getPlayerIndex(state.player);
        promptMortgageReceived(p, state.position);
    }
}

