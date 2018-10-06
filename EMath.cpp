//
//  EMath.cpp
//  Evolve
//
//  Created by Jonathan Wood on 08/10/2016.
//  Copyright © 2016 Jonathan Wood. All rights reserved.
//

#include "EMath.hpp"
#include <iostream>

namespace EMath {
    int randInt(int n1, int n2){
        return  rand() % (n2-n1) +n1;
    }

    float randFloatClamped(){
        float rndfltcmp = float(randInt(0, 100000) / 100000.0f);
        return rndfltcmp;
    }
    
    float randFloat(float n1, float n2){
        return randFloatClamped() * (n2 - n1) + n1;
    }
}


//n1 = -1000
//n2 = 2000
//n2 - n1 = 3000
//3000 * 1 - 1000 = 2000
//3000 * -1  -1000 = -4000