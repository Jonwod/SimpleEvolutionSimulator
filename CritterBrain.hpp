//
//  CritterBrain.hpp
//  Evolve
//
//  Created by Jonathan Wood on 08/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#ifndef CritterBrain_hpp
#define CritterBrain_hpp

#include <stdio.h>
#include "CritterBody.hpp"
#include "BrainNode.hpp"
#include "BrainDataStructs.h"

struct BrainOutput{
    bool shouldPropel;
    sf::Vector2f propulsionDirection;
    //should map to input vector of plantInfo
    std::vector<bool> shouldEatPerceivedPlant;
    //should map to input vector of critterInfo
    std::vector<bool> shouldEatPerceivedCritter;
};

struct BrainInput{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float nutritionLevel;
    std::vector<CritterInfo> perceivedCritters;
    std::vector<PlantInfo> perceivedPlants;
};




class CritterBrain{
public:    
    BrainOutput think(const BrainInput & brainInput);
private:
    std::vector<bool> shouldEatPerceivedCritters(const BrainInput & brainInput);
    bool shouldEatCritter(const CritterInfo & critInfo, sf::Vector2f position, sf::Vector2f velocity, float nutritionLevel);
};

#endif /* CritterBrain_hpp */
