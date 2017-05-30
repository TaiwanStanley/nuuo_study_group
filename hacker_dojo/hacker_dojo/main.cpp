#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include "StandardNumberCompiler.h"
#include "TelephoneNumberForm.h"
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
        CTelephoneNumberForm teleform;

        cin.ignore(100000, '\n');
        int telephone_number_list = GetOneLineToInt();

        for (int i = 0; i < telephone_number_list; i++)
        {
            string memorable_telephone_number;
            getline(cin, memorable_telephone_number);
            teleform.ToStandardForm(memorable_telephone_number);
        }

        teleform.PrintDuplicatesStandardFormNumber();
        teleform.HasDuplicatesNum();

        if (datasets != 0)
        {
            cout << endl;
        }
    }

    return 0;
}
