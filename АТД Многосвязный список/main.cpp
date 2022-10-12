#include <iostream>
#include <string>
#include "Entrant.h"
#include "MultyList.h"

using namespace std;

bool* IsCriterias(bool *criterias, Entrant entrant)
{
    criterias[0] = false;
    criterias[1] = entrant.GetFirstMark() == 5
                   && entrant.GetSecondMark() == 5
                   && entrant.GetThirdMark() == 5;
    criterias[2] = entrant.IsPerfectDiplom();
    criterias[3] = entrant.GetCity() != "Orel";
    criterias[4] = entrant.IsHostel();

    return criterias;
}

template <class T>
void Add(MultyList<T> &multyList, int criteriaCount)
{
    string secondName;
    int firstMark;
    int secondMark;
    int thirdMark;
    bool isPerfectDiplom;
    string city;
    bool isHostel;
    string boolTmp;

    bool criterias[criteriaCount + 1];
//    cout << "Second name:"; cin >> secondName;
//    cout << "First mark:";  cin >> firstMark;
//    cout << "Second mark:"; cin >> secondMark;
//    cout << "Third mark:";  cin >> thirdMark;
//    cout << "Perfect diplom?(y/n):"; cin >> boolTmp;
//    isPerfectDiplom = boolTmp == "y";
//    //cout << endl << "ISPD: " << isPerfectDiplom << endl << endl;
//    cout << "City:"; cin >> city;
//    cout << "Need hostel?(y/n):"; cin >> boolTmp;
//    isHostel = boolTmp == "y";
//    //cout << endl << "ISHOSTEL: " << isHostel << endl << endl;
//    Entrant entrant(secondName, firstMark, secondMark, thirdMark, isPerfectDiplom, city, isHostel);

    //IsCriterias(criterias ,entrant);
    //multyList.Add(entrant, criterias);

    Entrant entrant("Shorin", 5, 5, 5, true, "Orel", false);
    IsCriterias(criterias ,entrant);
    multyList.Add(entrant, criterias);

    Entrant entrant2("Petrov", 3, 4, 5, true, "Moscow", true);
    IsCriterias(criterias ,entrant2);
    multyList.Add(entrant2, criterias);

    Entrant entrant3("Sidorov", 2, 2, 2, false, "Mcensk", true);
    IsCriterias(criterias ,entrant3);
    multyList.Add(entrant3, criterias);

    Entrant entrant4("Ivanov", 5, 5, 5, false, "Orel", false);
    IsCriterias(criterias ,entrant4);
    multyList.Add(entrant4, criterias);

    Entrant entrant5("Smirnov", 5, 5, 5, false, "Bryansk", true);
    IsCriterias(criterias ,entrant5);
    multyList.Add(entrant5, criterias);
}

template <class T>
void PrintByCriteria(MultyList<T> &multyList)
{
    int userChoice = -1;

    while(true)
    {
        cout << "1 - All marks 5" << endl;
        cout << "2 - Perfect Diplom" << endl;
        cout << "3 - Lives out of Orel" << endl;
        cout << "4 - Need hostel" << endl;
        cout << "0 - Exit" << endl << endl;
        cout << "Your choice:" << endl;
        cin >> userChoice;

        switch (userChoice)
        {
            case 1:
            {
                multyList.PrintByCriteria(1);
                break;
            }
            case 2:
            {
                multyList.PrintByCriteria(2);
                break;
            }
            case 3:
            {
                multyList.PrintByCriteria(3);
                break;
            }
            case 4:
            {
                multyList.PrintByCriteria(4);
                break;
            }
            case 0:
            {
                return;
            }
            default:
            {
                cout << endl << "Undefined operation..." << endl << endl;
                break;
            }
        }
    }
}

template <class T>
void PrintAll(MultyList<T> &multyList)
{
    multyList.PrintAll();
}

template <class T>
void Delete(MultyList<T> &multyList)
{
    string secondName;

    cout << "Enter second name:";
    cin >> secondName;

    multyList.Delete(secondName);
}

template <class T>
void DeleteAll(MultyList<T> &multyList)
{
    multyList.DeleteAll();
}

int main() {

    int _userChoice = -1;
    int _criteriaCount = 4;

    MultyList<Entrant> _multyList = MultyList<Entrant>(_criteriaCount);

    while (true)
    {
        cout << "1 - Add entrant" << endl;
        cout << "2 - Delete entrant" << endl;
        cout << "3 - Delete all" << endl;
        cout << "4 - Show entrants by criteria" << endl;
        cout << "5 - Show all entrants" << endl;
        cout << "0 - Exit" << endl << endl;
        cout << "Your choice:" << endl;
        cin >> _userChoice;

        switch(_userChoice)
        {
            case 1:
            {
                Add(_multyList, _criteriaCount);
                break;
            }
            case 2:
            {
                Delete(_multyList);
                break;
            }
            case 3:
            {

                DeleteAll(_multyList);
                break;
            }
            case 4:
            {
                PrintByCriteria(_multyList);
                break;
            }
            case 5:
            {
                PrintAll(_multyList);
                break;
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                cout << endl << "Undefined operation..." << endl << endl;
                break;
            }
        }
    }
}