#include <iostream>
#include <fstream>
#include <vector>
#include "BinaryTreeNode.h"
#include "Functions.h"

using namespace std;

// Поиск вершин, у которых количество потомков в левом поддереве
// отличается от количества потомков в правом поддереве на единицу,
// на основе рекурсивного алгоритма восходящего обхода.
void ShowNodes(BinaryTreeNode *&binaryTreeNode)
{
    if(binaryTreeNode != nullptr)
    {
        cout << "Nodes:" << endl;
        NodesInTree(binaryTreeNode);
    }
    else
    {
        cout << "Tree is empty" << endl;
    }
}

// Поиск k-го в порядке слева направо листа дерева (k задается пользова-телем)
// на основе рекурсивного алгоритма смешанного обхода.
void FindLeaf(BinaryTreeNode *binaryTreeNode)
{
    int userK = 0;
    int currentK = 0;
    cout << "Enter number of leaf from left to the right:";
    cin >> userK;

    FindLeafInTree(binaryTreeNode, userK, &currentK);
}

// Удаление вершины по ключу, заданному пользователем, на основе операции поиска исключением.
void DeleteNode(BinaryTreeNode *binaryTreeNode)
{
    int key = -1;

    cout << "Enter key to delete:";
    cin >> key;
    if(SearchInTree(binaryTreeNode, key))
    {
        DeleteNodeInTree(binaryTreeNode, key);
    }
    else
    {
        cout << "No suck element" << endl;
    }
}

int main() {

    fstream _readNums(R"(C:\Users\vscho\CLionProjects\Algorithms_Lab3\db.txt)");
    vector<int> _numbers;

    if(_readNums.is_open())
    {
        int num;
        while(_readNums >> num)
        {
            _numbers.push_back(num);
        }
    }
    else
    {
        cout << "File is not open" << endl;
    }

    int _command = -1;

    BinaryTreeNode *_binaryTreeRoot = nullptr;
    Add(_binaryTreeRoot, _numbers[0]);
    for (int i = 1; i < _numbers.size(); ++i)
    {
        Add(_binaryTreeRoot, _numbers[i]);
    }

    while (true)
    {
        cout << "1 - Nodes" << endl;
        cout << "2 - Height of tree" << endl;
        cout << "3 - Find your leaf" << endl;
        cout << "4 - Delete node" << endl;
        cout << "5 - Search value" << endl;
        cout << "0 - Exit" << endl;
        cout << "Your choice:";
        cin >> _command;

        switch (_command)
        {
            case 1:
            {
                ShowNodes(_binaryTreeRoot);
                break;
            }
            case 2:
            {
                TreeHeight(_binaryTreeRoot);
                break;
            }
            case 3:
            {
                FindLeaf(_binaryTreeRoot);
                break;
            }
            case 4:
            {
                DeleteNode(_binaryTreeRoot);
                break;
            }
            case 5:
            {
                BinaryTreeNode *searchNode = nullptr;
                int searchValue = -1;
                cout << "Search value:";
                cin >> searchValue;
                searchNode = SearchInTree(_binaryTreeRoot, searchValue);
                if(searchNode != nullptr)
                {
                    cout << "This element exists in tree" << endl;
                    cout << "Value: " << searchNode->_value << endl;
                }
                else
                {
                    cout << "This element doesnt exists in tree" << endl;
                }
                break;
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                cout << "Undefined operation..." << endl;
            }
        }
    }
}