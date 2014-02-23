#include "HelloWorldScene.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::~HelloWorld()
{
    if(game) delete game;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    game = new Game();
    game->initialize(this);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");
    //sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //this->addChild(sprite, 0);


    auto player = Sprite::create("Player.png");
    player->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(player, 5);

    this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );

    int w = game->getMap()->getWidth();
    int h = game->getMap()->getHeight();
    tileSprites = vector< vector<Sprite*> > ( w, vector<Sprite*>(h, 0) );
    for(int x = 0; x < w; ++x)
        for(int y = 0; y < h; ++y)
        {
            auto sq = Sprite::create("Projectile.png");
            sq->setPosition(Point( visibleSize.width/2 + x * sq->getContentSize().width, visibleSize.height/2 + y * sq->getContentSize().height ) );
            this->addChild(sq);
            tileSprites[x][y] = sq;
        }
    
    return true;
}

void HelloWorld::drawTile() {
	
    auto white = Sprite::create("tilea.png");
    auto black = Sprite::create("tileb.png");
	for(int x=0; x<10; x++)
		for(int y=0; y<10; y++) {
			player->setPosition(Point(k*visibleSize.width/10 + origin.x, l*visibleSize.height/2 + origin.y));
			player->setPosition(Point(k*visibleSize.width/10 + origin.x, l*visibleSize.height/2 + origin.y));
		}
    this->addChild(player);
}


void HelloWorld::addEnemy()
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

    std::function<void(Node*)> callbackFunction = std::bind( &HelloWorld::spriteMoveFinished, this, std::placeholders::_1 );

    // Create the actions
    FiniteTimeAction* actionMove;
    FiniteTimeAction* actionMoveDone;
    actionMove = MoveTo::create( (float)actualDuration, Point(origin.x - target->getContentSize().width/2, actualY) );
    actionMoveDone = CallFuncN::create(callbackFunction);

    target->runAction( Sequence::create(actionMove, actionMoveDone, NULL) );
}

void HelloWorld::spriteMoveFinished(Node* sender)
{
    Sprite* sprite = (Sprite*)sender;
    this->removeChild(sprite, true);
}

void HelloWorld::gameLogic(float dt)
{
    game->move(UP);
    game->update();
}

void HelloWorld::gameUpdated()
{
    for(int x = 0; x < tileSprites.size(); ++x)
        for(int y = 0; y < tileSprites[0].size(); ++y)
            tileSprites[x][y]->setVisible( game->getMap()->val(x,y) );
}

void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
