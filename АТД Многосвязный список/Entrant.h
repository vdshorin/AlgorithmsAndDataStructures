#ifndef ALGORITHMS_LAB2_ENTRANT_H
#define ALGORITHMS_LAB2_ENTRANT_H

#include <string>
#include <iostream>

using namespace std;

class Entrant {
private:
    string _secondName;
    int _firstMark;
    int _secondMark;
    int _thirdMark;
    bool _isPerfectDiplom;
    string _city;
    bool _isHostel;
public:
    Entrant(){}

    Entrant(string secondName, int firstMark, int secondMark, int thirdMark,
                     bool isPerfectDiplom, string city, bool isHostel)
    {
        _secondName = secondName;
        _firstMark = firstMark;
        _secondMark = secondMark;
        _thirdMark = thirdMark;
        _isPerfectDiplom = isPerfectDiplom;
        _city = city;
        _isHostel = isHostel;
    }

    string GetSecondName()
    {
        return _secondName;
    }

    int GetFirstMark()
    {
        return _firstMark;
    }
    int GetSecondMark()
    {
        return _secondMark;
    }
    int GetThirdMark()
    {
        return _thirdMark;
    }
    bool IsPerfectDiplom()
    {
        return _isPerfectDiplom;
    }
    string GetCity()
    {
        return _city;
    }
    bool  IsHostel()
    {
        return _isHostel;
    }

    void Print()
    {
        cout << "Second name:" << _secondName << endl;
        cout << "First mark:" << _firstMark << endl;
        cout << "Second mark:" << _secondMark << endl;
        cout << "Third mark:" << _thirdMark << endl;
        if(IsPerfectDiplom())
        {
            cout << "Diplom is perfect" << endl;
        }
        else
        {
            cout << "Diplom is not perfect" << endl;
        }
        cout << "City:" << _city << endl;
        if(_isHostel)
        {
            cout << "Need a hostel" << endl << endl;
        }
        else
        {
            cout << "Dont need a hostel" << endl << endl;
        }
    }

    ~Entrant() {}
};


#endif //ALGORITHMS_LAB2_ENTRANT_H
