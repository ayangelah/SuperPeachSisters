#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//ACTOR
Actor::Actor(int imageID, int graphicalDepth, StudentWorld* sw, int x, int y)
: GraphObject(imageID, x, y, 0, 0, 1.0) {
    notDead = true;
}

Actor::~Actor() {
    
}

StudentWorld* Actor::getWorld() {
    return m_world;
}

//PEACH
Peach::Peach(StudentWorld* sw, int x, int y)
: Actor(IID_PEACH, 0, sw, x, y) {
    
}

Peach::~Peach() {
    cout << "deleted peach" << endl;
}

void Peach::doSomething() {
    if (!isAlive()) {
        return;
    }
    //check if invincible
    //check if recharging
    //check if overlapping with another game object
    int ch;
//    if (getWorld()->getKey(ch)) {
    // user hit a key during this tick!
//        switch (ch)
//        {
//            case KEY_PRESS_LEFT:
//                cout << "moves left" << endl;
//                break;
//            case KEY_PRESS_RIGHT:
//                cout << "moves right" << endl;
//                break;
//            case KEY_PRESS_SPACE:
//                cout << "fireball!" << endl;
//                break;
//            case KEY_PRESS_UP:
//                cout << "jump!" << endl;
//                break;
//            default:
//                break;
//        }
    return;
//    }
}

//BLOCK
Block::Block(StudentWorld* sw, int x, int y)
: Actor(IID_BLOCK, 2, sw, x, y) {
    
}
Block::~Block() {
    cout << "deleted block" << endl;
}

void Block::doSomething() {
    cout << "block does something" << endl;
}
