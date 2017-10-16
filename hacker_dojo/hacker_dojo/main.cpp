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
    const int GOTO_EAST = 1;
    const int GOTO_WEST = -1;
    const int GOTO_SOUTH = 1;
    const int GOTO_NORTH = -1;

    enum MOVING_METHOD
    {
        STEP,
        CONTINUE
    };

    enum MOVING_DIRECTION
    {
        NORTHWEST = 0,
        NORTH,
        NORTHEAST,
        EAST,
        SOUTHEAST,
        SOUTH,
        SOUTHWEST,
        WEST
    };
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
        for (size_t y = 0; y < m_row_set.size(); y++)
        {
            const string _row = m_row_set.get_row(y);
            for (size_t x = 0; x < _row.size(); x++)
            {
                // P(Pawn, Soldier), N(Knight/Horse), B(Bishop/Elephant), R(Rook/Car), Q(Queen), K(King)
                try
                {
                    switch (_row.at(x))
                    {
                    case 'p':
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTHEAST);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTHWEST);
                        set_and_check_boundary(y, x);

                        break;
                    case 'P':
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTHEAST);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTHWEST);
                        set_and_check_boundary(y, x);

                        break;
                    case 'n': case 'N':
                        knight_movement(y, x);
                        set_and_check_boundary(y, x);

                        break;
                    case 'b': case 'B':
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTHEAST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTHWEST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTHEAST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTHWEST);
                        set_and_check_boundary(y, x);

                        break;
                    case 'r': case 'R':
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTH);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::EAST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTH);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::WEST);
                        set_and_check_boundary(y, x);

                        break;
                    case 'q': case 'Q':
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTHEAST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTHWEST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTHEAST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTHWEST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTH);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::EAST);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTH);
                        move(x, y, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::WEST);
                        set_and_check_boundary(y, x);

                        break;
                    case'k': case 'K':
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTHEAST);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTHWEST);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTHEAST);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTHWEST);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTH);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::EAST);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTH);
                        move(x, y, MOVING_METHOD::STEP, MOVING_DIRECTION::WEST);
                        set_and_check_boundary(y, x);

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
        set_and_check_boundary(i + GOTO_NORTH * 2, j + GOTO_WEST);
        set_and_check_boundary(i + GOTO_NORTH * 2, j + GOTO_EAST);
        set_and_check_boundary(i + GOTO_NORTH, j + GOTO_WEST * 2);
        set_and_check_boundary(i + GOTO_NORTH, j + GOTO_EAST * 2);
        set_and_check_boundary(i + GOTO_SOUTH, j + GOTO_WEST * 2);
        set_and_check_boundary(i + GOTO_SOUTH, j + GOTO_EAST * 2);
        set_and_check_boundary(i + GOTO_SOUTH * 2, j + GOTO_WEST);
        set_and_check_boundary(i + GOTO_SOUTH * 2, j + GOTO_EAST);
    }

    void set_and_check_boundary(size_t y, size_t x)
    {
        try
        {
            m_has_threatening.at(y).at(x) = true;
        }
        catch (const out_of_range oor)
        {
        }
    }

    void move(size_t x, size_t y, MOVING_METHOD mm, MOVING_DIRECTION md)
    {
        if (x >= m_x_bouudary || y >= m_y_boundary)
        {
            return;
        }

        switch (md)
        {
        case chessboard::NORTHWEST:
            x += GOTO_WEST;
            y += GOTO_NORTH;
            break;
        case chessboard::NORTH:
            y += GOTO_NORTH;
            break;
        case chessboard::NORTHEAST:
            x += GOTO_EAST;
            y += GOTO_NORTH;
            break;
        case chessboard::EAST:
            x += GOTO_EAST;
            break;
        case chessboard::SOUTHEAST:
            x += GOTO_EAST;
            y += GOTO_SOUTH;
            break;
        case chessboard::SOUTH:
            y += GOTO_SOUTH;
            break;
        case chessboard::SOUTHWEST:
            x += GOTO_WEST;
            y += GOTO_SOUTH;
            break;
        case chessboard::WEST:
            x += GOTO_WEST;
            break;
        default:
            break;
        }

        if (has_chess(y, x)) return;

        set_and_check_boundary(y, x);
        if ( mm == MOVING_METHOD::CONTINUE)
        {
            move(x, y, mm, md);
        }
    }

    bool has_chess(size_t y, size_t x)
    {
        try
        {
            return m_row_set.get_row(y).at(x) != ' ';
        }
        catch (const out_of_range oor)
        {
        }
        return false;
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
