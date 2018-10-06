//
//  PlantGrid.cpp
//  Evolve
//
//  Created by Jonathan Wood on 02/07/2017.
//  Copyright © 2017 Jonathan Wood. All rights reserved.
//
#include <iostream>
#include "PlantGrid.hpp"

PlantGrid::PlantGrid()
{
    
}

PlantGrid::PlantGrid(sf::Vector2f initPosition, float initSquareSize, sf::Vector2i squares)
:position(initPosition)
,squareSize(initSquareSize)
,grid(squares.x)
{
    //grid already has squares.x rows
    for(int x = 0; x < squares.x; ++x){
        //push make a collumn of empty vectors y tall for each row
        for(int y = 0; y < squares.y; ++y){
            grid[x].push_back(std::vector<Plant*>());
        }
    }
}

void PlantGrid::addPlant(Plant& plantToAdd){
    const sf::Vector2i gridCoords = calcGridLocation(plantToAdd.getPosition());
    grid[gridCoords.x][gridCoords.y].push_back(&plantToAdd);
    //std::cout<<"plant added to grid at: "<<EMath::toString(gridCoords)<<std::endl<<std::endl;
}

void PlantGrid::removePlant(Plant& plantToRemove){
    const sf::Vector2i gridCoords = calcGridLocation(plantToRemove.getPosition());
    for(int i = 0 ; i < grid[gridCoords.x][gridCoords.y].size(); ++i){
        if(grid[gridCoords.x][gridCoords.y][i] == &plantToRemove){
            grid[gridCoords.x][gridCoords.y].erase(grid[gridCoords.x][gridCoords.y].begin() + i);
        }
    }
}



sf::Vector2i PlantGrid::calcGridLocation(const sf::Vector2f & worldSpacePos){
    const sf::Vector2f gridSpacePosition = worldSpacePos - position;
    const sf::Vector2i gridCoords = sf::Vector2i(gridSpacePosition.x/squareSize, gridSpacePosition.y/squareSize);
    return gridCoords;
}


std::vector<Plant*> PlantGrid::getPlantsInCellAndAdjacentCells(sf::Vector2i coords){
    std::vector<Plant*> retArray{};
    
    for(int x = coords.x-1; x < (coords.x+2); ++x){
        for(int y = coords.y - 1; y < (coords.y +2); ++y){
            if(coords.x > 0  &&  coords.y>0  &&  coords.x<grid.size()  &&  coords.y<grid[x].size()){
                retArray.insert(retArray.end(), grid[coords.x][coords.y].begin(), grid[coords.x][coords.y].end());
                //std::cout<<"testing cell "<<EMath::toString(sf::Vector2i(x, y));
            }
        }
    }
    std::cout<<std::endl;
    return retArray;
}

