#ifndef ALGORITHMS_LAB3_FUNCTIONS_H
#define ALGORITHMS_LAB3_FUNCTIONS_H

BinaryTreeNode* FindMin(BinaryTreeNode *root);
BinaryTreeNode* DeleteNodeInTree(BinaryTreeNode *binaryTreeNode, int key);
bool FindLeafInTree(BinaryTreeNode *&binaryTreeNode, int userK, int *currentK);
int NodesInTree(BinaryTreeNode *&binaryTreeNode);
BinaryTreeNode* SearchInTree(BinaryTreeNode *&binaryTreeNode, int other);
void Add(BinaryTreeNode *&binaryTreeNode, int other);
void TreeHeight(BinaryTreeNode *&binaryTreeNode);

#endif //ALGORITHMS_LAB3_FUNCTIONS_H