//
//  CritterEye.hpp
//  Evolve
//
//  Created by Jonathan Wood on 03/07/2017.
//  Copyright © 2017 Jonathan Wood. All rights reserved.
//

#ifndef CritterEye_hpp
#define CritterEye_hpp

#include <stdio.h>
#include "Plant.hpp"
#include "CritterBody.hpp"
#include "BrainDataStructs.h"

//Knows about and sees plants and critters
//Converts that into brain data structures to send to the brain

class CritterEye{
public:
    void update(float deltaSeconds, sf::Vector2f position);
    inline const std::vector<CritterInfo> & getPerceivedCritters(){
        return perceivedCritters;
    }
    inline const std::vector<PlantInfo> & getPerceivedPlants(){
        return perceivedPlants;
    }
private:
    float visionRadius = 1500.f;
    std::vector<CritterInfo> perceivedCritters;
    std::vector<PlantInfo> perceivedPlants;
    
    float perceptionUpdateFrequency = 10.0f;
    
    float timeSincePerceptionUpdate = 0.f;
    
    PlantInfo convertToBrainStruct(const Plant & plant);
    CritterInfo convertToBrainStruct(const CritterBody & plant);
};

#endif /* CritterEye_hpp */
