#include "player.h"
#include <string>
using namespace std;

Player::Player(string name, char piece, int turn, int money, int rimCups): name{name}, piece{piece}, turn{turn}, money{money}, rimCups{rimCups} {
    position = 0;
    isBankrupt = false; 
    isInLine = false;
    canRoll = true;
    networth = money;
    timsLineTurn = 0;
    isBankrupt = false;
}

int Player::getPosition() {
    return position;
}

char Player::getPiece() {
    return piece;
}

string Player::getName() {
    return name;
}

int Player::getMoney() {
    return money;
}

int Player::getNetworth() {
    return networth;
}

bool Player::stillInPlay() {
    return isBankrupt;
}

void Player::goesBankrupt() {
    isBankrupt = true;
}

// LineState Player::getLineState() {
//     return LineState{timsLineTurn, rimCups, money};
// }

int Player::getTimsLineTurn() {
    return timsLineTurn;
}

int Player::getRimCups() {
    return rimCups;
}

int Player::getTurn() {
    return turn;
}

bool Player::canRollAgain() {
    return canRoll;
}

void Player::setTimsLineTurn(int num) {
    timsLineTurn = num;
}

bool Player::isInTims() {
    return isInLine;
}

void Player::outOfTims() {
    isInLine = false;
}

void Player::advance(int moves) {
    int newPosition = position + moves;
    if (newPosition >= 40) {
        position = newPosition - 40;
    } else {
        position = newPosition;
    }
}

void Player::back(int moves) {
    int newPosition = position + moves;
    if (newPosition < 0) {
        position = 40 + newPosition;
    } else {
        position = newPosition;
    }
}

void Player::setPosition(int position) {
    this->position = position;
}

void Player::disableRoll() {
    canRoll = false;
}

void Player::enableRoll() {
    canRoll = true;
}


void Player::goToTimsLine() {
    position = 10;
    isInLine = true;
}

void Player::goToOSAP() {
    position = 0;
}

// the player will always be able to pay the money since the bankrupt logic is handled within the squares
void Player::payMoney(int amount) {
    money -= amount;
    networth -= amount;
}

void Player::gainMoney(int amount) {
    money += amount;
    networth += amount;
}

bool Player::hasMonoply(string block) {
    int count = 0;
    for(auto &p: properties) {
        if (p.first.second == block) count += 1;
    }
    if (block == "Arts1" || block == "Math") {
        if (count == 2) {
            return true;
        }
    } else {
        if(count == 3) {
            return true;
        }
    }
    return false;
}

void Player::addBuilding(int position, string name, string block, int cost) {
    properties[make_pair(name, block)] = position;
    networth += cost;
}

void Player::removeBuilding(string name, string block, int cost) {
    properties.erase(make_pair(name, block));
    networth -= cost;
    
}

void Player::receiveRimCup() {
    rimCups += 1;
}

void Player::reduceRimCup() {
    rimCups -= 1;
}

void Player::returnBlockPos(vector<int>& v, string block) {
    for(auto &p: properties) {
        if (p.first.second == block) {
            v.emplace_back(p.second);
        }
    }
}

void Player::returnAllProperties(std::vector<int>& v) {
    for(auto &p: properties) {
        v.emplace_back(p.second);
    }
}
