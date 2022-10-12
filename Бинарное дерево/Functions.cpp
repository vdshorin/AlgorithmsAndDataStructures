#include <iostream>
#include <vector>
#include <stack>
#include "BinaryTreeNode.h"
#include "Functions.h"

using namespace std;

BinaryTreeNode* FindMin(BinaryTreeNode *root)
{
    while(root->_left != nullptr)
    {
        root = root->_left;
    }
    return root;
}

BinaryTreeNode* DeleteNodeInTree(BinaryTreeNode *binaryTreeNode, int key)
{
    if(binaryTreeNode == nullptr)
    {
        return binaryTreeNode;
    }
    else if(key < binaryTreeNode->_value)
    {
        binaryTreeNode->_left = DeleteNodeInTree(binaryTreeNode->_left, key);
    }
    else if(key > binaryTreeNode->_value)
    {
        binaryTreeNode->_right = DeleteNodeInTree(binaryTreeNode->_right, key);
    }
    else
    {
        // No children
        if(binaryTreeNode->_left == nullptr
           && binaryTreeNode->_right == nullptr
                )
        {
            free(binaryTreeNode);
            return nullptr;
        }
        else if(binaryTreeNode->_left == nullptr)
        {
            BinaryTreeNode *tmp = binaryTreeNode;
            binaryTreeNode = binaryTreeNode->_right;
            free(tmp);
            return binaryTreeNode;
        }
        else if(binaryTreeNode->_right == nullptr)
        {
            BinaryTreeNode *tmp = binaryTreeNode;
            binaryTreeNode = binaryTreeNode->_left;
            free(tmp);
            return binaryTreeNode;
        }
        else
        {
            BinaryTreeNode *tmp = FindMin(binaryTreeNode->_right);
            binaryTreeNode->_value = tmp->_value;
            binaryTreeNode->_right = DeleteNodeInTree(binaryTreeNode->_right, tmp->_value);
            return binaryTreeNode;
        }
    }
    return binaryTreeNode;
}

bool FindLeafInTree(BinaryTreeNode *&binaryTreeNode, int userK, int *currentK)
{
    BinaryTreeNode *currentNode = binaryTreeNode;

    if(currentNode == nullptr)
    {
        return false;
    }

    if(FindLeafInTree(currentNode->_left, userK, currentK))
    {
        return true;
    }
    if(currentNode->_left == nullptr
       && currentNode->_right == nullptr
            )
    {
        if(*currentK == userK)
        {
            cout << "Leaf: " << currentNode->_value << endl;
            return true;
        }
        (*currentK)++;
    }
    FindLeafInTree(currentNode->_right, userK, currentK);
}

int NodesInTree(BinaryTreeNode *&binaryTreeNode)
{
    BinaryTreeNode *currentNode = binaryTreeNode;
    if(currentNode == nullptr)
    {
        return 0;
    }

    int leftChildren = 0;
    int rightChildren = 0;

    leftChildren += NodesInTree(currentNode->_left);
    rightChildren += NodesInTree(currentNode->_right);

    if(abs(leftChildren - rightChildren) == 1)
    {
        cout << "Value: " << currentNode->_value << endl;
    }

    return leftChildren + rightChildren + 1;
}

BinaryTreeNode* SearchInTree(BinaryTreeNode *&binaryTreeNode, int other)
{
    if(binaryTreeNode == nullptr)
    {
        return nullptr;
    }
    // _value more than other.
    if(binaryTreeNode->_value > other)
    {
        SearchInTree(binaryTreeNode->_left, other);
    }
        // _value less than other.
    else if (binaryTreeNode->_value < other)
    {
        SearchInTree(binaryTreeNode->_right, other);
    }
    else if(binaryTreeNode->_value == other)
    {
        return binaryTreeNode;
    }
    else
    {
        return nullptr;
    }
}

void Add(BinaryTreeNode *&binaryTreeNode, int other)
{
    if(SearchInTree(binaryTreeNode, other))
    {
        return;
    }

    if(binaryTreeNode == nullptr)
    {
        binaryTreeNode = new BinaryTreeNode(other);
        return;
    }

    // _value more than other.
    if(binaryTreeNode->_value > other)
    {
        Add(binaryTreeNode->_left, other);
    }
        // _value less than other.
    else if (binaryTreeNode->_value < other)
    {
        Add(binaryTreeNode->_right, other);
    }
    else
    {
        cout << "ADD_return" << endl;
        return;
    }
}

// Нахождение высоты дерева на основе итеративного алгоритма нисходящего обхода.
void TreeHeight(BinaryTreeNode *&binaryTreeNode)
{
    int height = 0;
    int curHeight = 0;
    stack<BinaryTreeNode*> nodes;
    stack<int> heights;
    BinaryTreeNode *currentNode = binaryTreeNode;

    while (currentNode != nullptr)
    {
        if(currentNode->_left != nullptr
           && currentNode->_right != nullptr
                )
        {
            nodes.push(currentNode->_right);
            heights.push(curHeight);
            currentNode = currentNode->_left;
            curHeight++;
        }
        else if(currentNode->_left == nullptr
                && currentNode->_right == nullptr
                )
        {
            if(!nodes.empty())
            {
                currentNode = nodes.top();
                nodes.pop();
                if(curHeight > height)
                {
                    height = curHeight;
                }
                curHeight = heights.top();
                heights.pop();
                curHeight++;
            }
            else
            {
                break;
            }
        }
        else if(currentNode->_left != nullptr
                && currentNode->_right == nullptr
                )
        {
            currentNode = currentNode->_left;
            curHeight++;
        }
        else if(currentNode->_left == nullptr
                && currentNode->_right != nullptr
                )
        {
            currentNode = currentNode->_right;
            curHeight++;
        }
    }
    cout << "Height of tree: " << height << endl;
}
#include "Functions.h"