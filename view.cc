
#include "view.h"
#include "controller.h"
#include "subject.h"
#include "gamestate.h"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;


// int rows = 56;
// int columns = 100;

// int boxHeight = 5;
// int boxWidth = 9;

// // prints the Game Board
// void View::printBoard() {
//     ifstream file;
//     file.open("gameboard.txt");
// }


// void View::addPlayer(string name, int pos) {
//     positions[name] = pos;
// }

// constants
int rows = 56;
int columns = 101;

int boxHeight = 5;
int boxWidth = 9;

map<char, string> colors;

// colors that represent each piece character
// colors['G'] = "\033[31m";
// colors['B'] = "\033[32m";
// colors['D'] = "\033[33m";
// colors['P'] = "\033[34m";
// colors['S'] = "\033[35m";
// colors['$'] = "\033[36m";
// colors['L'] = "\033[91m";
// colors['T'] = "\033[92m";

string resetSequence = "\033[0m";

// Read the preformatted board txt and sets the display to the characters
void View::init() {
    ifstream file;
    file.open("gameboard.txt");
    char c;
    for (int i = 0; i < rows; i++) {
        vector<string> row;
        for (int j = 0; j < columns; j++) {
            file.get(c);
            string s;
            s.assign(1, c);
            row.push_back(s);
        }
        theDisplay.push_back(row);
    }
    file.close();
    colors['G'] = "\033[31m";
    colors['B'] = "\033[32m";
    colors['D'] = "\033[33m";
    colors['P'] = "\033[34m";
    colors['S'] = "\033[35m";
    colors['$'] = "\033[36m";
    colors['L'] = "\033[91m";
    colors['T'] = "\033[92m";
}

// Converts the square number to the coordinates for the display when a player lands on a square
Coordinate View::convertPositionVisit(int pos) {
    if (pos < 10) {
        return Coordinate{((10 - pos) * boxWidth + 1), rows - 2};
    } else if (pos <= 30 && pos >= 20) {
        return Coordinate{((pos - 20) * boxWidth + 1), 4};
    } else if (pos < 20) {
        return Coordinate{1 , 4 + (10 - (pos - 10)) * 5};
    } else {
        return Coordinate{91 , 4 + (pos - 30) * 5};
    }
}

// Converts the square number to the coordinates for the display when a player lands on a square
Coordinate View::convertPositionProperty(int pos) {
    if (pos == 5) {
        return Coordinate{((pos) * boxWidth + 1), rows - 4};
    } else if (pos == 12 || pos == 15) {
        return Coordinate{1 , 2 + (10 - (pos - 10)) * 5};
    } else if (pos == 25 || pos == 28) {
        return Coordinate{((pos - 20) * boxWidth + 1), 2};
    } else if (pos == 35) {
        return Coordinate{91 , 2 + (pos - 30) * 5};
    } else {
        if (pos < 10) {
            return Coordinate{((10 - pos) * boxWidth + 1), rows - 5};
        } else if (pos <= 30 && pos >= 20) {
            return Coordinate{((pos - 20) * boxWidth + 1), 1};
        } else if (pos < 20) {
            return Coordinate{1 , 1 + (10 - (pos - 10)) * 5};
        } else {
            return Coordinate{91 , 1 + (pos - 30) * 5};
        }
    }
}

// Converts the square number to the coordinates for the display when a player mortgages a property
Coordinate View::convertPositionMortgage(int pos) {
    if (pos == 5) {
        return Coordinate{((pos) * boxWidth + 2), rows - 4};
    } else if (pos == 12 || pos == 15) {
        return Coordinate{2 , 2 + (10 - (pos - 10)) * 5};
    } else if (pos == 25 || pos == 28) {
        return Coordinate{((pos - 20) * boxWidth + 2), 2};
    } else if (pos == 35) {
        return Coordinate{92 , 2 + (pos - 30) * 5};
    } else {
        if (pos < 10) {
            return Coordinate{((10 - pos) * boxWidth + 2), rows - 5};
        } else if (pos <= 30 && pos >= 20) {
            return Coordinate{((pos - 20) * boxWidth + 2), 1};
        } else if (pos < 20) {
            return Coordinate{2 , 1 + (10 - (pos - 10)) * 5};
        } else {
            return Coordinate{92 , 1 + (pos - 30) * 5};
        }
    }
}

