#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

void testcase(map<char ,int >& table)
{
    string str;
    getline(cin, str);

    for (auto v : str)
    {
        v = toupper(v);
        if (v >= 'A' && v <= 'Z')
        {
            if (table.find(v) != table.end())
            {
                table[v]++;
            }
            else
            {
                table[v] = 1;
            }
        }
    }
}

void output(map<char, int>& table)
{
    vector<pair<char, int> > vcopy(table.begin(), table.end());

    sort(vcopy.begin(), vcopy.end(), [](pair<char, int> a, pair<char, int> b){ return a.second > b.second; });

    for (auto v : vcopy)
    {
        cout << v.first << " " << v.second << endl;
    }
}

int main()
{
    int lines = 0;
    cin >> lines;
    cin.ignore();

    map<char, int> table;

    while (lines--)
    {
        testcase(table);
    }
    
    output(table);

    return 0;
}

