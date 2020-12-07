#ifndef __BUILDER_H_
#define __BUILDER_H_

#include<vector>
#include<map>

class Colour;
class ResourceType;

class Builder{
  private:
    Colour colour;
    int points;
    std::map<ResourceType, int> resources;
    std::map<int, char> buildings; // map of <vertexNum, buildingType>
    std::vector<int> roads;
    char dice; //dice can be either F or L. It is L at the start of the game

  public:
    Builder(Colour colour);

    // TODO: Change raw pointers to smart pointers?
    //void stealResources(Builder* otherBuilder);
    

    // buildResidence() adds verexNum to list of buildings
    void buildResidence(int vertexNum);
    
    // buildRoad() adds edgeNum to list of roads
    void buildRoad(int edgeNum);
    
    void updateResidence(int vertexNum, char residenceType);

    //takeResources() adds the quantity of resource to builders resources
    void takeResources(ResourceType type, int reward);

    // haveResidence() returns true if builder owns a residence at the vertexNum
    bool haveResidence(int vertexNum);

    // haveRoad() returns true if builder owns a road at the edgeNum
    bool haveRoad(int edgeNum);

    // checkResources() returns true if builder owns at least
    // the passed in quantity of respective ResourceType
    bool checkResources(std::map<ResourceType,int>& requiredResources);

    /***** Getters and Setters *****/

    Colour getColour();
    int getPoints();
    char getDiceType();
    std::map<ResourceType, int>& getResources();
    std::map<int, char>& getBuildings();
    
    void setDice(char diceType);
};

#endif // __BUILDER_H_
