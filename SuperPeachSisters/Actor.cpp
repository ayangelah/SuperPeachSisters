#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

//ACTOR
Actor::Actor(int imageID, int dir, int graphicalDepth, StudentWorld* sw, int x, int y)
: GraphObject(imageID, x, y, dir, graphicalDepth, 1.0) {
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
: Actor(IID_PEACH, 0, 0, sw, x, y) {
    hitPoint = 1;
    isInvincible = false;
    hasJumpPower = false;
    hasStarPower = false;
    hasShootPower = false;
    isJumping = false;
}

Peach::~Peach() {
}

void Peach::doSomething() {
     if (!isAlive()) {
        return;
    }
    
    //check if invincible
    //check if recharging
    
    //checking overlap
    for (int i = 0; i < getWorld()->returnCast().size(); i++) {
        if (getWorld()->overlap(this, getWorld()->returnCast()[i])) {
            getWorld()->returnCast()[i]->bonk();
        }
    }
    if (isJumping) {
        if (remainingJumpDistance > 0) {
            int targetX = this->getX();
            int targetY = this->getY()+4;
            if (getWorld()->isBlockingObjectAt(targetX, targetY+4) != nullptr) {
                //bonk the object
                getWorld()->isBlockingObjectAt(targetX, targetY+4)->bonk();
                remainingJumpDistance = 0;
            }
            else if (getWorld()->isBlockingObjectAt(targetX+4, targetY+4) != nullptr) {
                //bonk the object
                getWorld()->isBlockingObjectAt(targetX+4, targetY+4)->bonk();
                remainingJumpDistance = 0;
            }
            else {
                moveTo(targetX, targetY);
                remainingJumpDistance--;
            }
        }
        else {
            isJumping = false;
        }
    }
    if (!isJumping) {
        if (getWorld()->isBlockingObjectAt(this->getX(), this->getY()-4) == nullptr && getWorld()->isBlockingObjectAt(this->getX()+4, this->getY()-4) == nullptr) {
            moveTo(this->getX(), this->getY()-4);
        }
    }
    
    
    int ch;
    if (getWorld()->getKey(ch)) {
    // user hit a key during this tick!
        switch (ch)
        {
            case KEY_PRESS_LEFT:
                setDirection(180);
                if (getWorld()->isBlockingObjectAt(getX()-4, getY()) != nullptr) {
                    break;
                }
                if (getWorld()->isBlockingObjectAt(getX(), getY()) == nullptr) {
                    moveTo(getX()-SPRITE_WIDTH/2, getY());
                }
                break;
            case KEY_PRESS_RIGHT: {
                setDirection(0);
                if (getWorld()->isBlockingObjectAt(getX()+8, getY()) != nullptr) {
                    break;
                }
                if (getWorld()->isBlockingObjectAt(getX(), getY()) == nullptr) {
                    moveTo(getX()+SPRITE_WIDTH/2, getY());
                }
                break;
            case KEY_PRESS_SPACE: {
                if (!hasShootPower) {
                    break;
                }
                if (rechargeTime > 0) {
                    break;
                }
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                rechargeTime = 8;
                int fireballX;
                if (getDirection() == 0)
                    fireballX = getX() + 4;
                else {
                    fireballX = getX() - 4;
                }
                
                Peach_Fireball* newPeachFireBall = new Peach_Fireball(getWorld(), fireballX, getY());
                break;
            }
            case KEY_PRESS_DOWN:
//                setDirection(180);
//                if (!(getWorld()->isBlockingObjectAt(getX(), getY()-SPRITE_HEIGHT/2 + 1))) {
//                    moveTo(this->getX(), this->getY()-SPRITE_HEIGHT/2);
//                }
                break;
            }
            case KEY_PRESS_UP: {
                if (getWorld()->isBlockingObjectAt(getX(), getY()-4)) {
                    isJumping = true;
                    if (hasJumpPower)
                        remainingJumpDistance = 12;
                    else
                        remainingJumpDistance = 8;
                    getWorld()->playSound(SOUND_PLAYER_JUMP);
                }
                break;
            }
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
: Actor(imageID, 0, 2, sw, x, y) {
    bool hasGoodie = true;
}
Block::~Block() {
}

void Block::doSomething() { }

int Block::actorType() {
    return IS_BLOCK_OR_PIPE;
}

void Block::bonk() {
    getWorld()->playSound(SOUND_PLAYER_BONK);
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
Enemy::Enemy(int imageID, StudentWorld* sw, int x, int y) : Actor(imageID, 0, 1, sw, x, y) {
    
}

Enemy::~Enemy() {
    
}

void Enemy::doSomething() {
    if (getDirection() == 0) {
        if (getWorld()->isBlockingObjectAt(getX()+4, getY()) != nullptr || getWorld()->isBlockingObjectAt(getX()+4, getY()-4) == nullptr) {
            setDirection(180);
            return;
        }
        else {
            moveTo(getX()+4, getY());
            return;
        }
        
    }
    if (getDirection() == 180) {
        if (getWorld()->isBlockingObjectAt(getX()-4, getY()) != nullptr || getWorld()->isBlockingObjectAt(getX()-4, getY()-4) == nullptr) {
            setDirection(0);
            return;
        }
        else {
            moveTo(getX()-4, getY());
            return;
        }
        
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

//void Goomba::doSomething() {
//    if (getDirection() == 0) {
//        if (getWorld()->isBlockingObjectAt(getX()+4, getY()) != nullptr || getWorld()->isBlockingObjectAt(getX()+4, getY()-4) == nullptr) {
//            setDirection(180);
//            return;
//        }
//        else {
//            moveTo(getX()+4, getY());
//            return;
//        }
//
//    }
//    if (getDirection() == 180) {
//        if (getWorld()->isBlockingObjectAt(getX()-4, getY()) != nullptr || getWorld()->isBlockingObjectAt(getX()-4, getY()-4) == nullptr) {
//            setDirection(0);
//            return;
//        }
//        else {
//            moveTo(getX()-4, getY());
//            return;
//        }
//
//    }
//}

void Goomba::bonk() {
}

//PIRANHA
Piranha::Piranha(StudentWorld* sw, int x, int y) : Enemy(IID_PIRANHA, sw, x, y){
    
}
Piranha::~Piranha() {
    
}
//void Piranha::doSomething() {
//    
//}

void Piranha::bonk() {
}

//KOOPA
Koopa::Koopa(StudentWorld* sw, int x, int y) : Enemy(IID_KOOPA, sw, x, y){
    
}
Koopa::~Koopa() {
    
}
//void Koopa::doSomething() {
//    
//}
void Koopa::bonk() {
}

//PEACH FIREBALL
Peach_Fireball::Peach_Fireball(StudentWorld* sw, int x, int y) : Actor(IID_PEACH_FIRE, 0, 1, sw, x, y) {
    
}
int Peach_Fireball::actorType() {
    return -1;
}
Peach_Fireball::~Peach_Fireball() {
    
}
void Peach_Fireball::doSomething() {
    
}
void Peach_Fireball::bonk() {
    
}

//FLAG
Flag::Flag(StudentWorld* sw, int x, int y) : Actor(IID_FLAG, 0, 1, sw, x, y) {
    
}
int Flag::actorType() {
    return IS_MARIO_OR_FLAG;
}
Flag::~Flag() {
    
}
void Flag::doSomething() {
//    if (!isAlive()) {
//        return;
//    }
//    getWorld()->changeScore(1000);
//    changeAliveStatus(false);
//    return;
}
void Flag::bonk() {
    getWorld()->playSound(SOUND_FINISHED_LEVEL);
    getWorld()->levelCompletedSet();
}

//MARIO
Mario::Mario(StudentWorld* sw, int x, int y) : Actor(IID_MARIO, 0, 1, sw, x, y) {
    
}
int Mario::actorType() {
    return IS_MARIO_OR_FLAG;
}
Mario::~Mario() {
    
}
void Mario::doSomething() {
    
}
void Mario::bonk() {
    getWorld()->playSound(SOUND_FINISHED_LEVEL);
    getWorld()->playerWonSet();
}
