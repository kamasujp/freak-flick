//
//  CharacterBall.h
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/04.
//
//

#ifndef __CocosProject__CharacterBall__
#define __CocosProject__CharacterBall__

#include <stdio.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Ball.h"

class CharacterBall : public Ball
{
    
public:
    bool initWithFile(std::string filepath);
    CREATE_SPRITE_FUNC(CharacterBall);
    PhysicsBody* createPhysicBody (PhysicsMaterial material);
    
    Sprite* circle;
    
    void setJitter (float jitterMagnitude);
    void update(float delta);
    
protected:
    void computePosition();

private:
    Vec2 _jitterPos;
    float _jitter;
    
};

#endif /* defined(__CocosProject__CharacterBall__) */