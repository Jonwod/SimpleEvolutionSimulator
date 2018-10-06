//
//  EMath.hpp
//  Evolve
//
//  Created by Jonathan Wood on 08/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#ifndef EMath_hpp
#define EMath_hpp

#include <stdio.h>
#include <sstream>
#include <cmath>
#include <string>
#include<SFML/Graphics.hpp>
//The math library for this project


namespace EMath{
    //returns clampee clamped between min and max
    template <class T> T clamp(T clampee, T min, T max){
        if(clampee < min){
            clampee = min;
        }
        else if (clampee > max){
            clampee = max;
        }
        return clampee;
    }
    
    template <class T> inline T magnitude(sf::Vector2<T> vec){
        return sqrt(vec.x * vec.x  +  vec.y * vec.y);
    }
    
    //does not check for length 0
    template <class T> sf::Vector2<T> normal(sf::Vector2<T> vec){
        return vec / magnitude(vec);
    }
    
    template <class T> sf::Vector2<T> safeNormal(sf::Vector2<T> vec){
        const float mag = magnitude(vec);
        if(mag > 0.001f){
            return vec / mag;
        }
        return sf::Vector2<T>{};
    }
    
    int randInt(int n1, int n2);
    
    float randFloatClamped();
    
    float randFloat(float n1, float n2);
    
    template<typename T>
    std::string toString(sf::Vector2<T> vec){
        std::stringstream ssx;
        ssx<<vec.x;
        
        std::stringstream ssy;
        ssy<<vec.y;
        
        return "(" + std::string(ssx.str()) + ", " + std::string(ssy.str()) + ")";
    }
    
    //Not really "math", but there you go...
    template<typename T>
    bool eraseObjectFromArray(std::vector<T> & vec, T & object){
        for(int i = 0; i < vec.size(); ++i){
            if(&vec[i] == &object){
                vec.erase(vec.begin() + i);
                return true;
            }
        }
        return false;
    }
}

#endif /* EMath_hpp */
