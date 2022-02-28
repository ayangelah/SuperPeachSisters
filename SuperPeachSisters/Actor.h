#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

//identifying returns
const int IS_PEACH = 0;
const int IS_BLOCK_OR_PIPE = 1;
const int IS_SPECIAL_BLOCK = 2;
const int IS_ENEMY = 3;
const int IS_MARIO_OR_FLAG = 4;

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor: public GraphObject {
public:
    Actor(int imageID, int dir, int graphicalDepth, StudentWorld* sw, int x, int y);
    virtual ~Actor() = 0;
    virtual void doSomething() = 0;
    virtual void bonk() = 0;
    void changeAliveStatus(bool isAlive) {
        notDead = isAlive;
    }
    StudentWorld* getWorld();
    bool isAlive() {
        if (this != nullptr)
            return notDead;
        return false;
    }
    void projectileMotion();
    virtual bool damaged() {return false;}
    virtual bool hitPeachAction() {return false;}
    virtual void hitAction() {}
private:
    StudentWorld* m_world;
    bool notDead;
};

class Peach: public Actor {
public:
    Peach(StudentWorld* sw, int x, int y);
    virtual ~Peach();
    virtual void doSomething();
    virtual
    void bonk();
    void changeHitPoints(int newHitPoints) {
        hitPoint = newHitPoints;
    }
    bool starPower() {
        return hasStarPower;
    }
    bool jumpPower() {
        return hasJumpPower;
    }
    bool shootPower() {
        return hasShootPower;
    }
    bool invincible() {
        return isInvincible;
    }
    void changeStarPower(bool status) {
        hasStarPower = status;
    }
    void changeJumpPower(bool status) {
        hasJumpPower = status;
    }
    void changeShootPower(bool status) {
        hasShootPower = status;
    }
    void changeInvincible(bool status) {
        isInvincible = status;
    }
private:
    bool isJumping;
    int remainingJumpDistance;
    int hitPoint;
    bool hasStarPower;
    bool hasJumpPower;
    bool hasShootPower;
    bool isInvincible;
    int rechargeTime;
    int invincibleTime;
    int tempInvincibleTime;
};

class Obstacle: public Actor {
public:
    Obstacle(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Obstacle();
    virtual void doSomething() {}
    virtual bool returnHasGoodie() = 0;
    virtual void releaseGoodie(int x, int y) = 0;
    virtual void bonk();
private:
};

class NormalBlock: public Obstacle {
public:
    NormalBlock(StudentWorld* sw, int x, int y);
    virtual ~NormalBlock();
    virtual void doSomething();
    bool returnHasGoodie() {
        return hasGoodie;
    }
    void releaseGoodie(int x, int y);
private:
    bool hasGoodie;
};

class FlowerBlock: public Obstacle {
public:
    FlowerBlock(StudentWorld* sw, int x, int y);
    virtual ~FlowerBlock();
    virtual void doSomething();
    bool returnHasGoodie() {
        return hasGoodie;
    }
    void releaseGoodie(int x, int y);
private:
    bool hasGoodie;
};

class StarBlock: public Obstacle {
public:
    StarBlock(StudentWorld* sw, int x, int y);
    virtual ~StarBlock();
    virtual void doSomething();
    bool returnHasGoodie() {
        return hasGoodie;
    }
    void releaseGoodie(int x, int y);
private:
    bool hasGoodie;
};

class MushroomBlock: public Obstacle {
public:
    MushroomBlock(StudentWorld* sw, int x, int y);
    virtual ~MushroomBlock();
    virtual void doSomething();
    bool returnHasGoodie() {
        return hasGoodie;
    }
    void releaseGoodie(int x, int y);
private:
    bool hasGoodie;
};

class Pipe: public Obstacle {
public:
    Pipe(StudentWorld* sw, int x, int y);
    virtual ~Pipe();
    virtual
    void bonk();
    bool returnHasGoodie() { return false; }
    virtual void releaseGoodie(int x, int y) {}
};

class Goodie: public Actor {
public:
    Goodie(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Goodie();
    void doSomething();
    virtual void givePower() = 0;
    void hitAction();
    bool hitPeachAction();
    void bonk();
};

class Flower: public Goodie {
public:
    Flower(StudentWorld* sw, int x, int y);
    virtual ~Flower();
    void givePower();
    void bonk();
private:
    int m_points = 50;
};

class Star: public Goodie {
public:
    Star(StudentWorld* sw, int x, int y);
    virtual ~Star();
    void givePower();
    void bonk();
private:
    int m_points = 100;
};

class Mushroom: public Goodie {
public:
    Mushroom(StudentWorld* sw, int x, int y);
    virtual ~Mushroom();
    void givePower();
    void bonk();
private:
    int m_points = 75;
};

class Flag: public Actor {
public:
    Flag(StudentWorld* sw, int x, int y);
    virtual ~Flag();
    void doSomething();
    void bonk();
    
};

class Mario: public Actor {
public:
    Mario(StudentWorld* sw, int x, int y);
    virtual ~Mario();
    virtual void doSomething();
    void bonk();
    
};

class Projectile: public Actor {
public:
    Projectile(int imageID, StudentWorld* sw, int x, int y, int dir);
    virtual ~Projectile();
    virtual void doSomething();
    virtual void bonk() {}
    void hitAction();
    virtual bool hitPeachAction();
};

class Piranha_Fireball: public Projectile {
public:
    Piranha_Fireball(StudentWorld* sw, int x, int y, int dir);
    virtual ~Piranha_Fireball();
    virtual void doSomething();
    void bonk();
    void hitAction();
    bool hitPeachAction();
};

class Peach_Fireball: public Projectile {
public:
    Peach_Fireball(StudentWorld* sw, int x, int y, int dir);
    virtual ~Peach_Fireball();
    virtual void doSomething();
    void hitAction();
    void bonk();
};

class Shell: public Projectile {
public:
    Shell(StudentWorld* sw, int x, int y, int dir);
    virtual ~Shell();
    virtual void doSomething();
    bool damaged();
    void bonk();
    
};

class Enemy: public Actor {
public:
    Enemy(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Enemy();
    void doSomething();
    void enemyMovement();
    bool projectileMovement();
    virtual bool damaged();
    virtual void bonk();
};

class Goomba: public Enemy {
public:
    Goomba(StudentWorld* sw, int x, int y);
    virtual ~Goomba();
//    void doSomething();
    
private:
};

class Piranha: public Enemy {
public:
    Piranha(StudentWorld* sw, int x, int y);
    virtual ~Piranha();
    void doSomething();
    
private:
    int firingDelay;
};

class Koopa: public Enemy {
public:
    Koopa(StudentWorld* sw, int x, int y);
    virtual ~Koopa();
    bool damaged();
    
private:
};

#endif // ACTOR_H_
