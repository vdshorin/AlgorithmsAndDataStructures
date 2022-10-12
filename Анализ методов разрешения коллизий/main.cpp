#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <time.h>
#include <iomanip>
#include "Functions.h"

using namespace std;

void CreateKeys(int num)
{
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    string res;

    ofstream out;
    out.open("keys.txt");

    if (out.is_open())
    {
        for (int i = 0; i < num; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                res += alphanum[rand() % (sizeof(alphanum) - 1)];
            }
            out << res << endl;
            res = "";
        }
    }

}
int CreateTable(int (*method)(int, int), int (*checker)(int, int, int), int M, int keysCount)
{
    string key;
    ifstream in("keys.txt");

    string array[M];
    vector<int> res;

    int testLimit = M;
    int j = 0;

    while(j != keysCount)
    {
        getline(in, key);
        int i = 0;

        while(i != testLimit)
        {
            int a = checker(method(HashExcludive(key), M), i, M);
            if(array[a].empty())
            {
                array[a] = key;
                res.push_back(i);
                break;
            }
            else if (array[a] == key)
            {
                res.push_back(i);
                break;
            }
            else
            {
                i++;
            }
        }
        res.push_back(i);
        j++;
    }

    int sum = 0;
    for (int re : res)
    {
        sum += re;
    }

    return sum;
}

int main()
{
    srand(time(nullptr));

    int _M = 500;
    int _keysCount = 500;
    int _maxKeys = 500;

    ofstream out;
    out.open("result.txt");

    int count;

    CreateKeys(_keysCount);

    float data[4][_maxKeys / 10];
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < _maxKeys / 10; ++j)
        {
            data[i][j] = 0;
        }
    }

    for (int k = 10; k <= _maxKeys; k += 10)
    {
        count = CreateTable(HashDivision, CheckLinear, _M, k);
        data[0][k / 10 - 1] += float(count) / k;

        count = CreateTable(HashMultiply, CheckLinear, _M, k);
        data[1][k / 10 - 1] += float(count) / k;

        count = CreateTable(HashDivision, CheckSquare, _M, k);
        data[2][k / 10 - 1] += float(count) / k;

        count = CreateTable(HashMultiply, CheckSquare, _M, k);
        data[3][k / 10 - 1] += float(count) / k;
    }

    for (int i = 10; i <= _maxKeys; i += 10)
    {
        out << i << setw(7);
    }
    out << endl;

    out.setf(ios::left);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < _maxKeys / 10; ++j)
        {
            out << data[i][j] << setprecision(3) << setw(7);
        }
        out << endl;
    }

    return 0;
}
