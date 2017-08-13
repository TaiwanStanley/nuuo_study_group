#include <iostream>
#include <vector>
#include <string>
using namespace std;

void test_case(vector<string>& minesweeper, const vector<string>& touched_pos)
{

}

void output(const vector<string>& minesweeper)
{
    for (auto v : minesweeper)
    {
        cout << v << endl;
    }
}


int main()
{
    size_t testcase = 0;
    cin >> testcase;
    cin.ignore();

    while (testcase--)
    {
        vector<string> minesweeper, touched_pos;
        size_t lines = 0;
        cin >> lines;
        cin.ignore();
        for (size_t i = 0; i < lines; i++)
        {
            string str;
            getline(cin, str);
            minesweeper.push_back(str);
        }
        
        for (size_t i = 0; i < lines; i++)
        {
            string str;
            getline(cin, str);
            touched_pos.push_back(str);
        }

        test_case(minesweeper, touched_pos);

        output(minesweeper);
    }


    system("pause");
    return 0;
}