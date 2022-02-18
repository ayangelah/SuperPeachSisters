#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject {
public:
    Actor(int imageID, int graphicalDepth, StudentWorld* sw, int x, int y);
    virtual ~Actor() = 0;
    virtual void doSomething() = 0;
    void changeAliveStatus(bool isAlive) {
        notDead = isAlive;
    }
    StudentWorld* getWorld();
    bool isAlive() {
        return true;
    }
private:
    StudentWorld* m_world;
    bool notDead;
};

class Peach: public Actor {
public:
    Peach(StudentWorld* sw, int x, int y);
    virtual ~Peach();
    virtual void doSomething();
private:
//    StudentWorld* m_world;
};

class Block: public Actor {
public:
    Block(StudentWorld* sw, int x, int y);
    virtual ~Block();
    virtual void doSomething();
    void bonk();
private:
    StudentWorld* m_world;
};

class Pipe: public Block {
    
};


#endif // ACTOR_H_
