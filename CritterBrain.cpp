//
//  CritterBrain.cpp
//  Evolve
//
//  Created by Jonathan Wood on 08/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#include "CritterBrain.hpp"
#include "World.hpp"




BrainOutput CritterBrain::think(const BrainInput & brainInput)
{
    BrainOutput output{};
    
    output.shouldPropel = true;
    
    float randX = ((EMath::randInt(1.0f, 10.0f)/10.0f) - 0.5f) * 2.0f;
    float randY = ((EMath::randInt(1.0f, 10.0f)/10.0f) - 0.5f) * 2.0f;
    output.propulsionDirection = {randX, randY};
    
    output.shouldEatPerceivedCritter = shouldEatPerceivedCritters(brainInput);
    
    
    std::vector<bool> shouldEatPlants{};
    for(const PlantInfo & plantInfo: brainInput.perceivedPlants){
        output.shouldEatPerceivedPlant.push_back(true);
    }

    return output;
}


std::vector<bool> CritterBrain::shouldEatPerceivedCritters(const BrainInput & brainInput){
    std::vector<bool> output;
    for(const CritterInfo & critInfo: brainInput.perceivedCritters){
        output.push_back(shouldEatCritter(critInfo, brainInput.position, brainInput.velocity, brainInput.nutritionLevel));
    }
    return output;
}


bool CritterBrain::shouldEatCritter(const CritterInfo & critInfo, sf::Vector2f position, sf::Vector2f velocity, float nutritionLevel){
    return 0.0f;
}
