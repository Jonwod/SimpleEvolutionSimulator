//
//  Plant.hpp
//  Evolve
//
//  Created by Jonathan Wood on 09/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#ifndef Plant_hpp
#define Plant_hpp

#include <stdio.h>
#include<SFML/Graphics.hpp>


//Gains nutrition though photosynthsis (passively)
class Plant{
public:
    Plant();
    inline void setPosition(sf::Vector2f newPosition){
        visualShape.setPosition(newPosition);
    }
    inline sf::Vector2f getPosition()const{
        return visualShape.getPosition();
    }
    //plants are currently square
    //size will be half a length
    void setSize(float size);
    inline float getSize()const{
        return visualShape.getRadius();
    }
    void update(float deltaT);
    void draw(sf::RenderWindow & renderWindow);
    inline void setNutritionLevel(float newNutritionLevel){
        nutritionLevel = newNutritionLevel;
    }
    inline float getNutritionLevel(){
        return nutritionLevel;
    }
    //Pre-compilation settings
    //When nutrition level reaches level, plant can reproduce
    constexpr static const float nutritionRequiredToReproduce = 15.0f;
    constexpr static const float photosynthesisRate = 1.75f;
    //will vary photosynthesis per frame by this value in either direction
    constexpr static const float photosynthesisRateRandomDrift = 0.1f;
    //The radius (or perhaps square) within which offspring will spawn randomly
    constexpr static const float offspringSpawnRadius = 300.0f;
    
    inline sf::FloatRect getVisualBounds(){
        return visualShape.getGlobalBounds();
    }
private:
    void reproduce();
    sf::CircleShape visualShape;
    //Plants do not die when nutrition reaches 0
    float nutritionLevel = 0;
};

#endif /* Plant_hpp */
