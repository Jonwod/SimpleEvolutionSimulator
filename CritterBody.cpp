//
//  Critter.cpp
//  Evolve
//
//  Created by Jonathan Wood on 07/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#include "CritterBody.hpp"
#include "World.hpp"
#include "EMath.hpp"
#include <iostream>


CritterBody::CritterBody(){
    mainCircle.setOutlineColor({0,0,0,255});
    mainCircle.setOutlineThickness(4.0f);
    stomachCircle.setFillColor({0,0,0,255});
    setColor({255, 255, 0, 255});
    
    setSize(50.0f);
    //velocity = sf::Vector2f(100, 100);
    setPropelling(false);
}


void CritterBody::applyForce(const sf::Vector2f & force, float deltaT){
    velocity += (force * deltaT) / getSize();
}


void CritterBody::update(float deltaTime, std::vector<CritterInfo> crittersToEat, std::vector<PlantInfo> plantsToEat){
    if(nutritionLevel > 0){
        bool eatCritter = false;
        if(crittersToEat.size()){
            if(CritterBody * critterTarget = World::get().getFirstOverlappingCritterWithTraits(*this, crittersToEat)){
                eatOtherCritter(*critterTarget);
                eatCritter = true;
            }
        }
        
        if(!eatCritter && plantsToEat.size()){
            if(Plant * plantTarget = World::get().getFirstOverlappingPlantWithTraits(getPosition(), getSize(), plantsToEat)){
                eatPlant(*plantTarget);
            }
        }
        
        if(isPropelling){
            propel(deltaTime);
        }
        metabolize(deltaTime);
        applyDampingDecceleration(deltaTime);
        move(velocity * deltaTime);
        //addNutrition(15.0f * deltaTime);
    }
}


void CritterBody::move(const sf::Vector2f & offset){
    mainCircle.move(offset);
    stomachCircle.setPosition(mainCircle.getPosition());
}

void CritterBody::setPosition(const sf::Vector2f & newPos){
    mainCircle.setPosition(newPos);
    stomachCircle.setPosition(newPos);
}
sf::Vector2f CritterBody::getPosition() const{
    return mainCircle.getPosition();
}


bool CritterBody::eatPlant(Plant & plant){
    if(overlaps(plant)){
        addNutrition(plant.getNutritionLevel() * getPlantEatEfficiency());
        World::get().destroy(plant);
        return true;
    }
    return false;
}

bool CritterBody::eatOtherCritter(CritterBody & otherCritter){
    if(overlaps(otherCritter)  &&  otherCritter.getNutrition() > 0){
        const float chanceToWin = pow(getSize(), 4) / (pow(getSize(), 4) + pow(otherCritter.getSize(), 4));
        if(EMath::randFloatClamped() < chanceToWin){
            addNutrition(otherCritter.getNutrition());
            otherCritter.setNutrition(-10.0f);
        }
        else{
            otherCritter.addNutrition(getNutrition());
            setNutrition(-10.0f);
        }
        return true;
    }
    return false;
}



void CritterBody::setSize(float newSize){
    mainCircle.setRadius(newSize);
    mainCircle.setOrigin(newSize, newSize);
    //This should perhaps not be here in future?
    nutritionLevel = newSize;
    //Update the stomatch size
    updateStomachCircleSize();
}

void CritterBody::setNutrition(float newNutrition){
    nutritionLevel = newNutrition;
    updateStomachCircleSize();
}


void CritterBody::setPropulsionDirection(sf::Vector2f direction){
    propulsionDirection = EMath::safeNormal(direction);
}

float CritterBody::calculateMaxSpeed(){
    //The point at which velocity reduction per second equals velocity addition per second
    //Velocity addition /s = propulsionForce / size
    //Velocity reduction /s = velocity * dampingDecceleration
    return getPropulsionForce() / (getSize() * damping);
}

void CritterBody::updateStomachCircleSize(){
    const float ratioOfSizeToMain = 1.0f - getNutrition() / nutritionRequiredToReproduce();
    const float clampedRatio = EMath::clamp(ratioOfSizeToMain, 0.05f, 1.0f);
    const float newRadius = clampedRatio * getSize();
    stomachCircle.setRadius(newRadius);
    stomachCircle.setOrigin(stomachCircle.getRadius(), stomachCircle.getRadius());
}


void CritterBody::applyDampingDecceleration(float deltaT){
    velocity -= velocity * damping * deltaT;
}

void CritterBody::propel(float deltaT){
    velocity += (propulsionDirection * propulsionForce * deltaT) / getSize();
}

void CritterBody::metabolize(float deltaT){
    addNutrition(-baseMetabolismPerUnitSize * getSize() * deltaT);
}


//Can always make more interesting later
float CritterBody::getPlantEatEfficiency(){
    return 1.0f;
}

