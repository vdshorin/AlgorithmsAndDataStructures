#include <string>
#include <vector>
#include <cmath>
#include "Functions.h"

using namespace std;

int HashDivision(int key, int M)
{
    return key % M;
}

int HashMultiply(int key, int M)
{
    double A = (sqrt(5.0) - 1.0) / 2.0;
    double i;

    return int(M * modf(key * A, &i));
}

int HashExcludive(string key)
{
    int res = 0;
    int r[6] = {17, 71, 512, 23, 5, 97};

    for (int i = 0; i < key.length(); ++i)
    {
        res += key[i] ^ r[i];
    }

    return res;
}

int CheckLinear(int key, int i, int M)
{
    int c = 73;
    return (key + c * i) % M;
}

int CheckSquare(int key, int i, int M)
{
    int c = 73;
    int d = 3;
    return (key + c * i + d * i * i) % M;
}