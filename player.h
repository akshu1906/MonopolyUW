#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>
#include <string>
#include "boardsquare.h"
#include <utility>

class Player {
    int position;
    std::string name;
    char piece;
    std::map<std::pair<std::string, std::string>, int> properties;
    int turn;
    int money;
    int networth;
    int rimCups;
    int timsLineTurn;
    bool isBankrupt;
    bool isInLine;
    bool canRoll;

    public:
        Player(std::string name, char piece, int turn, int money, int rimCups);

        int getPosition();

        char getPiece();

        std::string getName();

        int getMoney();

        int getTurn();

        int getNetworth();

        bool stillInPlay();

        void goesBankrupt();

        int getTimsLineTurn();

        int getRimCups();

        bool canRollAgain();

        void setTimsLineTurn(int num);

        bool isInTims();

        void outOfTims();

        void advance(int moves);

        void back(int moves);

        void setPosition(int position);

        void disableRoll();

        void enableRoll();

        void goToTimsLine();

        void goToOSAP();

        void payMoney(int amount);

        void gainMoney(int amount);
        
        bool hasMonoply(std::string block);

        void addBuilding(int position, std::string name, std::string block, int cost);

        void removeBuilding(std::string name, std::string block, int cost);

        void receiveRimCup();

        void reduceRimCup();

        void returnBlockPos(std::vector<int>& v, std::string block);

        void returnAllProperties(std::vector<int>& v);

};

#endif
