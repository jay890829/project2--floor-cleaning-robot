#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    T* _begin;
    T* _end;
    T* _front;
    T* _rear;
    int capacity;
    int size;
public:
    Queue()
    {
        capacity = 10;
        size = 0;
        _begin = new T[10];
        _end = _begin+10;
        _front = _begin;
        _rear = _begin;
    }
    void push(T n)
    {

            if (_front == _rear && size==capacity)
            {
                T* tmp = new T[capacity*2];
                T* index = _front;
                for (int i=0;i<size;i++)
                {
                    tmp[i] = *index;
                    if (index == _end-1) index = _begin;
                    else index++;
                }
                tmp[size] = n;
                delete [] _begin;
                _begin = tmp;
                _end = _begin + 2*capacity;
                _front = _begin;
                _rear = _front + size + 1;
                size++;
                capacity*=2;
            }
            else if (_rear == _end-1)
            {
                *_rear = n;
                _rear = _begin;
                size++;
            }
            else
            {
                *_rear = n;
                _rear = _rear+1;
                size++;
            }

    }
    inline T front()
    {
        return *_front;
    }
    inline bool empty()
    {
        return size==0;
    }
    void pop()
    {
        if (size==0)
            return;
        else if (_front == _end-1)
            _front = _begin;
        else
            _front++;
        size--;
    }
    void pop_back()
    {
        if (size>0)
        {_rear--;
        size--;}
    }
    T back()
    {
        return _front[size-1];
    }
    int _size()
    {
        return size;
    }
};
