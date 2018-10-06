//
//  World.cpp
//  Evolve
//
//  Created by Jonathan Wood on 07/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#include <iostream>
#include "World.hpp"


void World::spawnCritter(const Critter & templateCritter){
    crittersPendingSpawn.push_back(templateCritter);
}


void World::spawnPlant(const Plant & templatePlant){
    if(allPlants.size() < maxPlants){
        if(inhabitableZone.contains(templatePlant.getPosition())){
            plantsPendingSpawn.push_back(templatePlant);
        }
        //if plant tries to spawn outside inhabitable zone, just don't spawn it. It'd die anyway
    }
}



void resolveCritterCollision(Critter & a, Critter & b, float deltaT){
    const sf::Vector2f aTob = b.body.getPosition() - a.body.getPosition();
    sf::Vector2f aTobNormal;
    if(EMath::magnitude(aTob) > 0.01f){
        aTobNormal = EMath::normal(aTob);
    }
    else{
        aTobNormal = {1, 0};
    }
    a.body.applyForce(CritterBody::collisionResolutionForce * -aTob, deltaT);
    b.body.applyForce(CritterBody::collisionResolutionForce * aTob, deltaT);
}

void resolveCritterCollisions(std::vector<Critter> & critters, float deltaT){
    for(int i = 0; i < critters.size(); ++i){
        for(int j = i + 1; j < critters.size(); ++j){
            if(critters[i].body.overlaps(critters[j].body)){
                resolveCritterCollision(critters[i], critters[j], deltaT);
            }
        }
    }
}

void World::update(float deltaTime){
    updateSpontaneousPlantSpawning(deltaTime);
    for(int i = 0; i < allCritters.size(); ++i){
        allCritters[i].update(deltaTime);
    }
    resolveCritterCollisions(allCritters, deltaTime);
    for(int i = 0; i < allPlants.size(); ++i){
        allPlants[i].update(deltaTime);
    }
    for(Critter * critterToDestroy: crittersPendingDestroy){
        EMath::eraseObjectFromArray(allCritters, *critterToDestroy);
    }
    for(Plant * plantToDestroy: plantsPendingDestroy){
        EMath::eraseObjectFromArray(allPlants, *plantToDestroy);
    }
    for(Critter & templateCritter: crittersPendingSpawn){
        allCritters.push_back(templateCritter);
    }
    for(Plant & templatePlant: plantsPendingSpawn){
        allPlants.push_back(templatePlant);
        //std::cout<<"plant spawned at: "<<EMath::toString(allPlants.back().getPosition())<<std::endl;
        plantGrid.addPlant(allPlants.back());
    }
    crittersPendingDestroy.clear();
    plantsPendingDestroy.clear();
    crittersPendingSpawn.clear();
    plantsPendingSpawn.clear();
}

void World::draw(sf::RenderWindow &window){
    sf::FloatRect viewRect;
    viewRect.left = window.getView().getCenter().x - window.getView().getSize().x / 2.0f;
    viewRect.top = window.getView().getCenter().y - window.getView().getSize().y / 2.0f;
    viewRect.width = window.getView().getSize().x;
    viewRect.height = window.getView().getSize().y;
    for(Critter & critter: allCritters){
        if(critter.body.getVisualBounds().intersects(viewRect)){
            critter.body.draw(window);
        }
    }
    for(Plant & plant: allPlants){
        if(plant.getVisualBounds().intersects(viewRect)){
            plant.draw(window);
        }
    }
}


void World::destroy(Plant & plant){
    plantsPendingDestroy.push_back(&plant);
    plantGrid.removePlant(plant);
}

void World::destroy(Critter & critter){
    crittersPendingDestroy.push_back(&critter);
}


std::vector<Plant*> World::getOverlappingPlants(sf::Vector2f position, float radius){
//    sf::Vector2i critterGridPos = plantGrid.calcGridLocation(critter.getPosition());
//    std::vector<Plant*> plantsInAdjacentCells = plantGrid.getPlantsInCellAndAdjacentCells(critterGridPos);
//    
//    std::cout<<"critter in cell "<<EMath::toString(critterGridPos)<<" at pos "<<EMath::toString(critter.getPosition())<<"    num plants in cell: "<<plantsInAdjacentCells.size()<<std::endl;
    
    std::vector<Plant*> retArray{};
//    for(int i = 0; i < plantsInAdjacentCells.size(); ++i){
//        if(critter.overlaps(*plantsInAdjacentCells[i])){
//            retArray.push_back(plantsInAdjacentCells[i]);
//        }
//        else{
//            std::cout<<"no overlap, distance "<<EMath::magnitude(plantsInAdjacentCells[i]->getPosition() - critter.getPosition())<< "\n";
//        }
//    }
    
    for(int i = 0; i < allPlants.size(); ++i){
        const float distanceBetween = EMath::magnitude(allPlants[i].getPosition() - position);
        if(distanceBetween < (radius + allPlants[i].getSize())){
            retArray.push_back(&allPlants[i]);
        }
    }
    
    return retArray;
}


