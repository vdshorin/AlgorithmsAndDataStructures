#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <time.h>
#include "Functions.h"

using namespace std;

void DictInsert(int *dict, int index, int M)
{

//    if(dict.find(index) == dict.end())
//    {
//        dict.insert(pair<int, int>(index, 0));
//    }
//    else
//    {
//        dict[index]++;
//    }
}

void Print(map<int, int> &dict, ofstream &ofstream)
{
    map <int, int>::iterator it;
    for (it = dict.begin(); it != dict.end(); it++)
    {
        ofstream << (*it).first << "    " << (*it).second << endl;
    }
}

string CreateKey()
{
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    string res;

    for (int i = 0; i < 6; ++i)
    {
        res += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    //cout << "KEY: " << res << endl;

    return res;
}

int main() {

    srand(time(nullptr));

    int _keysCount = 250;
    int _M = 251;

    int dictAddDiv[_M];
    for (int k = 0; k < _M; ++k) {
        dictAddDiv[k] = 0;
    }
    int dictAddMult[_M];
    for (int k = 0; k < _M; ++k) {
        dictAddMult[k] = 0;
    }
    int dictExcDiv[_M];
    for (int k = 0; k < _M; ++k) {
        dictExcDiv[k] = 0;
    }
    int dictExcMult[_M];
    for (int k = 0; k < _M; ++k) {
        dictExcMult[k] = 0;
    }

    vector<string> _keys;

    for (int i = 0; i < _keysCount; ++i)
    {
        _keys.push_back(CreateKey());
    }

    for (int i = 0; i < _keysCount; ++i)
    {
        int index = HashDivision(HashAdditive(_keys[i]), _M);
        dictAddDiv[index]++;

        index = HashMultiply(HashAdditive(_keys[i]), _M);
        dictAddMult[index]++;

        index = HashDivision(HashExcludive(_keys[i]), _M);
        dictExcDiv[index]++;

        index = HashMultiply(HashExcludive(_keys[i]), _M);
        dictExcMult[index]++;
    }

    ofstream fout;
    fout.open("data.txt");

    fout << "AddDiv" << endl;
    fout << "Value" << endl;
    for (int j = 0; j < _M; ++j)
    {
        if(dictAddDiv[j] != 0)
        {
            fout << dictAddDiv[j] - 1 << endl;
            continue;
        }
        fout << dictAddDiv[j] << endl;
    }

    fout << endl << "AddMult" << endl;
    fout << "Value" << endl;
    for (int j = 0; j < _M; ++j)
    {
        if(dictAddMult[j] != 0)
        {
            fout << dictAddMult[j] - 1 << endl;
            continue;
        }
        fout << dictAddMult[j] << endl;
    }

    fout << endl << "ExcDiv" << endl;
    fout << "Value" << endl;
    for (int j = 0; j < _M; ++j)
    {
        if(dictExcDiv[j] != 0)
        {
            fout << dictExcDiv[j] - 1 << endl;
            continue;
        }
        fout << dictExcDiv[j] << endl;
    }

    fout << endl << "ExcMult" << endl;
    fout << "Value" << endl;
    for (int j = 0; j < _M; ++j)
    {
        if(dictExcMult[j] != 0)
        {
            fout << dictExcMult[j] - 1 << endl;
            continue;
        }
        fout << dictExcMult[j] << endl;
    }

    fout.close();

    return 0;
}