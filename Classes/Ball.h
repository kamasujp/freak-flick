//
//  Ball.h
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/05.
//
//

#ifndef __CocosProject__Ball__
#define __CocosProject__Ball__

#include <stdio.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ScreenUtil.h"

class Ball : public Node{
public:
    bool initWithFile (std::string);
    Sprite* sprite;
    Sprite* shadow;
    std::string textureName;

    
    PhysicsBody* body;
    
    virtual ~Ball ();
    virtual PhysicsBody* createPhysicBody (PhysicsMaterial material) = 0;
    virtual void update(float delta);
    virtual bool onContactBegin(PhysicsContact& contact);
    bool isMoving ();
    
    float randomSeed;
    
protected:
    virtual void computePosition();
    Vec2 floatingPos;
};

#endif /* defined(__CocosProject__Ball__) */
