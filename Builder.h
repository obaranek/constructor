#ifndef __BUILDER_H_
#define __BUILDER_H_

#include<vector>
#include<map>

class Colour;
//enum ResourceType;
class Dice;

class Builder{
  private:
    Colour colour;
    int points;
    std::map<ResourceType, int> resources;
    std::map<int, char> buildings; // map of <vertexNum, buildingType>
    std::vector<int> roads;
    Dice dice;

  public:
    // TODO: Change raw pointers to smart pointers?
    //void stealResources(Builder* otherBuilder);
    //void rollDice();
    //void tradeResource(Builder* otherBuilder, ResourceType res1, ResourceType res2);
    

    // checkResidenceResource() returns true if 
    // builder has enough resources to build a basement
    bool checkResidenceResources();
    
    // checkRoadResource() returns true if 
    // builder has enough resources to build a road
    bool checkRoadResources();
    
    //buildResidence adds verexNum to list of buildings
    void buildResidence(int vertexNum);
    
    
    //void buildRoad(int edgeNum);
    
    void improveResidence(int vertexNum, char residenceType);

    //takeResources() adds the quantity of resource to builders resources
    void takeResources(ResourceType type, int reward);

    Colour getColour();
    int getPoints();
};

#endif // __BUILDER_H_
