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
    CVertex v_tex;
    tie(v_tex.x, v_tex.y) = parallelo.get_fourth_podouble();
    cout << fixed << setprecision(3) << v_tex.x << " " << v_tex.y << endl;
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