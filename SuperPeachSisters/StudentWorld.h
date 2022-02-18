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
    bool overlap(Actor* a, Actor* b);
    inline
    Peach* returnPeach() {
        return m_peach;
    }
    inline
    vector<Actor*> returnCast() {
        return m_otherCast;
    }
    virtual int init(); //initializes levels
    virtual int move(); //plays a tick
    virtual void cleanUp(); //cleans up all objects at the end of levels.

private:
    vector<Actor*> m_otherCast; //blocks,pipes,flags,mario,enemies
    Peach* m_peach;
};

#endif // STUDENTWORLD_H_
