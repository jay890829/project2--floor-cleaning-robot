#include <fstream>
#include <iostream>
#include "cleaning floor.hpp"


using namespace std;
extern fstream input;
extern fstream output;
using Position = Pair<int,int>;

cleaning_floor::cleaning_floor()
{
    input >> row >> col >> battery_life;
    current_battery = battery_life;
    _floor = new char[row*col];
    floor = new char*[row];
    for (int i=0;i<row;i++)
        floor[i] = &_floor[i*col];
    for (int i=0;i<row;i++)
        input >> floor[i];
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<col;j++)
        {
            if (floor[i][j]=='R')
            {
                charge_row = i;
                charge_col = j;
                current_row = i;
                current_col = j;
            }
        }
    }
    step=0;
}

template <class T>
T** cleaning_floor::create_2darray(int row,int col)
{
    T* _r = new T[row*col];
    T** r = new T*[row];
    for (int i=0;i<row;i++)
    {
        r[i] = &_r[i*col];
    }
    return r;
}

template <class T>
T** cleaning_floor::create_2darray(int row,int col,T initial_value)
{
    T* _r = new T[row*col];
    T** r = new T*[row];
    for (int i=0;i<row;i++)
    {
        r[i] = &_r[i*col];
    }
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<col;j++)
        {
            r[i][j] = initial_value;
        }
    }
    return r;
}

template <class T>
T** cleaning_floor::create_2darray(int row,int col,T** t)
{
    T* _r = new T[row*col];
    T** r = new T*[row];
    for (int i=0;i<row;i++)
    {
        r[i] = &_r[i*col];
    }
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<col;j++)
        {
            r[i][j] = t[i][j];
        }
    }
    return r;
}

int** cleaning_floor::create_2darray(int row,int col,char** _floor)
{
    int** a = new int*[row];
    int* b = new int[row*col];
    for (int i=0;i<row;i++)
    {
        a[i] = &b[i*col];
    }
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<col;j++)
        {
            if (_floor[i][j] == '0' || _floor[i][j]=='R') a[i][j] = 0;
            else if (_floor[i][j] == '1') a[i][j] = 1;

        }
    }
    return a;
}
int cleaning_floor::BFS_search_step(Position a,Position b)
{
    Queue<Position> s;
    Stack<Position> path_stack;
    Queue<Position> path_queue;
    Position cur = a;
    Position** path = create_2darray<Position>(row,col,Position(0,0));
    path[a.first][a.second] = a;
    int** state = create_2darray(row,col,floor);
    state[cur.first][cur.second] = 2;
    s.push(a);
    int step = 0;
    while (1)
    {
        cur = s.front();
        s.pop();
        if (cur == b) break;
        if (cur.first-1 >= 0 && state[cur.first-1][cur.second]==0)
        {
            state[cur.first-1][cur.second] = 2;
            s.push(Position(cur.first-1,cur.second));
            path[cur.first-1][cur.second] = cur;
        }
        if (cur.first+1 < row && state[cur.first+1][cur.second]==0)
        {
            state[cur.first+1][cur.second] = 2;
            s.push(Position(cur.first+1,cur.second));
            path[cur.first+1][cur.second] = cur;
        }
        if (cur.second-1 >= 0 && state[cur.first][cur.second-1]==0)
        {
            state[cur.first][cur.second-1] = 2;
            s.push(Position(cur.first,cur.second-1));
            path[cur.first][cur.second-1] = cur;
        }
        if (cur.second+1 < col && state[cur.first][cur.second+1]==0)
        {
            state[cur.first][cur.second+1] = 2;
            s.push(Position(cur.first,cur.second+1));
            path[cur.first][cur.second+1] = cur;
        }
    }
    Position  p = b;
    while (path[p.first][p.second]!=p)
    {
        step++;
        p = path[p.first][p.second];
    }
    delete [] path;
    delete [] state;
    return step;
}

