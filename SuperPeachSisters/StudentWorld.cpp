#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //--------------------------------------------------
    // The term "actors" refers to all actors, e.g., Peach, goodies,
    // enemies, flags, blocks, pipes, fireballs, etc.
    // Give each actor a chance to do something, incl. Peach
//    for each of the actors in the game world
//    {
//     if (that actor is still active/alive)
//     {
//     // tell that actor to do something (e.g. move)
//     that actor -> doSomething();
//    if (Peach died during this tick) {
//     play dying sound
//    return GWSTATUS_PLAYER_DIED;
//    }
//    if (Peach reached Mario) {
//     play game over sound
//    return GWSTATUS_WON_GAME;
//    }
//    if (Peach competed the current level) {
//    play completed level sound
//    return GWSTATUS_FINISHED_LEVEL;
//    }
//     }
//    }
//    // Remove newly-dead actors after each tick
//    remove dead game objects
//    // Update the game status line
//    update display text // update the score/lives/level text at screen top
    // the player hasn’t completed the current level and hasn’t died, so
    // continue playing the current level
}

void StudentWorld::cleanUp()
{
}
