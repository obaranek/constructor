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
    std::vector<int> buildings;
    std::vector<int> roads;
    Dice dice;

  public:
    void stealResources(Builder* otherBuilder);
    void rollDice();
    void tradeResource(Builder* otherBuilder, ResourceType res1, ResourceType res2);
    bool checkResidence(int vertexNum);
    bool checkRoad(int edgeNum);
    void buildResidence(int vertexNum);
    void buildRoad(int edgeNum);
};

#endif // __BUILDER_H_
