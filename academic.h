#ifndef ACADEMIC_H
#define ACADEMIC_H

#include <map>
#include <string>
#include "ownable.h"

class Player;

class Academic: public Ownable {
    const int implCost;
    int numOfImprovements;
    int tuitions[6];
    bool inMonopoly = false;
    
    // calculates the tuition owed
    int getTuition();
    public:
        int getNumberOfImprovements();

        int getImprovementCost();

        bool isInMonopoly();

        // bool isMortgaged();

        // void mortgageProperty();

        // void unmortgageProperty();

        void changeMonopoly(bool b);

        Academic(int position, std::string name, std::string block, std::string type, int cost, int implCost, int numOfImprovements,
            int baseTuition, int oneImplTuition, int twoImplTuition, int threeImplTuition,
            int fourImplTuition, int fiveImplTuition);

        void accept(Player& p);

        void addImprovement(); 

        void setImprovements(int num);

        void reduceImprovement();   

        void resetImprovements();
};

#endif
