//
//  PlantGrid.hpp
//  Evolve
//
//  Created by Jonathan Wood on 02/07/2017.
//  Copyright © 2017 Jonathan Wood. All rights reserved.
//

#ifndef PlantGrid_hpp
#define PlantGrid_hpp

#include <stdio.h>
#include <vector>
#include "EMath.hpp"
#include "Plant.hpp"

class PlantGrid{
public:
    PlantGrid();
    PlantGrid(sf::Vector2f initPosition, float initSquareSize, sf::Vector2i squares);
    void addPlant(Plant& plantToAdd);
    void removePlant(Plant& plantToRemove);
    sf::Vector2i calcGridLocation(const sf::Vector2f & worldSpacePos);
    std::vector<Plant*> getPlantsInCellAndAdjacentCells(sf::Vector2i cellCoords);
private:
    //The top left coordinates
    sf::Vector2f position;
    float squareSize;
    std::vector<std::vector<std::vector<Plant*>>> grid;
};

#endif /* PlantGrid_hpp */
