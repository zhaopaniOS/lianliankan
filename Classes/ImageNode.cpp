//
//  ImageNode.cpp
//  lianliankan
//
//  Created by joe on 14-6-12.
//
//

#include "ImageNode.h"

USING_NS_CC;

CGImageNode::CGImageNode(int row, int col, int type)
: _row(row), _col(col), _type(type), _x(0), _y(0)
{
    
}

CGImageNode::~CGImageNode()
{
    
}

CGImageNode* CGImageNode::create(int row, int col, int type, cocos2d::SpriteFrameCache* frameCache)
{
    auto spriteFrame = frameCache->getSpriteFrameByName(StringUtils::format("%d.png", type+1));
    CGImageNode* sprite = new CGImageNode(row, col, type);
    if (spriteFrame && sprite && sprite->initWithSpriteFrame(spriteFrame))
    {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}