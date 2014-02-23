#include "CruxSceneScene.h"
#include <iostream>
using namespace std;

USING_NS_CC;

Scene* CruxScene::createScene()
{
    // 'scene' is an autorelease object
    // 'layer' is an autorelease object
    auto scene = Scene::create();
    auto layer = CruxScene::create();
    scene->addChild(layer);
    return scene;
}

CruxScene::CruxScene()
{
    game = new game;
    player = 0;
}

CruxScene::~CruxScene()
{
    delete game;
}

bool CruxScene::init()
{
    if ( !Layer::init() )
        return false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //Menu with close button
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(CruxScene::menuCloseCallback, this));
	closeItem->setPosition(origin + Point(visibleSize.width - closeItem->getContentSize().width/2 ,
                                closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    //Title
    auto label = LabelTTF::create("--~~** Crux **~~--", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    // add "CruxScene" splash screen"
    //auto sprite = Sprite::create("CruxScene.png");
    //sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //this->addChild(sprite, 0);

    //Create player sprite
    player = Sprite::create("Player.png");
    player->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(player, 5);

    //Load game
    game->initialize(this);
    
    this->schedule( schedule_selector(CruxScene::gameLoop), 1.0 );

    int w = game->getMap()->getWidth();
    int h = game->getMap()->getHeight();
    tileSprites = vector< vector<Sprite*> > ( w, vector<Sprite*>(h, 0) );
    for(int x = 0; x < w; ++x)
        for(int y = 0; y < h; ++y)
        {
            auto sq = Sprite::create("tilea.png");
            sq->setPosition(Point( visibleSize.width/2 + x * sq->getContentSize().width, visibleSize.height/2 + y * sq->getContentSize().height ) );
            this->addChild(sq);
            tileSprites[x][y] = sq;
        }

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(CruxScene::onKeyPressed, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
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
    game->update();
}

//Callback from game
void CruxScene::gameUpdated()
{
    for(int x = 0; x < tileSprites.size(); ++x)
        for(int y = 0; y < tileSprites[0].size(); ++y)
            tileSprites[x][y]->setTexture( game->getMap()->val(x,y) ? "tilea.png" : "tileb.png" );
    if(tileSprites.empty()) return;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int x = game->getPlayer()->x;
    int y = game->getPlayer()->y;
    auto sq = tileSprites[0][0];
    player->setPosition(Point( visibleSize.width/2 + x * sq->getContentSize().width, visibleSize.height/2 + y * sq->getContentSize().height ) );
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
