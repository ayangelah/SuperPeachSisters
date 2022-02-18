#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include "Actor.h"
using namespace std;

class Actor;
class Peach;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    void levelBuild();
    virtual int init(); //initializes levels
    virtual int move(); //plays a tick
    virtual void cleanUp(); //cleans up all objects at the end of levels.

private:
    vector<Actor*> m_otherCast; //blocks,pipes,flags,mario,enemies
    Peach* m_peach;
};

#endif // STUDENTWORLD_H_
