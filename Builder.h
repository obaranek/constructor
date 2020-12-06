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
    char dice; //dice can be either F or L. It is L at the start of the game

  public:
    // TODO: Change raw pointers to smart pointers?
    //void stealResources(Builder* otherBuilder);
    

    // checkResidenceResource() returns true if 
    // builder has enough resources to build a basement
    bool checkResidenceResources();
    
    // checkRoadResource() returns true if 
    // builder has enough resources to build a road
    bool checkRoadResources();
    
    // buildResidence() adds verexNum to list of buildings
    void buildResidence(int vertexNum);
    
    // buildRoad() adds edgeNum to list of roads
    void buildRoad(int edgeNum);
    
    // improveResidence() updates building in buildings with new type
    void updateResidence(int vertexNum, char residenceType);

    //takeResources() adds the quantity of resource to builders resources
    void takeResources(ResourceType type, int reward);

    // haveRoad() returns true if currBuilder owns a road at the edgeNum
    bool haveRoad(int edgeNum);

    /***** Getters and Setters *****/

    Colour getColour();
    int getPoints();

    void setDice(char diceType);
};

#endif // __BUILDER_H_
