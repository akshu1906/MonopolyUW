#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include "player.h"
#include "subject.h"
#include "gamestate.h"
#include "dice.h"

class BoardSquare;
class Controller;
class View;

class Game: public Subject<GameState> {
    std::vector<Player> players;
    Dice dice;
    std::vector<std::shared_ptr<BoardSquare>> gameboard;
    int currentPlayer = 0;
    int numOfPlayers = 0;
    // int numOfRimCups = 4;
    int rimCupsLeft = 4;

    public:
        void init(Controller* c, View* v);

        int roll();

        void disableRoll();

        void enableRoll();

        bool canRoll();

        void nextPlayer();

        void addPlayer(std::string name, char piece, int turn, int money, int rimCups);

        int getPlayerPosition(int whichPlayer);

        int getCurrentPosition();

        std::string getCurrentSquare();

        std::string getSquare(int whichBuilding);

        char getPlayerPiece(int whichPlayer);

        std::string getPlayerName(int whichPlayer);

        void setPlayerPosition(int whichPlayer, int position);

        void movePlayer(int moves);

        void payPlayerMoney(int whichPlayer, int amount);

        void gainPlayerMoney(int whichPlayer, int amount);

        int getPlayerMoney(int whichPlayer);

        int getPlayerNetworth(int whichPlayer);

        bool isInLine();

        bool isInLine(int whichPlayer);

        int getTimsLineTurn();

        int getTimsLineTurn(int whichPlayer);

        int getRimCups(int whichPlayer);

        void reduceRimCups();

        void setTimsLineTurn(int num);

        void setTimsLineTurn(int whichPlayer, int num);

        void goToTimsLine();

        void goToTimsLine(int whichPlayer);

        void outOfTimsLine();

        void outOfTimsLine(int whichPlayer);

        void goToOSAP();

        void bankruptPlayer(int whichPlayer);

        bool isPlayerBankrupt(int whichPlayer);

        BoardState getBuildingState(int whichBuilding);

        std::string getBuildingName(int whichBuilding);

        char getBuildingOwner(int whichBuilding);

        int getBuildingIndex(std::string name);

        int getCost(int whichBuilding);

        bool checkMonopoly(int whichPlayer, int whichBuilding);

        bool propertyCanBeOwned();

        bool propertyIsOwnable(int whichBuilding);

        bool canBuyProperty();

        bool ownsProperty(int whichPlayer, int whichBuilding);

        void getPlayerProperties(std::vector<int>& properties, int whichPlayer);

        bool isAcademic(int whichBuilding);

        bool isMortgaged(int whichBuilding);

        int getImprovements(int whichBuilding);

        int getImplementationCost(int whichBuilding);

        bool hasImprovements(int whichBuilding);

        bool monopolyHasImprovements(int whichBuilding);

        void buyProperty();

        void addPropertyToPlayer(int player, int squareNumber);

        void resetBuilding(int whichBuilding);

        void winAuction(int player, int squareNumber, int bidAmount);

        void buyImprovement(int whichPlayer, int whichBuilding);

        void sellImprovement(int whichPlayer, int whichBuilding);

        void setImprovements(int whichBuilding, int improvements);

        void mortgage(int whichPlayer, int whichBuilding);

        void unmortgage(int whichPlayer, int whichBuilding, bool immediate);

        void setPropertyMortgaged(int whichBuilding);

        void updateBlock(int whichPlayer, std::string block);

        void transferAssets(int fromWho, int toWho);

        void trade(int fromWho, int toWho, int amountOffered, std::string buildingReceived);

        void trade(int fromWho, int toWho, std::string buildingOffered, int amountReceived);

        void trade(int fromWho, int toWho, std::string buildingOffered, std::string buildingReceived);

};

#endif
