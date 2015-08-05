//
//  EnemyBall.h
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/05.
//
//

#ifndef __CocosProject__EnemyBall__
#define __CocosProject__EnemyBall__

#include <stdio.h>

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Ball.h"

class EnemyBall : public Ball
{
    
public:
    static Node* enemygage_prefab;
    bool initWithFile(std::string filepath);
    CREATE_SPRITE_FUNC(EnemyBall);
    PhysicsBody* createPhysicBody (PhysicsMaterial material);
    bool onContactBegin(PhysicsContact& contact);
    void update(float delta);
    
    long hpMax = 10000;
    long hpLeft;
    float hpGageMaxScaleX;
private:
    Vec2 _origin;
    float _jitter;
    Node* gage;
    Sprite* gageFront;
    
    void refleshHp();
    
};

#endif /* defined(__CocosProject__EnemyBall__) */
