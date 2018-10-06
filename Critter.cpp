//
//  Critter.cpp
//  Evolve
//
//  Created by Jonathan Wood on 08/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#include "Critter.hpp"
#include "World.hpp"


void Critter::update(float deltaT){
    eye.update(deltaT, body.getPosition());
    BrainOutput brainOutput = brain.think({body.getPosition(), body.getVelocity(), body.getNutrition(), eye.getPerceivedCritters() , eye.getPerceivedPlants()}) ;
    
    body.setPropelling(brainOutput.shouldPropel);
    body.setPropulsionDirection(brainOutput.propulsionDirection);
    
    std::vector<CritterInfo> crittersWouldLikeToEat{};
    for(int i = 0; i < brainOutput.shouldEatPerceivedCritter.size(); ++i){
        if(brainOutput.shouldEatPerceivedCritter[i])
            crittersWouldLikeToEat.push_back(eye.getPerceivedCritters()[i]);
    }
    
    std::vector<PlantInfo> plantsWouldLikeToEat{};
    for(int i = 0; i < brainOutput.shouldEatPerceivedPlant.size(); ++i){
        if(brainOutput.shouldEatPerceivedPlant[i])
            plantsWouldLikeToEat.push_back(eye.getPerceivedPlants()[i]);
    }
    
    body.update(deltaT, crittersWouldLikeToEat, plantsWouldLikeToEat);
    
    if(body.getNutrition() >= body.nutritionRequiredToReproduce()){
        reproduce();
    }
    else if(body.getNutrition() <= 0.0f){
        World::get().destroy(*this);
    }
}



void Critter::reproduce(){
    Critter offspring{};
    setOffspringTraits(offspring);
    sf::Vector2f randDirection{EMath::randFloat(-100.0f, 100.0f), EMath::randFloat(-100.0f, 100.0f)};
    randDirection = EMath::safeNormal(randDirection);
    offspring.body.setPosition(body.getPosition() + randDirection * (body.getSize() + +offspring.body.getSize()) * 1.5f);
    World::get().spawnCritter(offspring);
    body.setNutrition(body.getNutrition()/2.0f);
}

void Critter::setOffspringTraits(Critter & offspring){
    float randSize = body.getSize() * randTraitMultiplier();
    if(randSize < CritterBody::minimumSize){
        randSize = CritterBody::minimumSize;
    }
    offspring.body.setSize(randSize);
    offspring.body.setNutrition(body.getNutrition()/2.0f);
    float forceChangeWithSize = offspring.body.getSize() / body.getSize();
    offspring.body.setPropulsionForce(body.getPropulsionForce() * randTraitMultiplier() * forceChangeWithSize);
    
    const sf::Uint8 r = body.getColor().r + EMath::randInt(-2, 2);
    const sf::Uint8 g = body.getColor().g + EMath::randInt(-2, 2);
    const sf::Uint8 b = body.getColor().b + EMath::randInt(-2, 2);
    offspring.body.setColor(sf::Color{r,g,b});
}