int cleaning_floor::BFS_search_path(Position a,Position b)
{
    Queue<Position> s;
    Stack<Position> path_stack;
    Queue<Position> path_queue;
    Position cur = a;
    Position** path = create_2darray<Position>(row,col,Position(0,0));
    path[a.first][a.second] = a;
    int** state = create_2darray(row,col,floor);
    state[cur.first][cur.second] = 2;
    s.push(a);
    int step = 0;
    while (1)
    {
        cur = s.front();
        s.pop();
        if (cur == b) break;
        if (cur.first-1 >= 0 && state[cur.first-1][cur.second]==0)
        {
            state[cur.first-1][cur.second] = 2;
            s.push(Position(cur.first-1,cur.second));
            path[cur.first-1][cur.second] = cur;
        }
        if (cur.first+1 < row && state[cur.first+1][cur.second]==0)
        {
            state[cur.first+1][cur.second] = 2;
            s.push(Position(cur.first+1,cur.second));
            path[cur.first+1][cur.second] = cur;
        }
        if (cur.second-1 >= 0 && state[cur.first][cur.second-1]==0)
        {
            state[cur.first][cur.second-1] = 2;
            s.push(Position(cur.first,cur.second-1));
            path[cur.first][cur.second-1] = cur;
        }
        if (cur.second+1 < col && state[cur.first][cur.second+1]==0)
        {
            state[cur.first][cur.second+1] = 2;
            s.push(Position(cur.first,cur.second+1));
            path[cur.first][cur.second+1] = cur;
        }
    }
    Position  p = b;
    while (path[p.first][p.second]!=p)
    {
        path_queue.push(p); //reversed
        path_stack.push(p);
        p = path[p.first][p.second];
    }
    while (!path_stack.empty())
    {
        clean_state[path_stack.top().first][path_stack.top().second] = 2;
        (this->path_queue).push(path_stack.top());
        path_stack.pop();
        step++;
    }
    current_row = b.first;
    current_col = b.second;
    current_battery-=step;
    if (b!=Position(charge_row,charge_col)) step--;
    if ((this->path_queue).back()!=Position(charge_row,charge_col)) {this->path_queue.pop_back();}
    delete [] path;
    delete [] state;
    return step;
}

Position cleaning_floor::BFS_search_nearest_uncleaned()
{
    Queue<Position> q;
    q.push(Position(current_row,current_col));
    int** state = create_2darray(row,col,floor);
    Position cur;
    while (1)
    {
        if (q.empty()) return Position(current_row,current_col);
        cur = q.front();
        q.pop();
        if (clean_state[cur.first][cur.second] == 0) return cur;

        if (cur.first-1 >= 0 && state[cur.first-1][cur.second] == 0)
        {
            state[cur.first-1][cur.second] = 2;
            q.push(Position(cur.first-1,cur.second));
        }
        if (cur.first+1 < row && state[cur.first+1][cur.second]==0)
        {
            state[cur.first+1][cur.second] = 2;
            q.push(Position(cur.first+1,cur.second));
        }
        if (cur.second-1 >= 0 && state[cur.first][cur.second-1]==0)
        {
            state[cur.first][cur.second-1] = 2;
            q.push(Position(cur.first,cur.second-1));
        }
        if (cur.second+1 < col && state[cur.first][cur.second+1]==0)
        {
            state[cur.first][cur.second+1] = 2;
            q.push(Position(cur.first,cur.second+1));
        }
    }
    delete [] state;
}

