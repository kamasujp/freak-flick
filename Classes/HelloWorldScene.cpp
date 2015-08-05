#include "HelloWorldScene.h"
#import <TargetConditionals.h>

USING_NS_CC;

#define COLLIDER_TAG 100
#define CELL_TAG 200
#define HP_GAGE_TAG 300
#define PULL_FORCE 10



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    
    auto scene = Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity(Vec2(0,0));
#if TARGET_IPHONE_SIMULATOR
    //物理オブジェクトにを可視的にしてくれるデバックモード
    //world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    // return the scene
    return scene;
}
HelloWorld* HelloWorld::instance;
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    instance = this;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
    
    // イベント
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //HPゲージ
    hpGage = (Sprite *)rootNode->getChildByName("hp_front");
    hpGageMaxScaleX = hpGage -> getScaleX();
    hpLeft = hpMax;
    
    //柵
    auto center = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->setCollider(COLLIDER_TAG + 0);
    this->setCollider(COLLIDER_TAG + 1);
    this->setCollider(COLLIDER_TAG + 2);
    this->setCollider(COLLIDER_TAG + 3);
    
    //Player
    auto pos = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    
    players.pushBack(this->addPlayer( 0 , pos));
    players.pushBack(this->addPlayer( 1 , pos));
    players.pushBack(this->addPlayer( 2 , pos));
    players.pushBack(this->addPlayer( 3 , pos));
    nowPlayer = 0;
    
    //Player Cell
    cells.pushBack(this->addCell( 0 ));
    cells.pushBack(this->addCell( 1 ));
    cells.pushBack(this->addCell( 2 ));
    cells.pushBack(this->addCell( 3 ));
    cells.at(0) -> moveUpward();
    
    //Enemy
    auto e_pos = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    
    enemies.pushBack(this->addEnemy( 0 , e_pos));
    //enemies.pushBack(this->addEnemy( 1 , e_pos));
    //enemies.pushBack(this->addEnemy( 2 , e_pos));
    
    
    
    // add update
    this->scheduleUpdate();
    this->schedule(schedule_selector(HelloWorld::testTimer), 3);
    return true;
}
void HelloWorld::testTimer(float time)
{
}
void HelloWorld::update(float delta)
{
}

void HelloWorld::setCollider (int tag){
    Sprite* floor = (Sprite *)ScreenUtil::getChildbyTagRecursively(this, tag);
    auto size = Size(floor ->getContentSize().width * floor->getScaleX()
                     , floor ->getContentSize().height * floor->getScaleY());
    PhysicsBody* floorPb = PhysicsBody::createBox(size);
    
    floorPb->setDynamic(false);
    floor->setPhysicsBody(floorPb);
}

CharacterBall* HelloWorld::addPlayer (int type , Vec2 position){
    //add Player
    auto ball = CharacterBall::create(StringUtils::format("ball_%d.png",type));
    ball->setPosition(position);
    this->addChild(ball, 0);
    return ball;
}

EnemyBall* HelloWorld::addEnemy (int type , Vec2 position){
    //add Player
    auto ball = EnemyBall::create(StringUtils::format("enemy_%d.png",type));
    ball->setPosition(position);
    this->addChild(ball, 0);
    return ball;
}

CharacterCell* HelloWorld::addCell (int type){
    //add Player
    auto raw = (Sprite *)ScreenUtil::getChildbyTagRecursively(this, CELL_TAG + type);
    auto sprite = CharacterCell::create(StringUtils::format("cell_%d.png",type));
    sprite->setPosition(raw->getPosition());
    raw -> removeFromParent();
    this->addChild(sprite, 0);
    return sprite;
}


// タップ
Rect HelloWorld::getRect(Node* node)
{
    Point point = node->getPosition();
    int width = node->getContentSize().width;
    int height = node->getContentSize().height;
    return Rect(point.x - (width / 2), point.y - (height / 2), width, height);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    if (!screenBlock){
        touchPoint = touch->getLocation();
        players.at(nowPlayer)->setJitter(5);
        return true;
    }else{
        return false;
    }
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    Point endPoint = touch->getLocation();
    Vect force = Vect(touchPoint.x - endPoint.x, touchPoint.y - endPoint.y) * PULL_FORCE;
    players.at(nowPlayer)->getPhysicsBody()->applyImpulse(force);
    players.at(nowPlayer)->setJitter(0);
    screenBlock = true;
    this->schedule(schedule_selector(HelloWorld::checkPlayerMoving) , 0.5f );
}
void HelloWorld::checkPlayerMoving(float time){
    auto frag = false;
    auto it = players.begin();
    for (; it!=players.end() ; ++it ){
        frag |= (*it) -> isMoving();
    }
    if (!frag){
        //全員停止
        this->unschedule(schedule_selector(HelloWorld::checkPlayerMoving));
        screenBlock = false;
        cells.at(nowPlayer) -> moveDownward();
        nowPlayer = (nowPlayer + 1)%4;
        cells.at(nowPlayer) -> moveUpward();
    }
}

void HelloWorld::refleshHp(){
    hpGage -> runAction(EaseOut::create(ScaleTo::create(0.2f, hpGageMaxScaleX * ( ((double)hpLeft) / ((double)hpMax) ) , hpGage -> getScaleY()), 2) );
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
