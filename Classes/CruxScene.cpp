#include "CruxScene.h"
#include <string>
#include <iostream>
using namespace std;

USING_NS_CC;

Scene* CruxScene::createScene()
{
    // 'scene' is an autorelease object
    // 'layer' is an autorelease object
    auto scene = Scene::create();
    CruxScene* layer = CruxScene::create();
    scene->addChild(layer);
    scene->addChild(layer->getInterfaceLayer());
    return scene;
}

CruxScene::CruxScene()
{
    game = new Game();
    player = 0;
}

CruxScene::~CruxScene()
{
    delete game;
}

void CruxScene::initializeGame()
{
    if(game)
        delete game;

    game = new Game();

    tileMap = TMXTiledMap::create("test.tmx");
    background = tileMap->layerNamed("Background");
    this->addChild(tileMap);


    //Load game
    game->setMapProperties(tileMap->getMapSize().width, tileMap->getMapSize().height);
    game->initialize(this, "");
}

bool CruxScene::init()
{
    if ( !Layer::init() )
        return false;

    interfaceLayer = Layer::create();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //Title
    actionPointsLabel = LabelTTF::create("Action Points: ", "Arial", 13);
    actionPointsLabel->setPosition(Point(actionPointsLabel->getContentSize().width * 0.5 + 20, visibleSize.height - actionPointsLabel->getContentSize().height * 0.5 - 10));
    interfaceLayer->addChild(actionPointsLabel, 6);

    gameStateLabel = LabelTTF::create("Game State: ", "Arial", 13);
    gameStateLabel->enableStroke(Color3B::BLACK, 3.0f);
    gameStateLabel->setPosition(Point(gameStateLabel->getContentSize().width * 0.5 + 20, visibleSize.height - gameStateLabel->getContentSize().height - 20));
    interfaceLayer->addChild(gameStateLabel, 6);

    //Create player sprite
    player = Sprite::create("Player.png");
    player->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(player, 5);

    this->runAction(Follow::create(player));

    initializeGame();

    int w = game->getMap()->getWidth();
    int h = game->getMap()->getHeight();


    //Create NPC sprite
    for(int i=0; i<game->numNPCs(); i++) {
        string imgName="";
        switch(game->getNPC(i).getType()) {
            case HORSE:
                imgName="HORSE.png";
                break;
            case RANDOM:
                imgName="CREEP.png";
                break;
            default:
                imgName="RANDOM.png";
                break;
        }

        auto sprt = Sprite::create(imgName);
        sprt->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(sprt, 5);
        npcSprites.push_back(sprt);
    }

    /* auto batchNode = SpriteBatchNode::create("tiles.png", w*h);
       tileX = batchNode->getTexture()->getPixelsWide() / 4;
       tileY = batchNode->getTexture()->getPixelsHigh() / 3;

       tileSprites = vector< vector<Sprite*> > ( w, vector<Sprite*>(h, 0) );
       for(int x = 0; x < w; ++x)
       for(int y = 0; y < h; ++y)
       {
       auto sq = Sprite::createWithTexture(batchNode->getTexture());
       char type = game->getMap()->val(x,y);
       sq->setTextureRect(getRect(type));
       sq->setPosition(origin + Point(tileX/2,tileY/2) + Point(x*tileX, y*tileY));
       batchNode->addChild(sq);
       tileSprites[x][y] = sq;
       }
       this->addChild(batchNode);*/

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(CruxScene::onKeyPressed, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->schedule( schedule_selector(CruxScene::gameLoop), 1.0 );


    return true;
}

#define REKT(x,y,a,b) Rect( x * a, y * b, a, b )

Rect CruxScene::getRect(char type)
{
    switch(type)
    {
        case '.': return REKT(0,0, tileX, tileY);
        case '|': return REKT(1,0, tileX, tileY);
        case '#': return REKT(2,0, tileX, tileY);
        case '*': return REKT(3,0, tileX, tileY);
        case '=': return REKT(0,1, tileX, tileY);
        case '~': return REKT(1,1, tileX, tileY);
        case '/': return REKT(2,1, tileX, tileY);
        default: return REKT(3,1, tileX, tileY);
    }
}

void CruxScene::addEnemy()
{
    auto target = Sprite::create("Target.png", Rect(0,0,27,40));

    int enemyHeight = target->getContentSize().height;
    int enemyWidth = target->getContentSize().width;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    int minY = enemyHeight/2;
    int maxY = visibleSize.height - enemyHeight/2;
    int rangeY = maxY - minY;
    // srand( TimGetTicks() );
    int actualY = ( rand() % rangeY ) + minY;

    // Create the target slightly off-screen along the right edge,
    // and along a random position along the Y axis as calculated
    target->setPosition( Point(origin.x + visibleSize.width + (enemyWidth/2), actualY) );
    this->addChild(target);

    // Determine speed of the target
    int minDuration = (int)2.0;
    int maxDuration = (int)4.0;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = ( rand() % rangeDuration ) + minDuration;

    std::function<void(Node*)> callbackFunction = std::bind( &CruxScene::spriteMoveFinished, this, std::placeholders::_1 );

    // Create the actions
    FiniteTimeAction* actionMove;
    FiniteTimeAction* actionMoveDone;
    actionMove = MoveTo::create( (float)actualDuration, Point(origin.x - target->getContentSize().width/2, actualY) );
    actionMoveDone = CallFuncN::create(callbackFunction);

    target->runAction( Sequence::create(actionMove, actionMoveDone, NULL) );
}

void CruxScene::spriteMoveFinished(Node* sender)
{
    Sprite* sprite = (Sprite*)sender;
    this->removeChild(sprite, true);
}

void CruxScene::gameLoop(float dt)
{
    //game->update();
}

//Callback from game
void CruxScene::gameUpdated()
{
    // update player sprit
    Pos2 p = game->getPlayer()->getPosition(); 
    Point target = background->getPositionAt(Point(p.x, p.y));

    FiniteTimeAction* actionMove = MoveTo::create(0.05f, target);
    player->runAction(actionMove);

    //update action points label
    stringstream ss("Action Points: ");
    ss << ss.rdbuf() << game->getPlayer()->getActionPoints();
    actionPointsLabel->setString(ss.str());

    //update game state label
    ss.str("Game State: ");
    ss << ss.rdbuf() << (int)game->getGameState();
    gameStateLabel->setString(ss.str());

    // updated npc sprites
    for(int i=0; i<npcSprites.size(); i++) {
        p=game->getNPC(i).getPos();
        Point target = background->getPositionAt(Point(p.x, p.y));

        FiniteTimeAction* actionMove = MoveTo::create(0.05f, target);
        npcSprites[i]->runAction(actionMove);
    }
}

void CruxScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            game->move(UP);
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            game->move(DOWN);
            break;
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            game->move(LEFT);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            game->move(RIGHT);
            break;
        case EventKeyboard::KeyCode::KEY_A:
            game->finishPlayerTurn();
            break;
        case EventKeyboard::KeyCode::KEY_R:
            initializeGame();
            break;
        case EventKeyboard::KeyCode::KEY_ESCAPE:
            Director::getInstance()->end();
            break;
        default:
            break;
    }
}

void CruxScene::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
