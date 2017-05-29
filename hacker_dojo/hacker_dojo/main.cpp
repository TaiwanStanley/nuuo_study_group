#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include "StandardNumberCompiler.h"
using namespace std;

inline int GetOneLineToInt()
{
    string value;
    getline(cin, value);
    return stoi(value);
}

int main(void)
{
    int datasets = GetOneLineToInt();
    while (datasets--)
    {
        cin.ignore(100000, '\n');
        int telephone_number_list = GetOneLineToInt();
        map<string, unsigned int> result_map;
        bool has_duplicates = false;

        for (int i = 0; i < telephone_number_list; i++)
        {
            string memorable_telephone_number;
            getline(cin, memorable_telephone_number);

            string stardard_telphone_number = CStandardNumberCompiler::ToStandardForm(memorable_telephone_number);
            map<string, unsigned int>::iterator it = result_map.find(stardard_telphone_number);
            if (it != result_map.end())
            {
                it->second++;
                has_duplicates = true;
            }
            else
            {
                result_map[stardard_telphone_number] = 1;
            }
        }
        map<string, unsigned int>::iterator it = result_map.begin();
        for (; it != result_map.end(); it++)
        {
            if (it->second > 1)
            {
                cout << it->first << " " << it->second << endl;
            }
        }
        if (!has_duplicates)
        {
            cout << "No duplicates." << endl;
        }

        if (datasets != 0)
        {
            cout << endl;
        }
    }

    return 0;
}
