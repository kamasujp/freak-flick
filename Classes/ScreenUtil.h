//
//  ScreenUtil.h
//  CocosProject
//
//  Created by YAMADAKYOHEI on 2015/08/04.
//
//

#ifndef __CocosProject__ScreenUtil__
#define __CocosProject__ScreenUtil__

#include <stdio.h>

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


class ScreenUtil {
public:
    static Node* getChildbyTagRecursively(Node* target, int tag);
    static Node* cloneNode(Node* source);
    static float getTime ();
    
};

#endif /* defined(__CocosProject__ScreenUtil__) */
