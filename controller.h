#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>
#include <map>
#include "observer.h"
#include "gamestate.h"
#include "subject.h"
#include "game.h"
#include "view.h"

class invalidInput{};
class invalidFile{};
class endOfFileError{};


class Controller: public Observer<GameState> {
    Game g;
    View view;
    int turn = 0;
    int numOfPlayers = 0;
    int numOfPlayersLeft;
    int numOfDoubles = 0;
    std::vector<std::string> names;
    std::vector<char> players;
    bool testing;
    std::vector<std::string> validProperties;
    int lastLineTurnDice;
    bool lastLineTurn = false;
    bool gameIsWon = false;

    int getPlayerIndex(char who);

    int getPlayerIndexName(std::string name);

    void printPlayers();

    public:
        void launch(bool testing, bool loading, std::string savefile);

        void selectPlayers();

        void play();

        void nextPlayer();

        void promptPurchase(std::string squareName, int squareNumber);

        void promptTrade(int fromWho, std::string name, std::string give, std::string receive);

        void auction(int whoToStart, std::string squareName, int squareNumber);

        void promptBankruptcy(int whichPlayer, char toWho, int feesOwed);

        void buyImprovementPrompt(int whichPlayer, int whichBuilding);

        void sellImprovementPrompt(int whichPlayer, int whichBuilding);

        void mortgagePrompt(int whichPlayer, int whichBuilding);

        void unmortgagePrompt(int whichPlayer, int whichBuilding, bool immediate);

        void dropout(int whichPlayer, int toWho);

        void displayAssets(int whichPlayer);

        void displayAll();

        void promptTuition();

        void promptMortgageReceived(int whichPlayer, int whichBuilding);

        void saveGame(std::string file);

        void loadGame(std::string file);

        void notify(Subject<GameState>& whoFrom) override;

};

#endif
