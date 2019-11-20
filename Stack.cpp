#include <iostream>

using namespace std;

template <class T>
class Stack
{
private:
    T* v;
    int _size;
    int capacity;
public:
    Stack()
    {
        v = new T[10];
        _size = 0;
        capacity = 10;
    }
    Stack(const Stack<T> &s)
    {
        v = s.v;
        _size = s._size;
        capacity = s.capacity;
    }
    ~Stack()
    {
        delete [] v;
    }
    void push(const T& n)
    {
        if (_size == capacity)
        {
            T* tmp = new T[capacity*2];
            for (int i=0;i<_size;i++)
                tmp[i] = v[i];
            tmp[_size++] = n;
            delete [] v;
            v = tmp;
            capacity *= 2;
        }
        else v[_size++] = n;
    }

    void pop()
    {
        if (_size>0)
        {
            _size--;
        }
    }
    inline bool empty()
    {
        return _size==0;
    }
    inline T top()
    {
        return v[_size-1];
    }

    int size()
    {
        return _size;
    }
};


