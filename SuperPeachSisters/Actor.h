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
    Actor(int imageID, int graphicalDepth, StudentWorld* sw, int x, int y);
    virtual ~Actor() = 0;
    virtual void doSomething() = 0;
    virtual void bonk() = 0;
    void changeAliveStatus(bool isAlive) {
        notDead = isAlive;
    }
    StudentWorld* getWorld();
    bool isAlive() {
        return notDead;
    }
    virtual int actorType() = 0;
private:
    StudentWorld* m_world;
    bool notDead;
};

class Peach: public Actor {
public:
    Peach(StudentWorld* sw, int x, int y);
    virtual ~Peach();
    virtual void doSomething();
    Actor* touching();
    virtual int actorType();
    virtual void bonk() { }
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
private:
    int hitPoint;
    bool hasStarPower;
    bool hasJumpPower;
    bool hasShootPower;
    bool isInvincible;
};

class Block: public Actor {
public:
    Block(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Block();
    virtual void doSomething();
    virtual int actorType();
    bool hasGoodie;
    int goodieType;
    void bonk();
private:
};

class Pipe: public Block {
public:
    Pipe(StudentWorld* sw, int x, int y);
    virtual ~Pipe();
    virtual int actorType();
    void bonk();
};

class Flag: public Actor {
public:
    Flag(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Flag();
    virtual void doSomething();
    int actorType();
    void bonk();
};

class Mario: public Actor {
public:
    Mario(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Mario();
    virtual void doSomething();
    int actorType();
    void bonk();
};

class Flower: public Actor {
public:
    Flower(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Flower();
    virtual void doSomething();
    int actorType();
    void bonk();
};

class Star: public Actor {
public:
    Star(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Star();
    virtual void doSomething();
    int actorType();
    void bonk();
};

class Piranha_Fireball: public Actor {
public:
    Piranha_Fireball(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Piranha_Fireball();
    virtual void doSomething();
    int actorType();
    void bonk();
};

class Peach_Fireball: public Actor {
public:
    Peach_Fireball(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Peach_Fireball();
    virtual void doSomething();
    int actorType();
    void bonk();
};

class Enemy: public Actor {
public:
    Enemy(int imageID, StudentWorld* sw, int x, int y);
    virtual ~Enemy();
    virtual void doSomething();
    int actorType();
    void bonk();
};

class Shell: public Enemy {
public:
    Shell(StudentWorld* sw, int x, int y);
    virtual ~Shell();
    virtual void doSomething();
    void bonk();
private:
};

class Goomba: public Enemy {
public:
    Goomba(StudentWorld* sw, int x, int y);
    virtual ~Goomba();
    virtual void doSomething();
    void bonk();
private:
};

class Piranha: public Enemy {
public:
    Piranha(StudentWorld* sw, int x, int y);
    virtual ~Piranha();
    virtual void doSomething();
    void bonk();
private:
};

class Koopa: public Enemy {
public:
    Koopa(StudentWorld* sw, int x, int y);
    virtual ~Koopa();
    virtual void doSomething();
    void bonk();
private:
};

#endif // ACTOR_H_
