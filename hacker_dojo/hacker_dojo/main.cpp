#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

void test_case(vector<string>& minesweeper, const vector<string>& touched_pos)
{
    bool got_mine = false;

    for (size_t rows = 0; rows < minesweeper.size(); rows++)
    {
        for (size_t columns = 0; columns < minesweeper[rows].size(); columns++)
        {
            if (touched_pos[rows][columns] == 'x')
            {
                if (minesweeper[rows][columns] == '*')
                {
                    // bomb
                    got_mine = true;
                }
                else
                {
                    // do mask (3*3)
                    char nighborhood_mines = '0';
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            try
                            {
                                if (minesweeper.at(rows + i).at(columns + j) == '*')
                                {
                                    nighborhood_mines = nighborhood_mines + 1;
                                }
                            }
                            catch (const out_of_range& oor)
                            {
                            }
                        }
                    }
                    minesweeper[rows][columns] = nighborhood_mines;
                }
            }
        }
    }

    if (got_mine == false)
    {
        for (auto v : minesweeper)
        {
            std::replace(v.begin(), v.end(), '*', '.'); // replace all 'x' to 'y'
        }
    }
}

void output(vector<string>& minesweeper, size_t testcase)
{
    for (auto v : minesweeper)
    {
        cout << v << endl;
    }

    if (testcase > 0)
    {
        cout << endl;
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

        output(minesweeper, testcase);
    }

    return 0;
}