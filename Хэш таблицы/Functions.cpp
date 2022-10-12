//
// Created by vscho on 03.10.2019.
//

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

int HashAdditive(string key)
{
    int res = 0;

    for (char i : key) {
        res += i;
    }

    return res;
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