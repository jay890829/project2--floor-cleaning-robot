#include "Pair.cpp"
#include "Stack.cpp"
#include "Queue.cpp"
using namespace std;

using Position = Pair<int,int>;

class cleaning_floor
{
private:
    int row,col;
    int current_battery;
    int battery_life;
    int current_row;
    int current_col;
    int charge_row;
    int charge_col;
    int step;
    char* _floor;
    char** floor;
    int** clean_state;
    Queue<Position> path_queue;
public:
    cleaning_floor();
    ~cleaning_floor() = default;
    void run();
    template <class T>
    T** create_2darray(int,int);
    template <class T>
    T** create_2darray(int,int,T);
    template <class T>
    T** create_2darray(int,int,T**);
    int** create_2darray(int,int,char**);
    int BFS_search_step(Position,Position);
    int BFS_search_path(Position,Position);
    Position BFS_search_nearest_uncleaned();
    void DFS_search();
    void _DFS_search(Position);
    bool check_end(Position,int**);
    bool all_clear();
    void show_clean_state();
};
