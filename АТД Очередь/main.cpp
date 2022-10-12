#include <iostream>
#include <vector>
#include "SerialQueue.h"
//#include "ConnectedQueue.h"
#include "ELType.h"

using namespace std;

template <typename T>
void AddDetail(Queue<T> &queue)
{
    int time;
    string code;

    if(queue.IsFull())
    {
        cout << "Queue is full!" << endl;
        return;
    }

    cout << "Set detail code: ";
    cin >> code;
    cout << "Set detail model time: ";
    cin >> time;

    ELType<int> detail(time, code);

    queue.Enqueue(detail);
}

template <typename T>
void RemoveFromQueue(Queue<T> &queue)
{
    if(!queue.IsEmpty())
    {
        ELType<int> element = queue.Top();
        cout << "Delete detail with code: " << element.GetDetailCode() << endl;
        queue.Dequeue();
    }
    else
    {
        cout << "Queue is empty" << endl;
    }
}

template <typename T>
void AllProcessingDetails(Queue<T> &queue)
{
    if(queue.IsEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }
    else
    {
        ELType<int> element;
        vector<ELType<int>> bufferQueue;
        int elCount = queue.GetCount();
        //cout << "COUNT: " << elCount << endl;
        for(int i = 0; i < elCount; i++)
        {
            element = queue.Top();
            cout << "|_" << element.GetDetailCode() << "_|" << endl;
            bufferQueue.push_back(element);
            queue.Dequeue();
        }

        for (int i = 0; i < bufferQueue.size(); ++i)
        {
            //cout << "Code_" << i << "_: " << bufferQueue[i].GetDetailCode() << endl;
            queue.Enqueue(bufferQueue[i]);
        }

    }
}

int main() {

    Queue<ELType<int>> _queue = Queue<ELType<int>>();
    const int NO_TIME = -1;
    int _time = NO_TIME;

    int _userChoice;
    while(true)
    {
        cout << "Choose operation: " << endl;
        cout << "1 - Add detail to queue" << endl;
        cout << "2 - Next model time" << endl;
        cout << "3 - Remove from queue" << endl;
        cout << "4 - All processing details" << endl;
        cout << "5 - New queue" << endl;
        cout << "0 - Exit" << endl << endl;

        if(!_queue.IsEmpty())
        {
            cout << "Top element time: " << _time << endl;
        }

        cout << "Your choice: ";
        cin >> _userChoice;

        switch (_userChoice)
        {
            case 1:
            {
                AddDetail(_queue);
                if(_time == NO_TIME)
                {
                    _time = _queue.Top().GetProcessingTime();
                }
                break;
            }
            case 2:
            {
                if(!_queue.IsEmpty())
                {
                    _time--;
                    if(_time == 0)
                    {
                        _queue.Dequeue();
                        if(_queue.IsEmpty())
                        {
                            _time = NO_TIME;
                        }
                        else
                        {
                            _time = _queue.Top().GetProcessingTime();
                        }
                    }
                }
                else
                {
                    cout << "Queue is empty" << endl;	
                }
                break;
            }
            case 3:
            {
                RemoveFromQueue(_queue);
                if(_queue.IsEmpty())
                {
                    _time = NO_TIME;
                }
                else
                {
                    _time = _queue.Top().GetProcessingTime();
                }
                break;
            }
            case 4:
            {
                AllProcessingDetails(_queue);
                break;
            }
            case 5:
            {
                _queue = Queue<ELType<int>>();
                _time = NO_TIME;
                break;
            }
            case 0:
            {
                return 0;
            }
            default:
            {
                cout << endl << "Undefined operation..." << endl;
            }
        }
    }
}