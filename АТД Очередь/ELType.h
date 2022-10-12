#ifndef ALGORITMS_LAB1_ELTYPE_H
#define ALGORITMS_LAB1_ELTYPE_H

#include <string>

using namespace std;

template <typename T>
class ELType {
private:
    string _detailCode;
    int _processingTime;
public:
    ELType(){};
    ELType(int time, string code)
    {
        _processingTime = time;
        _detailCode = code;
    }

    string GetDetailCode()
    {
        return _detailCode;
    }

    int GetProcessingTime()
    {
        return _processingTime;
    }

    ~ELType() {}
};
#endif //ALGORITMS_LAB1_ELTYPE_H