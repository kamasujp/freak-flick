//
//  CharacterBall.cpp
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/04.
//
//

#include "CharacterBall.h"
#define RADIUS 0.8f

#define CIRCLE_RADIUS 0.9f


USING_NS_CC;

bool CharacterBall::initWithFile(std::string filepath) {
    if (!Ball::initWithFile(filepath)) {
        return false;
    }
    circle = Sprite::create("ball_circle.png");
    circle -> setScale(CIRCLE_RADIUS, CIRCLE_RADIUS);
    this->addChild(circle);
    
    this->reorderChild(sprite, 3);
    this->reorderChild(circle, 2);
    this->reorderChild(shadow, 1);
    
    return true;
}

PhysicsBody* CharacterBall::createPhysicBody(PhysicsMaterial material){
    auto physic =PhysicsBody::createCircle(sprite -> getContentSize().width/2 * RADIUS);
    return physic;
}

void CharacterBall::update(float delta){
    Ball::update(delta);
    
    //circle
    auto opa = (int)(sin((ScreenUtil::getTime() * 3.0f + randomSeed * 3.14f))* 50.0 + 130.0);
    //floating
    circle -> setOpacity(opa);
    
    
    //jitter
    if (_jitterPos.x > 0){
        _jitterPos = Vec2( -_jitter , 0);
    }else{
        _jitterPos = Vec2( _jitter , 0);
    }
}


void CharacterBall::computePosition(){
    if (!isMoving()){
        if (_jitter > 0){
            sprite -> setPosition( _jitterPos );
        }else{
            sprite -> setPosition( floatingPos );
        }
    }else{
        sprite -> setPosition( Vec2::ZERO );
    }
}


void CharacterBall::setJitter (float jitterMagnitude){
    _jitter = jitterMagnitude;
}

