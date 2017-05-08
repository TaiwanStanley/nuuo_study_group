#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

inline int GetOneLineToInt(istream& cin)
{
    string value;
    getline(cin, value);
    return stoi(value);
}

int main()
{
    int cases = GetOneLineToInt(cin);
    int caseIndex = 0;
    while (cases--)
    {
        caseIndex++;
        int wallLines = GetOneLineToInt(cin);

        string str;
        getline(cin, str);
        istringstream iss(str);
        int currentlyWall = 0, highJumps = 0, lowJumps = 0;
        for (int i = 0; i < wallLines; i++)
        {
            getline(iss, str, ' ');

            if (i == 0)
            {
                currentlyWall = stoi(str);
            }
            else
            {
                int nextWall = stoi(str);
                if (nextWall > currentlyWall)
                {
                    highJumps++;
                }
                else if (nextWall < currentlyWall)
                {
                    lowJumps++;
                }
                currentlyWall = nextWall;
            }
        }
        cout << "Case " << caseIndex << ": " << highJumps << " " << lowJumps << endl;
    }

    system("pause");
}