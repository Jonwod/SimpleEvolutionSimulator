//
//  BrainDataStructs.h
//  Evolve
//
//  Created by Jonathan Wood on 03/07/2017.
//  Copyright © 2017 Jonathan Wood. All rights reserved.
//

#ifndef BrainDataStructs_h
#define BrainDataStructs_h
#include "EMath.hpp"

struct CritterInfo{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float size;
};

struct PlantInfo{
    sf::Vector2f postion;
};

#endif /* BrainDataStructs_h */
