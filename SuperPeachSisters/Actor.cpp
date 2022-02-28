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

void Actor::projectileMotion() {
    if (!isAlive())
        return;
    if (getWorld()->overlap(this, getWorld()->returnPeach())) {
        if (hitPeachAction())
            return;
    }
    if (!(getWorld()->isBlockingObjectAt(getX(), getY()-2)) && !(getWorld()->isBlockingObjectAt(getX()+4, getY()-2))) {
        moveTo(getX(), getY()-2);
    }
    int targetX;
    if (getDirection() == 0) {
        targetX = getX()+2;
        if (getWorld()->isBlockingObjectAt(targetX+6, getY()) || getWorld()->isBlockingObjectAt(targetX+6, getY() + 6)) {
            hitAction();
            return;
        }
    }
    if (getDirection() == 180) {
        targetX = getX()-2;
        if (getWorld()->isBlockingObjectAt(targetX, getY()) || getWorld()->isBlockingObjectAt(targetX, getY() + 6)) {
            hitAction();
            return;
        }
    }
    moveTo(targetX, getY());
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
    rechargeTime = 0;
}

Peach::~Peach() {
}

void Peach::bonk() {
    if (hasStarPower || isInvincible)
        return;
    else {
        hitPoint--;
        //set temporary invincibility to 10 ticks
        tempInvincibleTime = 10;
        hasShootPower = false;
        hasJumpPower = false;
        if (hitPoint >= 1)
            getWorld()->playSound(SOUND_PLAYER_HURT);
        if (hitPoint < 1) {
            changeAliveStatus(false);
            //tell sw peach is dead.
        }
    }
}

void Peach::doSomething() {
     if (!isAlive()) {
        return;
    }
    
    //check if hasStarPower
    if (hasStarPower) {
        invincibleTime--;
    }
    if (invincibleTime == 0)
        hasStarPower = false;
    
    //check if invincible
    if (tempInvincibleTime > 0)
        tempInvincibleTime--;
    
    //check if recharging
    if (rechargeTime > 0) {
        rechargeTime--;
    }
    
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
                
                Peach_Fireball* newPeachFireBall = new Peach_Fireball(getWorld(), fireballX, getY(), getDirection());
                getWorld()->addToCast(newPeachFireBall);
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
}

//OBSTACLE
Obstacle::Obstacle(int imageID, StudentWorld* sw, int x, int y)
: Actor(imageID, 0, 2, sw, x, y) {
}

Obstacle::~Obstacle() {
}

void Obstacle::bonk() {
    if (!returnHasGoodie())
        getWorld()->playSound(SOUND_PLAYER_BONK);
    else {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        releaseGoodie(getX(), getY()+8);
    }
}

//NORMAL BLOCK
NormalBlock::NormalBlock(StudentWorld* sw, int x, int y)
: Obstacle(IID_BLOCK, sw, x, y) {
    hasGoodie = false;
}

NormalBlock::~NormalBlock() {
    
}

void NormalBlock::doSomething() {
    
}

void NormalBlock::releaseGoodie(int x, int y) { }


//FLOWER BLOCK
FlowerBlock::FlowerBlock(StudentWorld* sw, int x, int y)
: Obstacle(IID_BLOCK, sw, x, y) {
    hasGoodie = true;
}

FlowerBlock::~FlowerBlock() {
    
}

void FlowerBlock::doSomething() {
    
}


void FlowerBlock::releaseGoodie(int x, int y) {
    Flower* newFlower = new Flower(getWorld(), x, y);
    getWorld()->addToCast(newFlower);
    hasGoodie = false;
}

//STAR BLOCK
StarBlock::StarBlock(StudentWorld* sw, int x, int y)
: Obstacle(IID_BLOCK, sw, x, y) {
    hasGoodie = true;
}

StarBlock::~StarBlock() {
    
}

void StarBlock::doSomething() {
    
}

void StarBlock::releaseGoodie(int x, int y) {
    Star* newStar = new Star(getWorld(), x, y);
    getWorld()->addToCast(newStar);
    hasGoodie = false;
}

//MUSHROOM BLOCK
MushroomBlock::MushroomBlock(StudentWorld* sw, int x, int y)
: Obstacle(IID_BLOCK, sw, x, y) {
    hasGoodie = true;
}

MushroomBlock::~MushroomBlock() {
    
}

void MushroomBlock::doSomething() {
    
}

void MushroomBlock::releaseGoodie(int x, int y) {
    Mushroom* newMushroom = new Mushroom(getWorld(), x, y);
    getWorld()->addToCast(newMushroom);
    hasGoodie = false;
}

//GOODIE
Goodie::Goodie(int imageID, StudentWorld* sw, int x, int y) : Actor(imageID, 0, 1, sw, x, y) {
    
}

