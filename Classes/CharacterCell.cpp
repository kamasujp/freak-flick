//
//  CharacterCell.cpp
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/04.
//
//

#include "CharacterCell.h"
#define UP_POSITION_OFFSET 10


bool CharacterCell::initWithFile(std::string filepath) {
    if (!Sprite::initWithFile(filepath)) {
        return false;
    }
    return true;
}
void CharacterCell::setPosition(const cocos2d::Vec2 &pos){
    Sprite::setPosition(pos);
    originPos = pos;
    upPos = pos + Vec2( 0 , UP_POSITION_OFFSET);
}

void CharacterCell::update(float delta){
    
}
void CharacterCell::moveUpward(){
    runAction(EaseOut::create(MoveTo::create(0.2f, upPos ),2));
}
void CharacterCell::moveDownward(){
    runAction(EaseOut::create(MoveTo::create(0.2f, originPos ),2));
}
