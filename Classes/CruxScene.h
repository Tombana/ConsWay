#ifndef __CRUXSCENE_H__
#define __CRUXSCENE_H__

#include "cocos2d.h"
#include "CruxGame.h"

using namespace Crux;
using namespace cocos2d;

class CruxScene : public Layer, public GameDelegate
{
public:
    CruxScene();
    virtual ~CruxScene();

    static cocos2d::Scene* createScene();
    virtual bool init();  
    // implement the "static create()" method manually
    CREATE_FUNC(CruxScene);

    void menuCloseCallback(Object* pSender);

    //
    //---------------------------------------------
    //

    //Called every second
    void gameLoop(float dt);

    //Called by Game when something changes
    void gameUpdated();

    //Key press handler
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    //Not used
    void addEnemy();
    void spriteMoveFinished(Node* sender);
private:
    Game* game;
    Sprite* player;

    int tileX;
    int tileY;
    vector< vector<Sprite*> > tileSprites;

    Rect getRect(char type);
};

#endif // __CRUXSCENE_H__
