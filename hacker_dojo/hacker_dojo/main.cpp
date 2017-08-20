#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

class mine_sweeper
{
public:
    mine_sweeper(const vector<string>& grid)
        : m_got_mine(false), m_grid(grid)
    {}

    void stamp(size_t x, size_t y, const char c)
    {
        if (c == 'x')
        {
            if (m_grid[x][y] == '*')
            {
                // bomb
                m_got_mine = true;
            }
            else
            {
                // do mask (3*3)
                do_mask(x, y);
            }
        }
    }

    const vector<string>& result()
    {
        if (m_got_mine == false)
        {
            for (auto &v : m_grid)
            {
                std::replace(v.begin(), v.end(), '*', '.');
            }
        }
        return m_grid;
    }

private:
    void do_mask(size_t x, size_t y)
    {
        char nighborhood_mines = '0';
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                try
                {
                    if (m_grid.at(x + i).at(y + j) == '*')
                    {
                        nighborhood_mines = nighborhood_mines + 1;
                    }
                }
                catch (const out_of_range& oor)
                {
                }
            }
        }
        m_grid[x][y] = nighborhood_mines;
    }

private:
    bool m_got_mine;
    vector<string> m_grid;
};

void test_case(mine_sweeper &sweeper, const vector<string>& touched_pos)
{
    for (size_t rows = 0; rows < touched_pos.size(); rows++)
    {
        for (size_t columns = 0; columns < touched_pos[rows].size(); columns++)
        {
            sweeper.stamp(rows, columns, touched_pos[rows][columns]);
        }
    }
}

void output(const vector<string>& minesweeper, size_t testcase)
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

        mine_sweeper game(minesweeper);

        for (size_t i = 0; i < lines; i++)
        {
            string str;
            getline(cin, str);
            touched_pos.push_back(str);
        }

        test_case(game, touched_pos);

        output(game.result(), testcase);
    }

    return 0;
}