Goodie::~Goodie() {
    
}

void Goodie::bonk() {
    
}

void Goodie::hitAction() {
    if (getDirection() == 0)
        setDirection(180);
    else
        setDirection(0);
}

bool Goodie::hitPeachAction() {
    givePower();
    getWorld()->playSound(SOUND_PLAYER_POWERUP);
    changeAliveStatus(false);
    return true;
}

void Goodie::doSomething() {
    projectileMotion();
}

//FLOWER
Flower::Flower(StudentWorld* sw, int x, int y) : Goodie(IID_FLOWER, sw, x, y) {
}

Flower::~Flower() {
}

void Flower::givePower() {
    getWorld()->increaseScore(m_points);
    getWorld()->returnPeach()->changeShootPower(true);
    getWorld()->returnPeach()->changeHitPoints(2);
}

void Flower::bonk() {
    
}

//STAR
Star::Star(StudentWorld* sw, int x, int y) : Goodie(IID_STAR, sw, x, y) {
    
}

Star::~Star() {
    
}

void Star::givePower() {
    getWorld()->increaseScore(m_points);
    getWorld()->returnPeach()->changeStarPower(true);
}

void Star::bonk() {
    
}


//MUSHROOM
Mushroom::Mushroom(StudentWorld* sw, int x, int y) : Goodie(IID_MUSHROOM, sw, x, y) {
    
}

Mushroom::~Mushroom() {
    
}

void Mushroom::givePower() {
    getWorld()->increaseScore(m_points);
    getWorld()->returnPeach()->changeJumpPower(true);
    getWorld()->returnPeach()->changeHitPoints(2);
}

void Mushroom::bonk() {
    
}


//PIPE
Pipe::Pipe(StudentWorld* sw, int x, int y): Obstacle(IID_PIPE, sw, x, y) {
    
}

Pipe::~Pipe() {
    
}

void Pipe::bonk() {
}

//ENEMY
Enemy::Enemy(int imageID, StudentWorld* sw, int x, int y) : Actor(imageID, 0, 1, sw, x, y) {
    int dir = randInt(0, 1);
    if (dir == 0) {
        setDirection(0);
    }
    if (dir == 1) {
        setDirection(180);
    }
}

Enemy::~Enemy() {
    
}

void Enemy::doSomething() {
    if (!isAlive()) {
        return;
    }
    if (getWorld()->overlap(this, getWorld()->returnPeach())) {
        getWorld()->returnPeach()->bonk();
    }
    enemyMovement();
}

bool Enemy::projectileMovement() {
    if (getDirection() == 0) {
        if (getWorld()->isBlockingObjectAt(getX()+4, getY()) != nullptr || getWorld()->isBlockingObjectAt(getX()+4, getY()-4) == nullptr) {
            setDirection(180);
            return true;
        }
    }
    if (getDirection() == 180) {
        if (getWorld()->isBlockingObjectAt(getX()-4, getY()) != nullptr || getWorld()->isBlockingObjectAt(getX()-4, getY()-4) == nullptr) {
            setDirection(0);
            return true;
        }
    }
    return false;
}

void Enemy::enemyMovement() {
    if (getDirection() == 0) {
        if (getWorld()->isBlockingObjectAt(getX()+8, getY()) != nullptr || getWorld()->isBlockingObjectAt(getX()+8, getY()-4) == nullptr) {
            setDirection(180);
            return;
        }
        else {
            moveTo(getX()+1, getY());
            return;
        }
        
    }
    if (getDirection() == 180) {
        if (getWorld()->isBlockingObjectAt(getX()-2, getY()) != nullptr || getWorld()->isBlockingObjectAt(getX()-2, getY()-4) == nullptr) {
            setDirection(0);
            return;
        }
        else {
            moveTo(getX()-1, getY());
            return;
        }
        
    }
}

void Enemy::bonk() {
    if (getWorld()->returnPeach()->starPower() || getWorld()->returnPeach()->invincible()) {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        getWorld()->changeScore(100);
        changeAliveStatus(false);
    }
    else {
        getWorld()->returnPeach()->bonk();
    }
}

bool Enemy::damaged() {
    //bonked by fireball
    getWorld()->changeScore(100);
    changeAliveStatus(false);
    return true;
}

//GOOMBA
Goomba::Goomba(StudentWorld* sw, int x, int y)
: Enemy(IID_GOOMBA, sw, x, y) {
    
}
Goomba::~Goomba() {
}

