#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

#define GROUND_PX 20

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    
    addChild(rootNode);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    /*
    auto label = Label::createWithTTF("Frick-Flicker!", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);*/

    // イベント
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    CCLOG("visibleSize : %f , %f" , visibleSize.width, visibleSize.height);
    
    //柵
    auto center = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);
    this->createGround(Rect(GROUND_PX/2, center.y, GROUND_PX, visibleSize.height));
    this->createGround(Rect(visibleSize.width - GROUND_PX/2, center.y, GROUND_PX, visibleSize.height));
    this->createGround(Rect(center.x, GROUND_PX/2 + origin.y, visibleSize.width , GROUND_PX));
    this->createGround(Rect(center.x, visibleSize.height - GROUND_PX/2 + origin.y, visibleSize.width , GROUND_PX));
    
    
    //add Player
    auto me = this->createCharacter(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    me->setTag(1);

    // add update
    this->scheduleUpdate();
    this->schedule(schedule_selector(HelloWorld::testTimer), 3);
    return true;
}
void HelloWorld::testTimer(float time)
{}
void HelloWorld::update(float delta)
{}


void HelloWorld::createGround (Rect rect){
    Sprite* floor = Sprite::create();
    floor->setColor(Color3B::WHITE);
    floor->setTextureRect(rect);
    floor->setContentSize(rect.size);
    floor->setPosition(rect.origin);
    PhysicsBody* floorPb = PhysicsBody::createBox(rect.size);
    floorPb->setDynamic(false);
    floor->setPhysicsBody(floorPb);
    this->addChild(floor);
}
Sprite* HelloWorld::createCharacter (Vec2 position){
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create();
    sprite->setTag(1);
    
    // position the sprite on the center of the screen
    sprite->setContentSize(Size(80,80));
    sprite->setTextureRect(Rect(0,0, 80, 80));
    sprite->setColor(Color3B::WHITE);
    sprite->setPosition(position);
    PhysicsBody* body = PhysicsBody::createCircle(40);
    
    body->setMass(1.0f); // 重さ
    body->setMoment(1000.0f); // モーメント
    sprite->setPhysicsBody(body);
    
    auto force = Vec2 (100,100);
    body->applyImpulse(force);
    
    // add the sprite as a child to this layer
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
    Sprite* character = (Sprite*)this->getChildByTag(1);
    Rect characterRect = getRect(character);
    touchPoint = touch->getLocation();
    return characterRect.containsPoint(touchPoint);
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){}
void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    Sprite* character = (Sprite*)this->getChildByTag(1);
    Point endPoint = touch->getLocation();
    Vect force = Vect(touchPoint.x - endPoint.x, touchPoint.y - endPoint.y) * 4;
    character->getPhysicsBody()->applyImpulse(force);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
