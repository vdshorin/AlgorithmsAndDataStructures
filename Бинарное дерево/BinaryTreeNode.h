#ifndef ALGORITHMS_LAB3_BINARYTREENODE_H
#define ALGORITHMS_LAB3_BINARYTREENODE_H

class BinaryTreeNode {
public:
    BinaryTreeNode *_left = nullptr;
    BinaryTreeNode *_right = nullptr;
    int _value = -1;

    BinaryTreeNode(){}

    BinaryTreeNode(int value)
    {
        _value = value;
    }
};
#endif //ALGORITHMS_LAB3_BINARYTREENODE_H