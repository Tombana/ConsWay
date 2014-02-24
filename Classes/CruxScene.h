#ifndef __CRUXSCENE_H__
#define __CRUXSCENE_H__

#include "cocos2d.h"
#include "CruxGame.h"
#include <vector>

using namespace Crux;
using namespace cocos2d;

class CruxScene : public Layer, public GameDelegate
{
public:
    CruxScene();
    virtual ~CruxScene();

    //Called by AppDelegate
    //Creates a new Scene, and a new CruxScene layer
    //and adds the layer to the scene
    static Scene* createScene();
    Layer* getInterfaceLayer() const { return interfaceLayer; }

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

    void initializeGame();

private:
    Game* game;
    Sprite* player;

    Layer* interfaceLayer;
    LabelTTF* actionPointsLabel;
    LabelTTF* gameStateLabel;

    TMXTiledMap* tileMap;
    TMXLayer* background;

	vector<Sprite*> npcSprites;

    int tileX;
    int tileY;
    vector< vector<Sprite*> > tileSprites;

    Rect getRect(char type);
};

#endif // __CRUXSCENE_H__
