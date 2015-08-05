//
//  Ball.cpp
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/05.
//
//

#include "Ball.h"

#define AIR_RESISTANCE 0.5f
#define VELOCITY_DUMP 20

bool Ball::initWithFile(std::string filepath) {
    if (!Node::init()){
        return false;
    }
    
    textureName = filepath;
    
    sprite = Sprite::create(filepath);
    
    shadow = Sprite::create(filepath);
    shadow -> setScaleY(0.5f);
    shadow -> setColor(Color3B(0, 0, 0 ));
    shadow -> setOpacity(80);
    shadow -> setPosition(Vec2(0 , - sprite -> getContentSize().height * 0.26f) );
    
    
    
    this->addChild(shadow);
    this->addChild(sprite);
    
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.density     = 1.0f; // 密度
    material.restitution = 0.95f; // 反発係数
    material.friction = 0.5f;
    
    body = this -> createPhysicBody(material);
    
    body->setMass(1.0f); // 重さ
    body->setMoment(std::numeric_limits<float>::infinity()); // モーメント
    //body->setCategoryBitmask(1);
    body->setContactTestBitmask(1);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Ball::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(contactListener, 10);
    
    this -> setPhysicsBody(body);
    this -> Sprite::scheduleUpdate();
    
    randomSeed = ((float)(rand() % 1000))/1000;
    
    return true;
}

bool Ball::onContactBegin(PhysicsContact& contact){
    return true;
}

void Ball::update(float delta){
    if (isMoving()){
        //air resistance
        auto velocity = body -> getVelocity();
        auto length = velocity.length();
        if (length < VELOCITY_DUMP){
            body -> setVelocity( Vec2::ZERO );
        }else{
            auto dir = Vec2(velocity);
            dir.normalize();
            body -> setVelocity( velocity - (length * delta * AIR_RESISTANCE) * dir );
        }
    }
    //floating
    floatingPos = sin(ScreenUtil::getTime() * 3.0f + randomSeed * 3.14f) * Vec2(0 , 3);
    
    computePosition();
}

void Ball::computePosition(){
    if (!isMoving()){
        sprite -> setPosition( floatingPos );
    }else{
        sprite -> setPosition( Vec2::ZERO );
    }
}

inline bool Ball::isMoving(){
    return body -> getVelocity().length() != 0;
}

Ball::~Ball (){}