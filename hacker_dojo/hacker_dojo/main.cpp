#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

string testcase(const string& str)
{
    string ret;
    int previous = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        switch (str[i])
        {
        case 'B': case 'F': case 'P': case 'V':
            if (previous != 1)
                ret.append("1");
            previous = 1;
            break;
        case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z':
            if (previous != 2)
                ret.append("2");
            previous = 2;
            break;
        case 'D': case 'T':
            if (previous != 3)
                ret.append("3");
            previous = 3;
            break;
        case 'L':
            if (previous != 4)
                ret.append("4");
            previous = 4;
            break;
        case 'M': case 'N':
            if (previous != 5)
                ret.append("5");
            previous = 5;
            break;
        case 'R':
            if (previous != 6)
                ret.append("6");
            previous = 6;
            break;
        default:
            previous = 0;
            break;
        }
    }
    return ret;
}


int main()
{
    string str;
    while (getline(cin, str))
    {
        cout << testcase(str) << endl;
    }
    return 0;
}