std::vector<CritterBody*> World::getOverlappingCritters(CritterBody & critter){
    std::vector<CritterBody*> retArray{};
    for(int i = 0; i < allCritters.size(); ++i){
        if(critter.overlaps(allCritters[i].body) && &critter != &allCritters[i].body){
            retArray.push_back(&allCritters[i].body);
        }
    }
    return retArray;
}


std::vector<CritterBody*> World::getOverlappingCritters(sf::Vector2f position, float radius){
    std::vector<CritterBody*> retArray{};
    for(int i = 0; i < allCritters.size(); ++i){
        const float distanceBetween = EMath::magnitude(allCritters[i].body.getPosition() - position);
        if(distanceBetween < (radius + allCritters[i].body.getSize())){
            retArray.push_back(&allCritters[i].body);
        }
    }
    return retArray;
}


CritterBody* World::getFirstOverlappingCritterWithTraits(const CritterBody & testCrit, std::vector<CritterInfo> traitList){
    for(int i = 0; i < allCritters.size(); ++i){
        const float distanceBetween = EMath::magnitude(allCritters[i].body.getPosition() - testCrit.getPosition());
        if((distanceBetween < (testCrit.getSize() + allCritters[i].body.getSize()))){
            for(CritterInfo & traits: traitList){
                if(allCritters[i].body.matchesTraits(traits.color, traits.size))
                    return &allCritters[i].body;
            }
        }
    }
    return nullptr;
}


Plant* World::getFirstOverlappingPlantWithTraits(sf::Vector2f position, float radius, std::vector<PlantInfo> traitList){
    std::vector<Plant*> retArray{};

    for(int i = 0; i < allPlants.size(); ++i){
        const float distanceBetween = EMath::magnitude(allPlants[i].getPosition() - position);
        if(distanceBetween < (radius + allPlants[i].getSize())){
            for(PlantInfo & traits: traitList){
                if(traits.postion  ==  allPlants[i].getPosition())
                    return &allPlants[i];
            }
        }
    }
    
    return nullptr;
}



void World::updateSpontaneousPlantSpawning(float deltaSeconds){
    if(allPlants.size() < plantNumBelowWhichToSpontaneousSpawn  &&  timeSinceSpontaneousPlantSpawn >= 1.0f / plantSpontaneousSpawnRate){
        spontaneouslySpawnPlant();
        timeSinceSpontaneousPlantSpawn = 0.0f;
    }
    timeSinceSpontaneousPlantSpawn += deltaSeconds;
}

void World::spontaneouslySpawnPlant(){
    float randX = EMath::randInt(inhabitableZone.left, inhabitableZone.left + inhabitableZone.width);
    float randY = EMath::randInt(inhabitableZone.top, inhabitableZone.top + inhabitableZone.height);
    Plant plantTemplate{};
    plantTemplate.setPosition({randX, randY});
    spawnPlant(plantTemplate);
}

World::World()
:allCritters{}
,inhabitableZone(-5000, -5000, 10000, 10000)
{
    const float squareSize = 500.f;
    const sf::Vector2f plantgridPos{inhabitableZone.left - squareSize, inhabitableZone.top - squareSize};
    //+2 so that there are cells surrounding habitable zone with no plants. +1 in case rounds down
    const int plantGridNumCells = (inhabitableZone.width / squareSize) + 3;
    plantGrid = PlantGrid(plantgridPos, squareSize, {plantGridNumCells, plantGridNumCells});
    
    Critter critter{};
    critter.body.setSize(50.0f);
    critter.body.setPosition({200, 200});
    critter.body.setNutrition(critter.body.getSize());
    critter.body.setColor({125, 125, 125, 255});
    critter.body.setPropulsionForce(50000.0f);
    critter.body.addNutrition(100.0f);
    spawnCritter(critter);
    
    
    Plant plant{};
    plant.setPosition({400.0f, 400.0f});
    spawnPlant(plant);
    
    Plant plant2{};
    plant2.setPosition({0, 400.0f});
    spawnPlant(plant2);
}

