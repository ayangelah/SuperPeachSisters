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
    hitPoint = 1;
    isInvincible = false;
    hasJumpPower = false;
    hasStarPower = false;
    hasShootPower = false;
}

Peach::~Peach() {
}

void Peach::doSomething() {
     if (!isAlive()) {
        return;
    }
    //check if invincible
    //check if recharging
    //check if overlapping with another game object
    Actor* a = touching();
    if (a != nullptr) {
        a->bonk();
//        int identifier = a->actorType();
//        switch (identifier) {
//            case IS_PEACH: {
//
//            }
//            case IS_ENEMY: {
//
//            }
//            case IS_BLOCK_OR_PIPE: {
//
//            }
//            case IS_SPECIAL_BLOCK: {
//
//            }
//            case IS_MARIO_OR_FLAG: {
//
//            }
//
//        }
    }
    
    int ch;
    if (getWorld()->getKey(ch)) {
    // user hit a key during this tick!
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                setDirection(180);
                if (getWorld()->isBlockingObjectAt(this->getX()/4-1, this->getY()/4)) {
                    break;
                }
                if (!(getWorld()->isBlockingObjectAt(this->getX()/4, this->getY()/4))) {
                    moveTo(this->getX()-SPRITE_WIDTH/2, this->getY());
                }
                break;
            case KEY_PRESS_RIGHT:
                setDirection(0);
                if (getWorld()->isBlockingObjectAt(this->getX()/4+2, this->getY()/4)) {
                    break;
                }
                if (!(getWorld()->isBlockingObjectAt(this->getX()/4, this->getY()/4))) {
                    moveTo(this->getX()+SPRITE_WIDTH/2, this->getY());
                }
                break;
            case KEY_PRESS_SPACE:
                if (hasShootPower) {
                    //fireball
                }
                break;
            case KEY_PRESS_DOWN:
                setDirection(180);
                if (!(getWorld()->isBlockingObjectAt(getX(), getY()-SPRITE_HEIGHT/2 + 1))) {
                    moveTo(this->getX(), this->getY()-SPRITE_HEIGHT/2);
                }
                break;
            case KEY_PRESS_UP:
                if (getWorld()->isBlockingObjectAt(this->getX()/SPRITE_WIDTH, this->getY()/SPRITE_HEIGHT-1)) {
                    moveTo(this->getX(), this->getY()+SPRITE_HEIGHT/2);
                }
                break;
            default:
                break;
        }
    return;
    }
}

int Peach::actorType() {
    return IS_PEACH;
}

Actor* Peach::touching() {
    for (int i = 0; i < getWorld()->returnCast().size(); i++) {
        if (getWorld()->overlap(this, getWorld()->returnCast()[i])) {
            return getWorld()->returnCast()[i];
        }
    }
    return nullptr;
}

//BLOCK
Block::Block(int imageID, StudentWorld* sw, int x, int y)
: Actor(imageID, 2, sw, x, y) {
    bool hasGoodie = true;
}
Block::~Block() {
}

void Block::doSomething() { }

int Block::actorType() {
    return IS_BLOCK_OR_PIPE;
}

void Block::bonk() {
}

//PIPE
Pipe::Pipe(StudentWorld* sw, int x, int y): Block(IID_PIPE, sw, x, y) {
    
}

Pipe::~Pipe() {
    
}

void Pipe::bonk() {
}

int Pipe::actorType() {
    return IS_BLOCK_OR_PIPE;
}

//ENEMY
Enemy::Enemy(int imageID, StudentWorld* sw, int x, int y) : Actor(imageID, 1, sw, x, y) {
    
}

Enemy::~Enemy() {
    
}

void Enemy::doSomething() {
    if (getWorld()->overlap(this, getWorld()->returnPeach())) {
        //attempt to attack
    }
}

int Enemy::actorType() {
    return IS_ENEMY;
}

void Enemy::bonk() {
}

//GOOMBA
Goomba::Goomba(StudentWorld* sw, int x, int y)
: Enemy(IID_GOOMBA, sw, x, y) {
    
}
Goomba::~Goomba() {
}

void Goomba::doSomething() {
    if (getWorld()->overlap(this, getWorld()->returnPeach())) {
        //attempt to attack
    }
}

void Goomba::bonk() {
}

//PIRANHA
Piranha::Piranha(StudentWorld* sw, int x, int y) : Enemy(IID_PIRANHA, sw, x, y){
    
}
Piranha::~Piranha() {
    
}
void Piranha::doSomething() {
    
}

void Piranha::bonk() {
}

//KOOPA
Koopa::Koopa(StudentWorld* sw, int x, int y) : Enemy(IID_KOOPA, sw, x, y){
    
}
Koopa::~Koopa() {
    
}
void Koopa::doSomething() {
    
}
void Koopa::bonk() {
}