// Converts the square number to the coordinates for the display when a player buys improvements
Coordinate View::convertPositionImprovement(int pos) {
    if (pos < 10) {
        return Coordinate{((10 - pos) * boxWidth + 4), rows - 5};
    } else if (pos <= 30 && pos >= 20) {
        return Coordinate{((pos - 20) * boxWidth + 4), 1};
    } else if (pos < 20) {
        return Coordinate{4 , 1 + (10 - (pos - 10)) * 5};
    } else {
        return Coordinate{94 , 1 + (pos - 30) * 5};
    }
}

void View::setPlayers() {
    for (auto& p: positions) {
        Coordinate c = convertPositionVisit(p.second);
        for (int i  = 0; i < 6; i++) {
            if (theDisplay[c.y][c.x + i] == " ") {
                theDisplay[c.y][c.x + i] = colors[p.first] + p.first + resetSequence;
                break;
            }
        }
        // theDisplay[c.y][c.x] = colors[count] + p.first + resetSequence;
    }
}

void View::unsetPlayers() {
    for (auto& p: positions) {
        Coordinate c = convertPositionVisit(p.second);
        for (int i  = 0; i < 6; i++) {
            if (theDisplay[c.y][c.x + i] != " ") {
                theDisplay[c.y][c.x + i] = " ";
            }
        }
    }
}

// prints the Game Board
void View::printBoard() {
    setPlayers();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << theDisplay[i][j];
        }
        cout << endl;
    }
    unsetPlayers();
}

// add a player and its board position to the positions map or update the player's position
void View::addPlayer(char piece, int pos) {
    positions[piece] = pos;
}

// remove the player from the positions map
void View::removePlayer(char piece) {
    positions.erase(piece);
}

void View::setImprovements(int whichSquare, int numberOfImprovements) {
    Coordinate c = convertPositionImprovement(whichSquare);
    for (int i = 0; i < numberOfImprovements; i++) {
        theDisplay[c.y][c.x + i] = "I";
    }
}

// void View::printSize() {
//     cout << theDisplay.size() << endl;
//     cout << theDisplay[0].size() << endl;
//     // if (theDisplay[54][1] == "") {
//     //     cout << "empty string" << endl;
//     // } else if (theDisplay[54][1] == " ") {
//     //     cout << "space" << endl;
//     // } else {
//     //     cout << "not" << endl;
//     // }
// }

void View::notify(Subject<GameState>& whoNotified) {
    GameState state = whoNotified.getState();
    // for a new move update the positions map for view
    if (state.type == MessageType::NewMove) {
        positions[state.player] = state.position;
        printBoard();
        cout << "You landed on " << state.squareName << endl;
    } else if (state.type == MessageType::NewProperty) {
        Coordinate c = convertPositionProperty(state.position);
        theDisplay[c.y][c.x] = colors[state.player] + state.player + resetSequence;
        // printBoard();
    } else if (state.type == MessageType::Mortgage) {
        Coordinate c = convertPositionMortgage(state.position);
        theDisplay[c.y][c.x] = "M";
    } else if (state.type == MessageType::Unmortgage) {
        Coordinate c = convertPositionMortgage(state.position);
        theDisplay[c.y][c.x] = " ";
    } else if (state.type == MessageType::SLCMove) {
        int newPosition = positions[state.player] + state.position;
        if (newPosition >= 40) {
            positions[state.player] = newPosition - 40;
        } else if (newPosition < 0) {
            positions[state.player] = 40 + newPosition;
        } else {
            positions[state.player] = newPosition;
        }
    } else if (state.type == MessageType::NewImprovement) {
        Coordinate c = convertPositionImprovement(state.position);
        for (int i = 0; i < 5; i++) {
            if (theDisplay[c.y][c.x + i] == " ") {
                c.x = c.x + i;
                break;
            }
        }
        theDisplay[c.y][c.x] = "I";
    } else if (state.type == MessageType::RemoveImprovement) {
        Coordinate c = convertPositionImprovement(state.position);
        int count = 0;
        for (int i = 0; i < 5; i++) {
            if (theDisplay[c.y][c.x + i] == "I") count++;
        }
        theDisplay[c.y][c.x + count - 1] = " ";

    } else if (state.type == MessageType::ResetImprovements) {
        Coordinate c = convertPositionImprovement(state.position);
        for (int i = 0; i < 5; i++) {
            theDisplay[c.y][c.x + i] = " ";
        }
    }
}
