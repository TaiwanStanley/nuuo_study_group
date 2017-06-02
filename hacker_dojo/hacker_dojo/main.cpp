#include <iostream>
#include <string>
#include <tuple>
#include <iomanip>
#include "Parallelogram.h"

using namespace std;

void test_case(const string& line)
{
    if (line.empty())
        return;

    CParallelogram parallelo;
    parallelo.split_each_point(line);
    vertex v_tex;
    tie(v_tex.x, v_tex.y) = parallelo.get_fourth_point();
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