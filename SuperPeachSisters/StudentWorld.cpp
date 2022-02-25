#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include "Level.h"
#include "Actor.h"
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    for (int i = 0; i < GRID_WIDTH; i++) {
        for (int j = 0; j < GRID_HEIGHT; j++) {
            blockingObject[i][j] = nullptr;
        }
    }
    marioIndex = -1;
    flagIndex = -1;
    levelCompleted = false;
    playerWon = false;
}

int StudentWorld::init()
{
    levelBuild();
    //m_peach = new Peach(this, VIEW_WIDTH/2,  VIEW_HEIGHT/2);
    //initialize data structures in game
    //allocate and insert a peach object
    //allocate and insert all blocks, pipes, flags, enemies, and mario
    //load data from level data file

    for (int j=GRID_HEIGHT*2-1; j>=0; j--) {
        for (int i=0; i<GRID_WIDTH*2; i++) {
                cout << (this->blockingObject[i][j] != nullptr ? "#" : " ");
        }
        cout << endl;

    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //--------------------------------------------------
    //Gamestuff
    if (levelCompleted)
        return GWSTATUS_FINISHED_LEVEL;
    
    if (playerWon)
        return GWSTATUS_PLAYER_WON;
    //Peachstuff
    if (m_peach->isAlive()) {
        m_peach->doSomething();
    }
    
    //othercast stuff
    for (int i = 0; i < m_otherCast.size(); i++) {
        m_otherCast[i]->doSomething();
    }
    if (!m_peach->isAlive()) {
        playSound(SOUND_PLAYER_DIE);
        //destroy peach
        return GWSTATUS_PLAYER_DIED;
    }
    
    //if found mario
    if (marioIndex != -1 && overlap(m_peach, m_otherCast[marioIndex])) {
        playSound(SOUND_GAME_OVER);
        return GWSTATUS_PLAYER_WON;
    }
    //if completed level
    if (flagIndex != -1 && overlap(m_peach, m_otherCast[flagIndex])) {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }

//    // Remove newly-dead actors after each tick
    for (int i = 0; i < m_otherCast.size(); i++) {
        if (!m_otherCast[i]->isAlive()) {
            delete m_otherCast[i];
        }
    }
//    remove dead game objects
//    // Update the game status line
//    update display text // update the score/lives/level text at screen top
    // the player hasn’t completed the current level and hasn’t died, so
    // continue playing the current level
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    for (int i = 0; i < m_otherCast.size(); i++) {
        delete m_otherCast[i];
    }
}

bool StudentWorld::overlap(Actor* a, Actor* b) {
    if (abs(a->getX()-b->getX()) < SPRITE_WIDTH && abs(a->getY()-b->getY()) < SPRITE_HEIGHT)
        return true;
    return false;
}

Actor* StudentWorld::isBlockingObjectAt(int x, int y) {
    return (blockingObject[x/4][y/4]);
}

void StudentWorld::levelBuild() {
    Level lev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    
    if (result == Level::load_fail_file_not_found)
    cerr << "Could not find level01.txt data file" << endl;
    
    else if (result == Level::load_fail_bad_format)
    cerr << "level01.txt is improperly formatted" << endl;
    
    else if (result == Level::load_success)
    {
    cerr << "Successfully loaded level" << endl; Level::GridEntry ge;
        for (int i = 0; i < GRID_HEIGHT; i++) {
            for (int j = 0; j < GRID_WIDTH; j++) {
                ge = lev.getContentsOf(i, j);
                int x = SPRITE_HEIGHT*i;
                int y = SPRITE_WIDTH*j;
                switch (ge) {
                    case Level::empty:
                        break;
                    case Level::peach:
                        //construct peach w/ position
                        m_peach = new Peach(this, x, y);
                        assert(m_peach);
                        break;
                    case Level::koopa:{
                        Koopa* newKoopa = new Koopa(this, x, y);
                        m_otherCast.push_back(newKoopa);
                    }
                        break;
                    case Level::goomba: {
                        Goomba* newGoomba = new Goomba(this, x, y);
                        m_otherCast.push_back(newGoomba);
                        break;
                        }
                    case Level::piranha: {
                        Piranha* newPiranha = new Piranha(this, x, y);
                        m_otherCast.push_back(newPiranha);
                        }
                        break;
                    case Level::block: {
                        Block* newBlock = new Block(IID_BLOCK, this, x, y);
                        m_otherCast.push_back(newBlock);
                        for (int a = 0; a < 2; a++) {
                            for (int b = 0; b < 2; b++) {
                                blockingObject[2*i+a][2*j+b] = newBlock;
                            }
                        }
                        break;
                        }
                    case Level::star_goodie_block:
                        //construct star block
                        break;
                    case Level::mushroom_goodie_block:
                        //construct mushroom block
                        break;
                    case Level::flower_goodie_block:
                        //construct flower block
                        break;
                    case Level::pipe:{
                        Pipe* newPipe = new Pipe(this, x, y);
                        m_otherCast.push_back(newPipe);
                        for (int a = 0; a < 2; a++) {
                            for (int b = 0; b < 2; b++) {
                                blockingObject[2*i+a][2*j+b] = newPipe;
                            }
                        }
                        break;
                        }
                        break;
                    case Level::flag: {
                        Flag* newFlag = new Flag(this, x, y);
                        m_otherCast.push_back(newFlag);
                        flagIndex = m_otherCast.size()-1;
                         }
                        break;
                    case Level::mario: {
                        Mario* newMario = new Mario(this, x, y);
                        m_otherCast.push_back(newMario);
                        marioIndex = m_otherCast.size()-1;
                        }
                        break;
                }
            }
        }
    }
}
