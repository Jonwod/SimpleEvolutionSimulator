//
//  Plant.cpp
//  Evolve
//
//  Created by Jonathan Wood on 09/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#include "Plant.hpp"
#include "World.hpp"

Plant::Plant(){
    setSize(10.0f);
    visualShape.setFillColor({17,255,12,230});
    visualShape.setOutlineThickness(2);
    visualShape.setOutlineColor({0,0,0,255});
}

void Plant::setSize(float radius){
    visualShape.setRadius(radius);
    visualShape.setOrigin(radius, radius);
}

void Plant::update(float deltaT){
    const float photosynthAdd = photosynthesisRate * deltaT;
    nutritionLevel += photosynthAdd + photosynthAdd * EMath::randFloat(-photosynthesisRateRandomDrift, photosynthesisRateRandomDrift);
    if(nutritionLevel >= nutritionRequiredToReproduce){
        reproduce();
    }
}

void Plant::draw(sf::RenderWindow &renderWindow){
    renderWindow.draw(visualShape);
}


void Plant::reproduce(){
    Plant offspring{};
    //I can't remember if my rand function works for negative ranges
    const int randX = EMath::randInt( 0, 2 * offspringSpawnRadius) - offspringSpawnRadius;
    const int randY = EMath::randInt( 0, 2 * offspringSpawnRadius) - offspringSpawnRadius;
    offspring.setPosition(getPosition() + sf::Vector2f(randX, randY));
    offspring.setNutritionLevel(getNutritionLevel()/2);
    World::get().spawnPlant(offspring);
    nutritionLevel = getNutritionLevel() / 2.0f;
}
