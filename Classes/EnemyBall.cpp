//
//  EnemyBall.cpp
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/05.
//
//

#include "EnemyBall.h"
#include "HelloWorldScene.h"
#define RADIUS 0.8f
#define GAGE_OFFSET 0.5f

USING_NS_CC;

Node* EnemyBall::enemygage_prefab;

bool EnemyBall::initWithFile(std::string filepath) {
    if (!Ball::initWithFile(filepath)) {
        return false;
    }
    if (EnemyBall::enemygage_prefab == nullptr){
        enemygage_prefab = HelloWorld::instance -> rootNode -> getChildByName("enemy_gage");
        enemygage_prefab -> setVisible(false);
    }
    
    
    //体力ゲージ
    gage = ScreenUtil::cloneNode(enemygage_prefab);
    gage -> setPosition(Vec2(0, - GAGE_OFFSET * sprite->getContentSize().height));
    gageFront = (Sprite *)gage -> getChildByName("front");
    hpGageMaxScaleX = gageFront -> getScaleX();
    this -> addChild(gage);
    hpLeft = hpMax;
    
    
    return true;
}

PhysicsBody* EnemyBall::createPhysicBody(PhysicsMaterial material){
    auto physic = PhysicsBody::createCircle(sprite -> getContentSize().width/2 * RADIUS);
    physic -> setDynamic(false);
    return physic;
}

void EnemyBall::refleshHp(){
    gageFront -> runAction(EaseOut::create(ScaleTo::create(0.2f, hpGageMaxScaleX * ( ((double)hpLeft) / ((double)hpMax) ) , gageFront -> getScaleY()), 2) );
}


void EnemyBall::update(float delta){
    Ball::update(delta);
}

bool EnemyBall::onContactBegin(PhysicsContact& contact){
    
    if ( isMyCollision )
    {
        Ball::onContactBegin(contact);
        hpLeft -= 1000;
        refleshHp();
        
        return true;
    }
    return true;
}
