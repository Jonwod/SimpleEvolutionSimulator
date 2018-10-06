//
//  World.hpp
//  Evolve
//
//  Created by Jonathan Wood on 07/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <vector>
#include<SFML/Graphics.hpp>
#include "Critter.hpp"
#include "Plant.hpp"
#include "PlantGrid.hpp"

//A singleton
class World{
public:
    //access the instance
    inline static World & get(){
        static World instance;
        return instance;
    }
    void spawnCritter(const Critter & templateCritter);
    void spawnPlant(const Plant & templatePlant);
    void update(float deltaTime);
    void draw(sf::RenderWindow & window);
    void destroy(Plant & plant);
    void destroy(Critter & critter);
    std::vector<Plant*> getOverlappingPlants(sf::Vector2f position, float radius);
    std::vector<CritterBody*> getOverlappingCritters(CritterBody & critter);
    std::vector<CritterBody*> getOverlappingCritters(sf::Vector2f position, float radius);
    //First critter that overlaps with testCritter, but isn't testCritter and has traits
    CritterBody* getFirstOverlappingCritterWithTraits(const CritterBody & testCritter, std::vector<CritterInfo> traits);
    Plant* getFirstOverlappingPlantWithTraits(sf::Vector2f position, float radius, std::vector<PlantInfo> traits);
private:
    std::vector<Critter> allCritters;
    std::vector<Plant> allPlants;
    std::vector<Critter> crittersPendingSpawn;
    std::vector<Critter*> crittersPendingDestroy;
    std::vector<Plant> plantsPendingSpawn;
    std::vector<Plant*> plantsPendingDestroy;
    sf::FloatRect inhabitableZone;
    //For efficient collision detection against obnoxious numbers of plants
    PlantGrid plantGrid;
    int maxPlants = 3000;
    void updateSpontaneousPlantSpawning(float deltaSeconds);
    void spontaneouslySpawnPlant();
    //Just prevents ecosystem dying once all the plants are gone
    int plantNumBelowWhichToSpontaneousSpawn = 200;
    float plantSpontaneousSpawnRate = 2.0f;
    float timeSinceSpontaneousPlantSpawn = 0.0f;
    World(); // Prevent construction
    World(const World&){}; // Prevent construction by copying
    World& operator=(const World&){return *this;}; // Prevent assignment
    ~World(){}; // Prevent unwanted destruction
};

#endif /* World_hpp */
