#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <stdlib.h> 
#include <algorithm>
using namespace std;

class chessboard
{
    const int EAST = 1;
    const int WEST = -1;
    const int SOUTH = 1;
    const int NORTH = -1;

public:
    class chess_row_set
    {
    public:
        void insert_row(const string &row)
        {
            m_chess_set.push_back(parse_row(row));
        }

        const string &get_row(size_t x) const
        {
            return m_chess_set.at(x);
        }

        size_t size() const
        {
            return m_chess_set.size();
        }

    private:
        string parse_row(const string &row)
        {
            string s_row;
            for (const auto i : row)
            {
                if (isdigit(i))
                {
                    s_row.insert(s_row.end(), atoi(&i), ' ');
                }
                else
                {
                    s_row.push_back(i);
                }
            }
            return s_row;
        }

    private:
        vector<string> m_chess_set;
    };

public:
    chessboard(const chess_row_set& _row_set, size_t x, size_t y) :
        m_row_set(_row_set),
        m_x_bouudary(x),
        m_y_boundary(y),
        m_has_threatening(x, vector<bool>(y, false))
    {
    }

    virtual ~chessboard(){}
    size_t get_number_of_safe_squares()
    {
        cal_the_step();
        size_t safe_squares = 0;
        for (size_t i = 0; i < m_has_threatening.size(); i++)
        {
            safe_squares += count(m_has_threatening.at(i).begin(), m_has_threatening.at(i).end(), false);
        }
        return safe_squares;
    }
    
    void cal_the_step()
    {
        for (size_t i = 0; i < m_row_set.size(); i++)
        {
            const string _row = m_row_set.get_row(i);
            for (size_t j = 0; j < _row.size(); j++)
            {
                // P(Pawn, Soldier), N(Knight/Horse), B(Bishop/Elephant), R(Rook/Car), Q(Queen), K(King)
                try
                {
                    switch (_row.at(j))
                    {
                    case 'p':
                        set_and_check_boundary(i + SOUTH, j + EAST);
                        set_and_check_boundary(i + SOUTH, j + WEST);
                        m_has_threatening.at(i).at(j) = true;
                        break;
                    case 'P':
                        set_and_check_boundary(i + NORTH, j + EAST);
                        set_and_check_boundary(i + NORTH, j + WEST);
                        m_has_threatening.at(i).at(j) = true;
                        break;
                    case 'n': case 'N':
                        knight_movement(i, j);
                        m_has_threatening.at(i).at(j) = true;
                        break;
                    case 'b': case 'B':
                        bishop_movement(i, j);
                        m_has_threatening.at(i).at(j) = true;
                        break;
                    case 'r': case 'R':
                        rook_movement(i, j);
                        m_has_threatening.at(i).at(j) = true;
                        break;
                    case 'q': case 'Q':
                        bishop_movement(i, j);
                        rook_movement(i, j);
                        m_has_threatening.at(i).at(j) = true;
                        break;
                    case'k': case 'K':
                        king_movement(i, j);
                        m_has_threatening.at(i).at(j) = true;
                        break;
                    default:
                        break;
                    }
                }
                catch (const out_of_range oor)
                {
                }
            }
        }
    }

private:
    void knight_movement(size_t i, size_t j)
    {
        set_and_check_boundary(i + NORTH * 2, j + WEST);
        set_and_check_boundary(i + NORTH * 2, j + EAST);
        set_and_check_boundary(i + NORTH, j + WEST * 2);
        set_and_check_boundary(i + NORTH, j + EAST * 2);
        set_and_check_boundary(i + SOUTH, j + WEST * 2);
        set_and_check_boundary(i + SOUTH, j + EAST * 2);
        set_and_check_boundary(i + SOUTH * 2, j + WEST);
        set_and_check_boundary(i + SOUTH * 2, j + EAST);
    }

    void king_movement(size_t i, size_t j)
    {
        set_and_check_boundary(i + NORTH, j + WEST);
        set_and_check_boundary(i + NORTH, j);
        set_and_check_boundary(i + NORTH, j + EAST);
        set_and_check_boundary(i, j + WEST);
        set_and_check_boundary(i, j + EAST);
        set_and_check_boundary(i + SOUTH, j + WEST);
        set_and_check_boundary(i + SOUTH, j);
        set_and_check_boundary(i + SOUTH, j + EAST);
    }
    void rook_movement(size_t i, size_t j)
    {
        // go to east 
        for (size_t p = j + 1; p < m_x_bouudary; p++)
        {
            if (has_chess(i, p))
                break;
            set_and_check_boundary(i, p);
        }

        // go to west 
        for (int p = j - 1; p >= 0; p--)
        {
            if (has_chess(i, p))
                break;
            set_and_check_boundary(i, p);
        }

        // go to south
        for (size_t p = i + 1; p < m_y_boundary; p++)
        {
            if (has_chess(p, j))
                break;
            set_and_check_boundary(p, j);
        }

        // go to north
        for (int p = i - 1; p >= 0; p--)
        {
            if (has_chess(p, j))
                break;
            set_and_check_boundary(p, j);
        }
    }

    void bishop_movement(size_t i, size_t j)
    {
        // go to northeast
        size_t times = 1;
        for (size_t p = j + 1; p < m_x_bouudary; p++)
        {
            if (has_chess(i + times, p))
                break;
            set_and_check_boundary(i + times, p);
            times++;
        }
        // goto southeast
        times = 1;
        for (size_t p = j + 1; p < m_x_bouudary; p++)
        {
            if (has_chess(i - times, p))
                break;
            set_and_check_boundary(i - times, p);
            times++;
        }

        // go to northwest
        times = 1;
        for (int p = j - 1; p >= 0; p--)
        {
            if (has_chess(i + times, p))
                break;
            set_and_check_boundary(i + times, p);
            times++;
        }

        // go to southwest
        times = 1;
        for (int p = j - 1; p >= 0; p--)
        {
            if (has_chess(i - times, p))
                break;
            set_and_check_boundary(i - times, p);
            times++;
        }
    }

    void set_and_check_boundary(size_t x, size_t y)
    {
        try
        {
            m_has_threatening.at(x).at(y) = true;
        }
        catch (const out_of_range oor)
        {
        }
    }

    bool has_chess(size_t x, size_t y)
    {
        try
        {
            return m_row_set.get_row(x).at(y) != ' ';
        }
        catch (const out_of_range oor)
        {
            return false;
        }
    }

private:
    const chess_row_set m_row_set;
    const size_t m_x_bouudary;
    const size_t m_y_boundary;
    vector<vector<bool>> m_has_threatening;
};

void testcases(const string &fen_str)
{
    istringstream iss(fen_str);

    string row;
    chessboard::chess_row_set row_set;
    while (getline(iss, row, '/'))
    {
        row_set.insert_row(row);
    }

    chessboard chess_game(row_set, 8, 8);
    cout << chess_game.get_number_of_safe_squares() << endl;
}

int main()
{
    string fen_str;
    while (getline(cin, fen_str))testcases(fen_str);
    return 0;
}
