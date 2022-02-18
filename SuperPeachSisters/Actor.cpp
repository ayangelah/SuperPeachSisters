#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

//ACTOR
Actor::Actor(int imageID, int graphicalDepth, StudentWorld* sw, int x, int y)
: GraphObject(imageID, x, y, graphicalDepth, 0, 1.0) {
    notDead = true;
    m_world = sw;
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
    if (getWorld()->getKey(ch)) {
    // user hit a key during this tick!
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                cout << "moves left" << endl;
                setDirection(180);
                moveTo(this->getX()-SPRITE_WIDTH/2, this->getY());
                break;
            case KEY_PRESS_RIGHT:
                setDirection(0);
                cout << "moves right" << endl;
                moveTo(getX()+SPRITE_WIDTH/2, getY());
                break;
            case KEY_PRESS_SPACE:
                cout << "fireball!" << endl;
                
                break;
            case KEY_PRESS_UP:
                cout << "jump!" << endl;
                break;
            default:
                cout << "char not recognized" << endl;
                break;
        }
    return;
    }
}

//BLOCK
Block::Block(StudentWorld* sw, int x, int y)
: Actor(IID_BLOCK, 2, sw, x, y) {
}
Block::~Block() {
    cout << "deleted block" << endl;
}

void Block::doSomething() {
    //cout << "block does something" << endl;
}

//GOOMBA
Goomba::Goomba(StudentWorld* sw, int x, int y)
: Actor(IID_GOOMBA, 1, sw, x, y) {
    
}
Goomba::~Goomba() {
    cout << "deleted goomba" << endl;
}

void Goomba::doSomething() {
    if (getWorld()->overlap(this, getWorld()->returnPeach())) {
        //attempt to attack
        cout << "attack peach" << endl;
    }
    //cout << "goomba does something" << endl;
}
