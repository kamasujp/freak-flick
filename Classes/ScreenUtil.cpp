//
//  ScreenUtil.cpp
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/04.
//
//

#include "ScreenUtil.h"
#include <time.h>


Node* ScreenUtil::getChildbyTagRecursively(Node* target, int tag)
{
    CCAssert(target != NULL, "Invalid target");
    
    Node *node = target->getChildByTag(tag);
    if (node == NULL) {
        auto children = target->getChildren();
        int cnt = 0;
        
        for (cnt = 0; cnt < children.size() ; ++cnt) {
            target = children.at(cnt);
            node = getChildbyTagRecursively(target, tag);
            if (node != NULL) {
                break;
            }
        }
    }
    return node;
}
Node* ScreenUtil::cloneNode(Node* source)
{
    Node* clone;
    
    if (auto sprite = dynamic_cast<Sprite *>(source) ) {
        clone = Sprite::createWithTexture(sprite -> getTexture());
        ((Sprite *)clone) -> setDisplayFrame(sprite -> getDisplayFrame());
    }else{
        clone = Node::create();
    }
    
    clone -> setPosition(source -> getPosition());
    clone -> setScale(source->getScaleX(), source->getScaleY());
    clone -> setAnchorPoint(source->getAnchorPoint());
    clone -> setColor(source->getColor());
    clone -> setOpacity(source -> getOpacity());
    clone -> setName(source->getName());
    
    for (auto child : source -> getChildren()) {
        auto subnode = cloneNode(child);
        clone -> reorderChild(subnode, child -> getLocalZOrder());
        clone -> addChild(subnode);
    }
    
    return clone;
}

float ScreenUtil::getTime (){
    return ((float)clock()) / ((float)CLOCKS_PER_SEC);
}