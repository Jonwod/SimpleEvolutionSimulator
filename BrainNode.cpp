//
//  BrainNode.cpp
//  Evolve
//
//  Created by Jonathan Wood on 06/07/2017.
//  Copyright © 2017 Jonathan Wood. All rights reserved.
//

#include "BrainNode.hpp"
#include <iostream>


void BrainNode::setInputNode(int index, BrainNode * newInputNode){
    if(index < inputNodes.size()){        
        inputNodes[index] = newInputNode;
    }
    else{
        std::cout<<"Error! Trying to set input node index in excess of numInputNodes (BrainNode) \n";
    }
}




BrainNodeNetwork::BrainNodeNetwork(unsigned int numInputs){
    for(int i = 0; i < numInputs; ++i){
        inputNodes.push_back(InputBrainNode{});
    }
}


BrainNodeNetwork::BrainNodeNetwork( const BrainNodeNetwork &obj){
        
}


BrainNodeNetwork::~BrainNodeNetwork(){
    for(int i = 0; i < nodes.size(); ++i){
        delete nodes[i];
        nodes[i] = nullptr;
    }
}


float BrainNodeNetwork::exectute(){
    return outputNode.execute();
}

void BrainNodeNetwork::setInput(unsigned int index, float value){
    
}