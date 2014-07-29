//
//  ImageNode.h
//  lianliankan
//
//  Created by joe on 14-6-12.
//
//

#ifndef __lianliankan__ImageNode__
#define __lianliankan__ImageNode__

#include "cocos2d.h"

class CGImageNode : public cocos2d::Sprite
{
    CC_SYNTHESIZE(int, _row, Row)
    CC_SYNTHESIZE(int, _col, Col)
    CC_SYNTHESIZE(int, _type, Type)
    CC_SYNTHESIZE(int, _x, X)
    CC_SYNTHESIZE(int, _y, Y)
private:
    CGImageNode(int row, int col, int type);
    ~CGImageNode();
public:
    static CGImageNode* create(int row, int col, int type, cocos2d::SpriteFrameCache* frameCache);
};

#endif /* defined(__lianliankan__ImageNode__) */