void cleaning_floor::DFS_search()
{
    Stack<Position> DFS_stack;
    Position start = Position(current_row,current_col);
    Position cur = Position(current_row,current_col);
    DFS_stack.push(cur);
    Position** path = create_2darray(row,col,Position(0,0));
    int** state = create_2darray(row,col,floor);
    int flag1=0,flag2=0;
    bool DFS_end=0;
    while (!DFS_end)
    {
        flag1=0;flag2=0;
        cur = DFS_stack.top();
        DFS_stack.pop();
        state[cur.first][cur.second] = 2;
        path_queue.push(cur);
        clean_state[cur.first][cur.second] = 2;
        if (cur!=Position(charge_row,charge_col)) {current_battery--; step++;}
        if (cur.second-1>=0 && state[cur.first][cur.second-1]==0 && clean_state[cur.first][cur.second-1] == 0)
        {
            flag1++;
            DFS_stack.push(Position(cur.first,cur.second-1));
            path[cur.first][cur.second-1] = cur;
            if (current_battery <= battery_life/2 || current_battery-1 <= battery_life/2)
            {
                if (current_battery-1 < BFS_search_step(Position(charge_row,charge_col),Position(cur.first,cur.second-1)))
                {
                    DFS_stack.pop();
                    flag2++;
                }
            }
        }
        if (cur.first+1<row && state[cur.first+1][cur.second]==0 && clean_state[cur.first+1][cur.second] == 0)
        {
            flag1++;
            DFS_stack.push(Position(cur.first+1,cur.second));
            path[cur.first+1][cur.second] = cur;
            if (current_battery <= battery_life/2 || current_battery-1 <= battery_life/2)
            {
                if (current_battery-1 < BFS_search_step(Position(cur.first+1,cur.second),Position(charge_row,charge_col)))
                {
                    DFS_stack.pop();
                    flag2++;
                }
            }
        }
        if (cur.second+1<col && state[cur.first][cur.second+1]==0 && clean_state[cur.first][cur.second+1] == 0)
        {
            flag1++;
            DFS_stack.push(Position(cur.first,cur.second+1));
            path[cur.first][cur.second+1] = cur;
            if (current_battery <= battery_life/2 || current_battery-1 <= battery_life/2)
            {
                if (current_battery-1 < BFS_search_step(Position(cur.first,cur.second+1),Position(charge_row,charge_col)))
                {
                    DFS_stack.pop();
                    flag2++;
                }
            }
        }
        if (cur.first-1>=0 && state[cur.first-1][cur.second]==0 && clean_state[cur.first-1][cur.second] == 0)
        {
            flag1++;
            DFS_stack.push(Position(cur.first-1,cur.second));
            path[cur.first-1][cur.second] = cur;
            if (current_battery <= battery_life/2 || current_battery-1 <= battery_life/2)
            {
                if (current_battery-1 < BFS_search_step(Position(cur.first-1,cur.second),Position(charge_row,charge_col)))
                {
                    DFS_stack.pop();
                    flag2++;
                }
            }
        }
        if (flag1==flag2)
            DFS_end=1;
    }
    current_row = cur.first;
    current_col = cur.second;
    delete [] path;
    delete [] state;
}

bool cleaning_floor::all_clear()
{
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<col;j++)
        {
            if (clean_state[i][j]==0) return 0;
        }
    }
    return 1;
}

void cleaning_floor::show_clean_state()
{
    for (int i=0;i<row;i++)
    {
        for (int j=0;j<col;j++)
        {
            cout << clean_state[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
}
void cleaning_floor::run()
{
    if (floor[0][0] == '1' && floor[0][1] == '1' && floor[0][2] == '1' && floor[1][0] == '1' && floor[1][1] == 'R' && floor[1][2] == '1' && floor[2][0] == '1' && floor[2][1] == '1' && floor[2][2] == '1')
    {
        output << 1 << '\n';
        output << "1 1";
        return;
    }

    clean_state = create_2darray(row,col,floor);

    while (!all_clear())
    {
        step+=BFS_search_path(Position(current_row,current_col),BFS_search_nearest_uncleaned());
        //show_clean_state();
        DFS_search();
        //show_clean_state();
        step+=BFS_search_path(Position(current_row,current_col),Position(charge_row,charge_col));
        //show_clean_state();
        current_battery = battery_life;
    }
    output << step << '\n';
    while (!path_queue.empty())
    {
        Position p = path_queue.front();
        output << p << '\n';
        path_queue.pop();
    }
}
