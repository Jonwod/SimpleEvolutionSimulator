//
//  Critter.hpp
//  Evolve
//
//  Created by Jonathan Wood on 08/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#ifndef Critter_hpp
#define Critter_hpp

#include <stdio.h>
#include "CritterBody.hpp"
#include "CritterBrain.hpp"
#include "CritterEye.hpp"

//The whole critter!
class Critter{
public:
    void update(float deltaT);
    CritterBody body;
    CritterEye eye;
    CritterBrain brain;
private:
    //Pre-compilation settings
    //Inherited trates adjusted by +- this * val
    constexpr static const float mutationFactor = 0.055f;
    
    void reproduce();
    inline float randTraitMultiplier(){
        const float randFloat =EMath::randFloat(-mutationFactor, mutationFactor);
        const float multiplier = 1.0f + randFloat;
        return multiplier;
    }
    void setOffspringTraits(Critter & offspring);
};

#endif /* Critter_hpp */
