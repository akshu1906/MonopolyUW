#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>

enum class MessageType { NewMove, SLCMove, NewImprovement, NewProperty, 
                    RemoveImprovement, RemoveProperty, Mortgage, Unmortgage, Tuition, 
                    Payment, Bankruptcy, GoToTims, GoToOSAP, emptyOwnable, ReceiveMortgage, ResetImprovements};


struct GameState {
    MessageType type;
    char player;
    int position;
    int turn;
    std::string squareName;
    char target;
    int owed;

    GameState() {}
    GameState(MessageType type, int position): type{type}, position{position} {}
    GameState(MessageType type, char player, int position, int turn, std::string squareName): 
        type{type}, player{player}, position{position}, turn{turn}, squareName{squareName} {}
    GameState(MessageType type, char player, int position): 
        type{type}, player{player}, position{position} {}
    GameState(MessageType type, char player, char target, int owed): type{type}, player{player}, target{target}, owed{owed} {}
    GameState(MessageType type): type{type} {}
};

#endif
