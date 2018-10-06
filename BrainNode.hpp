//
//  BrainNode.hpp
//  Evolve
//
//  Created by Jonathan Wood on 06/07/2017.
//  Copyright © 2017 Jonathan Wood. All rights reserved.
//

#ifndef BrainNode_hpp
#define BrainNode_hpp

#include <stdio.h>
#include <vector>
#include <cmath>



//Base node
//Has one optional input, otherwise will default to 0
class BrainNode{
public:
    BrainNode()
    :inputNodes{nullptr}
    {
    }
    
    virtual float execute(){
        if(inputNodes.size() && inputNodes[0]){
             return inputNodes[0]->execute();
        }
        return 0.0f;
    }
    
    unsigned long getNumInputs(){
        return inputNodes.size();
    }
    
    void setInputNode(int index, BrainNode * newInputNode);
protected:
    std::vector<BrainNode *> inputNodes;
};

//A single value, which can be set externally to the node network
//No inputs, so can be at the start of a node chain
class InputBrainNode: public BrainNode{
public:
    virtual float execute() override{
        return value;
    }
private:
    float value;
};


class AndNode: public BrainNode{
public:
    AndNode()
    {
        inputNodes = std::vector<BrainNode*>{nullptr, nullptr};
    }
    
    virtual float execute() override{
        const float a = inputNodes[0] ? inputNodes[0]->execute() : 0.f;
        const float b = inputNodes[1] ? inputNodes[1]->execute() : 0.f;
        return a  &&  b;
    }
};


class GreaterThanNode: public BrainNode{
public:
    GreaterThanNode(){
        inputNodes = std::vector<BrainNode*>{nullptr, nullptr};
    }
    
    virtual float execute() override{
        const float a = inputNodes[0] ? inputNodes[0]->execute() : 0.f;
        const float b = inputNodes[1] ? inputNodes[1]->execute() : 0.f;
        return a > b;
    }
};
        

class SumNode: public BrainNode{
public:
    SumNode(){
        inputNodes = std::vector<BrainNode*>{nullptr, nullptr};
    }
    
    virtual float execute() override{
        const float a = inputNodes[0] ? inputNodes[0]->execute() : 0.f;
        const float b = inputNodes[1] ? inputNodes[1]->execute() : 0.f;
        return a + b;
    }
};
        
class SizeNode: public BrainNode{
public:
    SizeNode(){
        inputNodes = std::vector<BrainNode*>{nullptr, nullptr};
    }
    
    virtual float execute() override{
        const float x = inputNodes[0] ? inputNodes[0]->execute() : 0.f;
        const float y = inputNodes[1] ? inputNodes[1]->execute() : 0.f;
        return sqrt(x * x  +  y * y);
    }
};

        
//Set a number of inputs, which will populate input nodes
//These can then be set
class BrainNodeNetwork{
public:
    BrainNodeNetwork(unsigned int numInputs);
    BrainNodeNetwork( const BrainNodeNetwork &obj);
    ~BrainNodeNetwork();
    float exectute();
    void setInput(unsigned int index, float value);
    
    template<typename T>
    void addNewNode(){
        nodes.push_back(new T);
    }
private:
    BrainNode outputNode;
    std::vector<InputBrainNode> inputNodes;
    std::vector<BrainNode*> nodes;
};

#endif /* BrainNode_hpp */