//PIRANHA
Piranha::Piranha(StudentWorld* sw, int x, int y) : Enemy(IID_PIRANHA, sw, x, y){
    firingDelay = 0;
}
Piranha::~Piranha() {
    
}
void Piranha::doSomething() {
    if (!isAlive()) {
        return;
    }
    increaseAnimationNumber();
    if (getWorld()->overlap(this, getWorld()->returnPeach())) {
        getWorld()->returnPeach()->bonk();
        return;
    }
    if (!(abs(getY()-getWorld()->returnPeach()->getY()) <= 1.5*SPRITE_HEIGHT))
        return;
    if (getWorld()->returnPeach()->getX() < getX()) //left
        setDirection(180);
    if (getWorld()->returnPeach()->getX() > getX()) //right
        setDirection(0);
    if (firingDelay > 0) {
        firingDelay--;
        return;
    }
    else {
        Piranha_Fireball* newPiranhaFireball;
        if (abs(getX() - getWorld()->returnPeach()->getX()) < 8 * SPRITE_WIDTH) {
            if (getDirection() == 0) {
                newPiranhaFireball = new Piranha_Fireball(getWorld(), getX(), getY(), 0);
            }
            if (getDirection() == 180) {
                newPiranhaFireball = new Piranha_Fireball(getWorld(), getX(), getY(), 180);
            }
            getWorld()->addToCast(newPiranhaFireball);
            getWorld()->playSound(SOUND_PIRANHA_FIRE);
            firingDelay = 40;
        }
    }
}

//KOOPA
Koopa::Koopa(StudentWorld* sw, int x, int y) : Enemy(IID_KOOPA, sw, x, y){
    
}
Koopa::~Koopa() {
    
}
bool Koopa::damaged() {
    //bonked by fireball
    getWorld()->changeScore(100);
    changeAliveStatus(false);
    Shell* newShell = new Shell(getWorld(), getX(), getY(), getDirection());
    getWorld()->addToCast(newShell);
    return true;
}

//PROJECTILE
Projectile::Projectile(int imageID, StudentWorld* sw, int x, int y, int dir) : Actor(imageID, dir, 1, sw, x, y) {

}
Projectile::~Projectile() {
    
}
void Projectile::doSomething() {
    
}
void Projectile::hitAction() {
    changeAliveStatus(false);
}
bool Projectile::hitPeachAction() {
    return false;
}

//PEACH FIREBALL
Peach_Fireball::Peach_Fireball(StudentWorld* sw, int x, int y, int dir) : Projectile(IID_PEACH_FIRE, sw, x, y, dir) {
    changeAliveStatus(true);
}
Peach_Fireball::~Peach_Fireball() {
    
}
void Peach_Fireball::doSomething() {
    projectileMotion();
    for (int i = 0; i < getWorld()->returnCast().size(); i++) {
        if (getWorld()->overlap(this, getWorld()->returnCast()[i]) && getWorld()->returnCast()[i]->isAlive()) {
            getWorld()->returnCast()[i]->damaged();
            if (getWorld()->returnCast()[i]->damaged()) {
                changeAliveStatus(false);
            }
            return;
        }
    }
}
void Peach_Fireball::bonk() {
    
}
void Peach_Fireball::hitAction() {
    changeAliveStatus(false);
}

//PIRANHA FIREBALL
Piranha_Fireball::Piranha_Fireball(StudentWorld* sw, int x, int y, int dir) : Projectile(IID_PIRANHA_FIRE, sw, x, y, dir) {
    
}
Piranha_Fireball::~Piranha_Fireball() {
    
}
void Piranha_Fireball::doSomething() {
    projectileMotion();
}
void Piranha_Fireball::bonk() {
    getWorld()->returnPeach()->bonk();
}

void Piranha_Fireball::hitAction() {
    changeAliveStatus(false);
}

bool Piranha_Fireball::hitPeachAction() {
    getWorld()->returnPeach()->bonk();
    changeAliveStatus(false);
    return true;
}

//SHELL
Shell::Shell(StudentWorld* sw, int x, int y, int dir) : Projectile(IID_SHELL, sw, x, y, dir) {
    
}
Shell::~Shell() {
    
}
void Shell::doSomething() {
    projectileMotion();
    for (int i = 0; i < getWorld()->returnCast().size(); i++) {
        if (getWorld()->overlap(this, getWorld()->returnCast()[i]) && getWorld()->returnCast()[i]->isAlive()) {
            if (getWorld()->returnCast()[i]->damaged()) {
                changeAliveStatus(false);
            }
            return;
        }
    }
}

bool Shell::damaged() {
    return false;
}
void Shell::bonk() {
    
}

//FLAG
Flag::Flag(StudentWorld* sw, int x, int y) : Actor(IID_FLAG, 0, 1, sw, x, y) {
    
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
Mario::~Mario() {
    
}
void Mario::doSomething() {
    
}
void Mario::bonk() {
    getWorld()->playSound(SOUND_FINISHED_LEVEL);
    getWorld()->playerWonSet();
}
