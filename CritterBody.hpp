//
//  Critter.hpp
//  Evolve
//
//  Created by Jonathan Wood on 07/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#ifndef CritterBody_hpp
#define CritterBody_hpp

#include <cmath>
#include <stdio.h>
#include<SFML/Graphics.hpp>
#include <iostream>
#include "EMath.hpp"
#include "Plant.hpp"
#include "BrainDataStructs.h"

class CritterBody{
public:
    CritterBody();
    void applyForce(const sf::Vector2f & force, float deltaT);
    //vectors are of critters and plants that the brain would like to eat
    void update(float deltaTime, std::vector<CritterInfo> crittersToEat, std::vector<PlantInfo> plantsToEat);
    inline void draw(sf::RenderWindow & window){
        window.draw(mainCircle);
        window.draw(stomachCircle);
    }
    void move(const sf::Vector2f & offset);
    void setPosition(const sf::Vector2f & newPos);
    sf::Vector2f getPosition() const;
    inline void setVelocity(const sf::Vector2f & newVelocity){
        velocity = newVelocity;
    }
    inline sf::Vector2f getVelocity() const{
        return velocity;
    }
    //for convinience
    inline float getSpeed()const{
        return EMath::magnitude(velocity);
    }
    //genetic trait
    void setSize(float radius);
    inline float getSize() const{
        return mainCircle.getRadius();
    }
    void setNutrition(float newNutrition);
    //genetic trait
    inline void setColor(sf::Color newColor){
        mainCircle.setFillColor(newColor);
    }
    inline sf::Color getColor() const{
        return mainCircle.getFillColor();
    }
    inline void addNutrition(float deltaNutrition){
        setNutrition(getNutrition() + deltaNutrition);
    }
    inline float getNutrition() const{
        return nutritionLevel;
    }
    //A genetic trait
    inline void setPropulsionForce(float newPropelForce){
        propulsionForce = newPropelForce;
    }
    inline float getPropulsionForce() const{
        return propulsionForce;
    }
    inline bool overlaps(const CritterBody & otherCritter) const{
        const float distanceBetween = EMath::magnitude(otherCritter.getPosition() - getPosition());
        return distanceBetween < (getSize() + otherCritter.getSize());
    }
    inline bool overlaps(const Plant & plant) const{
        const float distanceBetween = EMath::magnitude(plant.getPosition() - getPosition());
        return distanceBetween < (getSize() + plant.getSize());
    }
    inline bool matchesTraits(sf::Color colorTest, float sizeTest){
        return colorTest == getColor()  &&  sizeTest == getSize();
    }
    //Pre-compilation settings
    //When nutrition level reaches this * size, the critter can reproduce
    constexpr static const float reproduceFactor = 2.0f;
    //Note that size acts as mass here
    //Applied per frame overlapping another critter
    constexpr static const float collisionResolutionForce = 1000.0f;
    //velocity reduced by this factor per second
    constexpr static const float damping = 1.0f;
    //the absolute smallest a critter can evolve to
    constexpr static const float minimumSize = 14.0f;
    //nutrition loss per second per unit size
    constexpr static const float baseMetabolismPerUnitSize = 0.02f;
    //End Pre-compilation settings
    inline float nutritionRequiredToReproduce(){
        return reproduceFactor * getSize();
    }
    
    //Brain action interface
    //Argument doesn't have to be normalized
    void setPropulsionDirection(sf::Vector2f direction);
    inline sf::Vector2f getPropulsionDirection()const{
        return propulsionDirection;
    }
    inline void setPropelling(bool shouldPropell){
        isPropelling = shouldPropell;
    }
    inline bool isCurrentlyPropelling(){
        return isPropelling;
    }
    //returns whether succesfull (i.e if was in range)
    bool eatPlant(Plant & plant);
    
    //Steals it's nutrition
    bool eatOtherCritter(CritterBody & critter);
        
    float calculateMaxSpeed();
    
    inline sf::FloatRect getVisualBounds(){
        return mainCircle.getGlobalBounds();
    }
private:
    //The radius of the colored center as a ratio of the size
    //Currently used to indicate how close the creature is to reproduction
    void updateStomachCircleSize();
    void applyDampingDecceleration(float deltaT);
    void propel(float deltaT);
    void metabolize(float deltaT);
    //from 0 to 1
    float getPlantEatEfficiency();
    sf::CircleShape mainCircle;
    sf::CircleShape stomachCircle;
    sf::Color baseColor;
    sf::Vector2f velocity;
    sf::Vector2f propulsionDirection;
    float propulsionForce;
    bool isPropelling;
    //When it reaches size * reproduceFactor, critter can reproduce. When it reaches 0, critter will die
    //When critter reproduces, nutrition is split between the offspring and itself
    float nutritionLevel;
};

#endif /* CritterBody_hpp */
