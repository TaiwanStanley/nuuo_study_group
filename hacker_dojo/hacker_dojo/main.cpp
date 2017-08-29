#include <iostream>
#include <sstream>
using namespace std;

void OutputValueTimes(int i, ostringstream& oss)
{
    for (int j = 1; j <= i; j++)
    {
        oss << to_string(i);
    }
    oss << "\n";
}

void testcase(const pair<int, int >& triangle_wave, int testcases)
{
    ostringstream oss;
    for (int i = 1; i < triangle_wave.first; i++)
    {
        OutputValueTimes(i, oss);
   }

    for (int i = triangle_wave.first; i >= 1; i--)
    {
        OutputValueTimes(i, oss);
    }

    for (int i = 0; i < triangle_wave.second; i++)
    {
        cout << oss.str();

        // Don't print out the last one with end line.
        if ( (i != triangle_wave.second -1) || testcases != 0)
        {
            cout << endl;
        }
    }
}

int main()
{
    int testcases = 0;
    
    cin >> testcases;
    cin.ignore();
    
    while (testcases--)
    {
        int _amplitude = 0, _frequency = 0;
        cin >> _amplitude;
        cin >> _frequency;
        testcase(make_pair(_amplitude, _frequency), testcases);
    }

    return 0;
}