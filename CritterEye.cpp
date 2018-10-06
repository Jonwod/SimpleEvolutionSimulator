//
//  CritterEye.cpp
//  Evolve
//
//  Created by Jonathan Wood on 03/07/2017.
//  Copyright © 2017 Jonathan Wood. All rights reserved.
//

#include "CritterEye.hpp"
#include "World.hpp"



void CritterEye::update(float deltaSeconds, sf::Vector2f position){
    timeSincePerceptionUpdate += deltaSeconds;
    
    if(timeSincePerceptionUpdate >= 1.0f/perceptionUpdateFrequency){
        perceivedPlants.clear();
        std::vector<Plant*> seenPlants = World::get().getOverlappingPlants(position, visionRadius);
        for (Plant* plant: seenPlants){
            perceivedPlants.push_back(convertToBrainStruct(*plant));
        }
        
        perceivedCritters.clear();
        std::vector<CritterBody*> seenCritters = World::get().getOverlappingCritters(position, visionRadius);
        for(CritterBody* critBod: seenCritters){
            if(critBod->getPosition() != position)
                perceivedCritters.push_back(convertToBrainStruct(*critBod));
        }
        
        timeSincePerceptionUpdate = 0.f;
    }
}



PlantInfo CritterEye::convertToBrainStruct(const Plant & plant){
    return PlantInfo{plant.getPosition()};
}

CritterInfo CritterEye::convertToBrainStruct(const CritterBody & critterBod){
    return CritterInfo{critterBod.getPosition(), critterBod.getVelocity(), critterBod.getColor(), critterBod.getSize()};
}