#ifndef VIEW_H
#define VIEW_H

#include <map>
#include <vector>
#include <string>
#include <utility>
#include "observer.h"
#include "gamestate.h"
#include "subject.h"

struct Coordinate {
    int x;
    int y;
};

class View: public Observer<GameState> {
    std::vector<std::vector<std::string>> theDisplay;

    std::map<char, int> positions;

    // converts the square number of the board into a coordinate for the display
    Coordinate convertPositionVisit(int pos);

    Coordinate convertPositionProperty(int pos);

    Coordinate convertPositionMortgage(int pos);

    Coordinate convertPositionImprovement(int pos);

    public:
        void init();

        void printBoard();

        void setPlayers();

        void unsetPlayers();

        void addPlayer(char piece, int pos);

        void removePlayer(char piece);

        void setImprovements(int whichSquare, int numberOfImprovements);

        void notify(Subject<GameState>& whoFrom);
};

#endif
