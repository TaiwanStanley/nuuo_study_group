#include <iostream>
#include <string>
#include <tuple>
#include <iomanip>
#include "Parallelogram.h"

using namespace std;

void test_case(const string& line)
{
    CParallelogram parallelo;
    parallelo.split_each_podoubles(line);
    CVertex Vtex;
    tie(Vtex.x, Vtex.y) = parallelo.get_fourth_podouble();
    cout << fixed << setprecision(3) << Vtex.x << " " << Vtex.y << endl;
}

int main(void)
{
    string line;
    while (getline(cin, line))
    {
        test_case(line);
    }
    return 0;
}