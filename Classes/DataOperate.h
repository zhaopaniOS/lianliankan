//
//  DataOperate.h
//  lianliankan
//
//  Created by joe on 14-6-12.
//
//

#ifndef __lianliankan__DataOperate__
#define __lianliankan__DataOperate__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <map>

#include "ImageNode.h"

// 连连看数据数组中空值
#define kEmpty -1

// 图片四条边的方向
// 总的方向数
#define kTargetNum 4
// 向上
#define kTargetUp 0
// 向右
#define	kTargetRight 1
// 向下
#define kTargetDown 2
// 向左
#define kTargetLeft 3

typedef struct _t_ArrNodeItem{
    int col;
    int row;
    
    _t_ArrNodeItem(int _col, int _row)
    {
        col = _col;
        row = _row;
    }
}ArrNodeItem;

struct ArrNodeItemLess : std::binary_function<ArrNodeItem, ArrNodeItem, bool>
{
    bool operator()(const ArrNodeItem &item1, const ArrNodeItem &item2) const
    {
        if (item1.col < item2.col) return true;
        if (item1.row < item2.row) return true;
        return false;
    }
};

inline bool operator<(const ArrNodeItem& item1, const ArrNodeItem& item2)
{
    if (item1.row < item2.row) return true;
    if (item1.row > item2.row) return false;
    if (item1.col < item2.col) return true;
    return false;
}

inline bool operator==(const ArrNodeItem& item1, const ArrNodeItem& item2)
{
    return item1.col == item2.col && item1.row == item2.row;
}

class CGDataOperate
{
public:
    CGDataOperate(int rows, int cols, int types);
    ~CGDataOperate();
public:
    int GetRows(){return mRows;};
    int GetCols(){return mCols;};
    int GetTypes(){return mTypes;};
    int** GetArr(int &rows, int &cols){rows = mRows+2;cols = mCols+2;return mArr;};
private:
    static int** GenerateGameData(int rows, int cols, int types);
    static void FreeGameData(int** data);
private:
    int mRows;
    int mCols;
    int mTypes;
    int** mArr;
public:
    void AddNode(CGImageNode* node);
    void RemoveNode(CGImageNode* node);
    CGImageNode* GetNodeByPoint(const cocos2d::Point& pt);
    CGImageNode* GetCurrentNode(){return mCurrentNode;};
    void SetCurrentNode(CGImageNode* node){mCurrentNode = node;};
    bool CheckErase(CGImageNode *node1, CGImageNode *node2);
private:
    typedef std::vector<CGImageNode*> ImageNodeVec;
    ImageNodeVec mNodes;
    
    typedef std::map<ArrNodeItem, CGImageNode*> ArrNodeItemMap;
    ArrNodeItemMap mMapArr;
    
    CGImageNode *mCurrentNode;
};

#endif /* defined(__lianliankan__DataOperate__) */
