#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <sstream>
#include <vector>

#define MAX_KEYS 10000

int _keysCount = MAX_KEYS;
int _LCount = 0;

using namespace std;

//region Structs

struct Node
{
    int key;
    char data[196];
};

//endregion

//region Create Source File

int CreateRandomKey()
{
    return 1 + rand() % _keysCount;
}

void CreateSourceFile()
{
    ofstream fout;
    fout.open("source.out", ios::binary);
    if(!fout.is_open())
    {
        cout << "Can`t open file" << endl;
        return;
    }

    for (int i = 0; i < _keysCount; i++)
    {
        Node node{};
        node.key = CreateRandomKey();
        //cout << "KEY: " << node.key << endl;
        fout.write((char*)&node, sizeof(Node));
    }

    fout.close();
}

//endregion

//region File functions

void CloseAllFiles(fstream f[], int N)
{
    for (int i = 0; i < 2 * N; ++i)
    {
        f[i].close();
    }
}

//endregion

void BMerge(int N)
{
    // Source file.
    ifstream f0;

    fstream f[2 * N];

    //region INT variables

    // File access index card.
    int t[2 * N];
    for (int i = 0; i < 2 * N; ++i)
    {
        t[i] = 0;
    }

    // количество полученных в результате слияния за проход отрезков.
    // The number of segments obtained as a result of the merger per pass.
    int L = 0;

    // Number of active files.
    int af = 0;

    // Number of active files with active segments.
    int ao = 0;

    // Index of next output file.
    int j = 0;

    // Index of the file from which the minimum key was copied during the merge.
    int m = MAX_KEYS + 5;

    // An array of indexes of active files in which there are active segments.
    int ta[N];
    for (int i = 0; i < N; ++i)
    {
        ta[i] = 0;
    }

    //endregion

    // Open for reading f0.
    f0.open("source.out", fstream::in | fstream::binary);

    //region Open for writing f[1]-f[N]
    for (int i = 0; i < N; ++i)
    {
        ostringstream filename;
        filename << i << ".out";
        //cout << "FILENAME: " << filename.str() << endl;
        f[i].open(filename.str(), fstream::out | fstream::binary);
    }

    //endregion

    j = 0;
    L = 0;

    //region The initial distribution of the segments.

    while (!f0.eof())
    {
        Node nodeRead {};
        f0.read((char*)&nodeRead, 200);
        if(nodeRead.key == 0)
        {
            break;
        }

        //cout << "FILE_" << j % N << ": " << nodeRead.key << endl;
        f[j % N].write((char*)&nodeRead, sizeof(Node));

        j++;
        L++;
    }

    //endregion

    CloseAllFiles(f, N);

    //region Initial initialization of the index card.

    for (int i = 0; i < 2 * N; ++i)
    {
        t[i] = i;
    }

    //endregion

    //region Merge from f[t[1]].. f[t[N]] to f[t[N+1]].. f[t[2N]].

    while(L != 1)
    {
        af = (L >= N) ? N : L;

        //region Open files for reading.

        for (int i = 0; i < af; ++i)
        {
            ostringstream filename;
            filename << t[i] << ".out";

            f[t[i]].clear();
            f[t[i]].close();

            f[t[i]].open(filename.str(), fstream::in | fstream::binary);
            f[t[i]].seekg(0, ios::beg);
        }

        //endregion

        //region Open files for writing.

        for (int i = N; i < 2 * N; ++i)
        {
            ostringstream filename;
            filename << t[i] << ".out";

            f[t[i]].clear();
            f[t[i]].close();

            f[t[i]].open(filename.str(), fstream::out | fstream::binary);
            f[t[i]].seekp(0, ios::beg);
        }

        //endregion

        L = 0;
        j = N;

        vector<int> not_af;

        //region Passage.

        while(af != 0)
        {
            L++;
            ao = af;

            //region Initialization ta[1].. ta[af] with indexes from t[].

            int offset = 0;
            bool isConsists;

            for (int i = 0; i < N; ++i)
            {
                if(not_af.empty())
                {
                    ta[i] = t[i];
                    continue;
                }
                isConsists = false;

                for (int k = 0; k < not_af.size(); ++k)
                {
                    if(t[i] == not_af[k])
                    {
                        offset++;
                        isConsists = true;
                        continue;
                    }
                }
                if(!isConsists)
                {
                    ta[i - offset] = t[i];
                }
            }

            //endregion

            //region Merging the first active segments into f[t[j]].

            while(ao != 0)
            {
                //region Index of the file with the minimum key.

                int minKey = MAX_KEYS + 5;
                for (int i = 0; i < ao; ++i)
                {
                    fpos<mbstate_t> pos = f[ta[i]].tellg();
                    //cout << ta[i] << "_POS: " << pos << endl;

                    Node nodeMin{};
                    f[ta[i]].read((char*)&nodeMin, sizeof(Node));

                    minKey = (nodeMin.key < minKey) ? nodeMin.key : minKey;
                    m = (nodeMin.key <= minKey) ? i : m;

                    f[ta[i]].seekg(pos);
                }

                //endregion

                Node nodeCopy{};
                f[ta[m]].read((char*)&nodeCopy, sizeof(Node));
                f[t[j]].write((char*)&nodeCopy, sizeof(Node));

                Node nodeNext{};
                fpos<mbstate_t> pos = f[ta[m]].tellg();
                f[ta[m]].read((char*)&nodeNext, sizeof(Node));
                f[ta[m]].seekg(pos);
                if(nodeNext.key == 0)
                {
                    not_af.push_back(ta[m]);
                    for (int i = m; i < af; ++i)
                    {
                        ta[i] = ta[i + 1];
                    }
                    af--;
                    ao--;
                }
                else
                {
                    if(nodeNext.key < nodeCopy.key)
                    {
                        for (int i = m; i < ao; ++i)
                        {
                            ta[i] = ta[i + 1];
                        }
                        ao--;
                    }
                }
            }
            j++;
            if(j == 2 * N)
            {
                j = N;
            }

            //endregion
        }

        //endregion

        _LCount++;

        //region Switch index card.

        int tmp[2 * N];
        for (int i = 0; i < 2 * N; ++i)
        {
            tmp[i] = t[i];
        }
        for (int i = 0, k = N; i < 2 * N; ++i, k++)
        {
            t[i] = tmp[k % (2 * N)];
        }

        //endregion

    }

    //endregion

    //region Sorted sequence in f[t[0]].

//    ostringstream filenameRes;
//    filenameRes << t[0] << ".out";
//    f[t[0]].clear();
//    f[t[0]].close();
//    f[t[0]].open(filenameRes.str(), fstream::in | fstream::binary);
//    f[t[0]].seekg(0, ios::beg);
//    cout << "RESULT" << endl;
//    int i = 0;
//    while(!f[t[0]].eof())
//    {
//        Node read{};
//        f[t[0]].read((char*)&read, 200);
//        if(read.key == 0)
//        {
//            break;
//        }
//
//        cout << i << ": " << read.key << endl;
//        i++;
//    }

    //endregion

    CloseAllFiles(f, N);
}

int main()
{
    srand(time(nullptr));

    //CreateSourceFile();

    //int N = 4;


//    fstream fin;
//    fin.open("source.out", ios::binary | ios::in);
//
//    int i = 0;
//    while(!fin.eof())
//    {
//        Node read{};
//        fin.read((char*)&read, 200);
//        if(read.key == 0)
//        {
//            break;
//        }
//        //cout << i << ": " << read.key << endl;
//        i++;
//    }
//
//    fin.seekg(0);

    ofstream fileResult;
    fileResult.open("result.csv");

    fileResult << "Ways,Passes,Time" << endl;
    for (int i = 2; i < 11; ++i)
    {
        _LCount = 0;
        clock_t start = clock();

        BMerge(i);

        clock_t end = clock();
        double seconds = (double)(end - start) / CLOCKS_PER_SEC;

        fileResult << i << "," << _LCount << "," << seconds << endl;
    }

    fileResult.close();

    return 0;
}