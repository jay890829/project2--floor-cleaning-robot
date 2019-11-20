#include <iostream>
using namespace std;
template <class A,class B>
class Pair
{
public:
    A first;
    B second;
    Pair() = default;
    Pair(A a,B b):first(a),second(b){}
    Pair(const Pair<A,B>& k):first(k.first),second(k.second){};
    void operator= (const Pair<A,B>& k)
    {
        first = k.first;
        second = k.second;
    }

    bool operator== (const Pair<A,B>& k)
    {
        return (first == k.first) && (second == k.second);
    }
    bool operator!= (const Pair<A,B>& k)
    {
        return !((first == k.first) && (second == k.second));
    }
    ~Pair() = default;
    template <class AA,class BB>
    friend ostream& operator << (ostream& os,Pair<AA,BB> &p);
};

template <class AA,class BB>
inline ostream& operator<< (ostream& os,Pair<AA,BB> &p)
{
    os << p.first << ' ' << p.second;
    return os;
}

