#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CharacterBall.h"
#include "CharacterCell.h"
#include "EnemyBall.h"
#include "ScreenUtil.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    static HelloWorld* instance;

    Node* rootNode;
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float delta);
    void testTimer(float time);
    float testTime;
    cocos2d::Vec2 touchPoint;
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    cocos2d::Sprite* createCharacter (cocos2d::Vec2 position);
    void refleshHp();
    
    void setCollider (int tag);
    cocos2d::Rect getRect(Node* node);
    
    long hpMax = 54826;
    long hpLeft;
    
    Sprite* hpGage;
    float hpGageMaxScaleX;
    
    CharacterBall* addPlayer (int type , Vec2 position);
    CharacterCell* addCell (int type);
    EnemyBall* addEnemy (int type , Vec2 position);
    Vector<CharacterBall *> players;
    Vector<CharacterCell *> cells;
    Vector<EnemyBall *> enemies;
    int nowPlayer;
    bool screenBlock;
    
    void checkPlayerMoving(float time);
};

#endif // __HELLOWORLD_SCENE_H__
