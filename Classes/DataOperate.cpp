//
//  DataOperate.cpp
//  lianliankan
//
//  Created by joe on 14-6-12.
//
//

#include "DataOperate.h"

USING_NS_CC;

CGDataOperate::CGDataOperate(int rows, int cols, int types)
: mRows(rows), mCols(cols), mTypes(types)
{
    mArr = GenerateGameData(rows, cols, types);
    mCurrentNode = nullptr;
}

CGDataOperate::~CGDataOperate()
{
    FreeGameData(mArr);
}

/**
 * rows 行数
 * cols 列数
 * types 图片总类数量
 * int** 返回二位数组，对应显示的列表
 */
int** CGDataOperate::GenerateGameData(int rows, int cols, int types)
{
    if (0 == rows || 0 == cols || 0 == types)
        return nullptr;
    
    int total = rows * cols;
    int *pTotalArray = new int[total];
    memset(pTotalArray, 0, sizeof(int) * total);
    
    int temp = 0;
    // 成对添加图片
    for (int i = 0; i < total/2; i++)
    {
        if (i < types)
            temp = i;
        else
        {
            temp = (int)(arc4random() % 100) * types / 100;
        }
        pTotalArray[i] = temp;
        pTotalArray[i+1] = temp;
    }
    // 数组随机排序
    for (int j = 0; j < total; j++)
    {
        int tempIndex = (int) arc4random() % (total/2) + total/2;
        temp = pTotalArray[j];
        pTotalArray[j] = pTotalArray[tempIndex];
        pTotalArray[tempIndex] = temp;
    }
    
    int** pRet = new int*[rows+2 + 1];
    memset(pRet, 0, sizeof(int*) * (rows+2 + 1));
    for (int n = 0; n < rows + 2; n++)
    {
        pRet[n] = new int[cols+2];
        for (int m = 0; m < cols + 2; m++)
        {
            if (0 == n || rows + 1 == n || 0 == m || cols + 1 == m)
            {
                pRet[n][m] = kEmpty;
            }
            else
            {
                pRet[n][m] = pTotalArray[(n-1)*cols + (m-1)];
            }
        }
    }
    delete[] pTotalArray;
    return pRet;
}

void CGDataOperate::FreeGameData(int** data)
{
    for (int i = 0; i < sizeof(data)/sizeof(int*); i++)
    {
        if (data[i] != 0)
            delete [] data[i];
    }
    delete [] data;
}

void CGDataOperate::AddNode(CGImageNode* node)
{
    mNodes.push_back(node);
    
    ArrNodeItem item(node->getCol(), node->getRow());
    mMapArr[item] = node;
}

void CGDataOperate::RemoveNode(CGImageNode* node)
{
    ArrNodeItem item(node->getCol(), node->getRow());
    mMapArr.erase(item);
    
    ImageNodeVec::iterator itFind = std::find(mNodes.begin(), mNodes.end(), node);
    if (itFind != mNodes.end())
        mNodes.erase(itFind);
}

CGImageNode* CGDataOperate::GetNodeByPoint(const Point& pt)
{
    for (Vector<CGImageNode*>::const_iterator iter = mNodes.begin();
         iter != mNodes.end();
         iter++)
    {
        CGImageNode *node = *iter;
        if (node->getBoundingBox().containsPoint(pt))
        {
            return node;
        }
    }
    return nullptr;
}

bool CGDataOperate::CheckErase(CGImageNode *node1, CGImageNode *node2)
{
    if (node1->getType() != node2->getType()) return false;
    
    std::vector<ArrNodeItem> vecPath;
    // 列相等
    if (node1->getCol() == node2->getCol())
    {
        int i = node1->getCol();
        
        int begin = node1->getRow();
        int end = node2->getRow();
        
        if (begin < end)
        {
            for (int j = begin + 1; j < end; j++)
            {
                ArrNodeItem item(i, j);
                
                ArrNodeItemMap::iterator itFind = mMapArr.find(item);
                if (itFind != mMapArr.end()) return false;
                
                vecPath.push_back(item);
            }
        }
        else
        {
            for (int j = begin - 1; j > end; j--)
            {
                ArrNodeItem item(i, j);
                
                ArrNodeItemMap::iterator itFind = mMapArr.find(item);
                if (itFind != mMapArr.end()) return false;
                
                vecPath.push_back(item);
            }
        }
        return true;
    }
    // 行相等
    if (node1->getRow() == node2->getRow())
    {
        int j = node1->getRow();
        
        int begin = node1->getCol();
        int end = node2->getCol();
        
        if (begin < end)
        {
            for (int i = begin + 1; i < end; i++)
            {
                ArrNodeItem item(i, j);
                
                ArrNodeItemMap::iterator itFind = mMapArr.find(item);
                if (itFind != mMapArr.end()) return false;
                
                vecPath.push_back(item);
            }
        }
        else
        {
            for (int i = begin - 1; i > end; i--)
            {
                ArrNodeItem item(i, j);
                
                ArrNodeItemMap::iterator itFind = mMapArr.find(item);
                if (itFind != mMapArr.end()) return false;
                
                vecPath.push_back(item);
            }
        }
        return true;
    }
    // 不同行列
    
    return false;
}