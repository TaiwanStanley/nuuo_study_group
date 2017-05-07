#include <iostream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

inline int GetOneLineToInt(istream& cin)
{
    string value;
    getline(cin, value);
    return stoi(value);
}

int main()
{
    // it is number of tests
    int article = GetOneLineToInt(cin);

    while (article--)
    {
        double iMoney = 0;
        map<unsigned char, double> mMoneyTable;

        // get key lines
        int key_lines = GetOneLineToInt(cin);

        // build key table
        for (int i = 0; i < key_lines; i++)
        {
            mMoneyTable[getchar()] = GetOneLineToInt(cin);
        }

        // get content lines
        int content_lines = GetOneLineToInt(cin);

        // calculate the reward of article
        unsigned char uc;
        while ((uc = getchar()) != EOF)
        {
            switch (uc)
            {
            case '\n':
                content_lines--;
                break;
            case ' ':
                break;
            default:
                iMoney += mMoneyTable[uc];
                break;
            }

            if (content_lines == 0) break;
        }

        // print money how much does the new agency need to pay
        cout << fixed << setprecision(2) << iMoney / 100 << '$' << endl;
    }

    return 0;
}
