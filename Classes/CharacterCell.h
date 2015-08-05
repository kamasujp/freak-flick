//
//  CharacterCell.h
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/04.
//
//

#ifndef __CocosProject__CharacterCell__
#define __CocosProject__CharacterCell__

#include <stdio.h>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


class CharacterCell : public Sprite
{
public:
    CREATE_SPRITE_FUNC(CharacterCell);
    virtual bool initWithFile(std::string filepath);
    void setPosition(const cocos2d::Vec2 &pos);
    void update (float delta);
    void moveUpward ();
    void moveDownward ();
    
private:
    Vec2 originPos;
    Vec2 upPos;
};


#endif /* defined(__CocosProject__CharacterCell__) */
