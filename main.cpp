#pragma once
#include <iostream>
#include <fstream>
#include "cleaning floor.hpp"
using namespace std;
fstream input;
fstream output;
int main()
{
    int row,column;
    input.open("floor.data",ios::in);
    output.open("final.path",ios::out);
    cleaning_floor c;
    c.run();
    return 0;
}



