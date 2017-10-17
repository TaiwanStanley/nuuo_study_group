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
public:
    enum MOVING_METHOD
    {
        STEP = 0,
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

    class chess
    {
    public:
        chess(){}
        chess(size_t _x, size_t _y) : m_x(_x), m_y(_y){}
        virtual ~chess(){}

        void set(size_t _x, size_t _y)
        {
            m_x = _x;
            m_y = _y;
        }

        chess& move(chessboard &board, size_t _x, size_t _y)
        {
            m_x = _x;
            m_y = _y;
            board.set_and_check_boundary(m_x, m_y);
            return *this;
        }

        chess& move(chessboard &board, MOVING_METHOD mm, MOVING_DIRECTION md)
        {
            if (m_x >= board.board_width() || m_y >= board.board_length())
            {
                return *this;
            }

            switch (md)
            {
            case chessboard::NORTHWEST:
                go_to_west();
                go_to_north();
                break;
            case chessboard::NORTH:
                go_to_north();
                break;
            case chessboard::NORTHEAST:
                go_to_east();
                go_to_north();
                break;
            case chessboard::EAST:
                go_to_east();
                break;
            case chessboard::SOUTHEAST:
                go_to_east();
                go_to_south();
                break;
            case chessboard::SOUTH:
                go_to_south();
                break;
            case chessboard::SOUTHWEST:
                go_to_west();
                go_to_south();
                break;
            case chessboard::WEST:
                go_to_west();
                break;
            default:
                break;
            }

            if (board.has_chess(m_x, m_y)) return *this;

            board.set_and_check_boundary(m_x, m_y);
            if (mm == MOVING_METHOD::CONTINUE)
            {
                move(board, mm, md);
            }
            return *this;
        }

        size_t go_to_north(size_t step = 1)
        {
            m_y -= step;
            return m_y;
        }

        size_t go_to_south(size_t step = 1)
        {
            m_y += step;
            return m_y;
        }

        size_t go_to_east(size_t step = 1)
        {
            m_x += step;
            return m_x;
        }

        size_t go_to_west(size_t step = 1)
        {
            m_x -= step;
            return m_x;
        }

    private:
        size_t m_x;
        size_t m_y;
    };

public:
    chessboard(const chess_row_set& _row_set, size_t x, size_t y) :
        m_row_set(_row_set),
        m_x_boundary(x),
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
        chess piece;
        for (size_t y = 0; y < m_row_set.size(); y++)
        {
            const string _row = m_row_set.get_row(y);
            for (size_t x = 0; x < _row.size(); x++)
            {
                // P(Pawn, Soldier), N(Knight/Horse), B(Bishop/Elephant), R(Rook/Car), Q(Queen), K(King)
                piece.set(x, y);
                switch (_row.at(x))
                {
                case 'p':
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTHEAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTHWEST).set(x, y);
                    set_and_check_boundary(x, y);
                    break;
                case 'P':
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTHEAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTHWEST).set(x, y);
                    set_and_check_boundary(x, y);
                    break;
                case 'n': case 'N':
                    knight_movement(piece, x, y);
                    set_and_check_boundary(x, y);
                    break;
                case 'b': case 'B':
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTHEAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTHWEST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTHEAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTHWEST).set(x, y);
                    set_and_check_boundary(x, y);
                    break;
                case 'r': case 'R':
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTH).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::EAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTH).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::WEST).set(x, y);
                    set_and_check_boundary(x, y);
                    break;
                case 'q': case 'Q':
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTHEAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTHWEST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTHEAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTHWEST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::NORTH).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::EAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::SOUTH).set(x, y);
                    piece.move(*this, MOVING_METHOD::CONTINUE, MOVING_DIRECTION::WEST).set(x, y);
                    set_and_check_boundary(x, y);
                    break;
                case'k': case 'K':
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTHEAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTHWEST).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTHEAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTHWEST).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::NORTH).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::EAST).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::SOUTH).set(x, y);
                    piece.move(*this, MOVING_METHOD::STEP, MOVING_DIRECTION::WEST).set(x, y);
                    set_and_check_boundary(x, y);
                    break;
                default:
                    break;
                }
            }
        }
    }

    void set_and_check_boundary(size_t x, size_t y)
    {
        try
        {
            m_has_threatening.at(y).at(x) = true;
        }
        catch (const out_of_range oor)
        {
        }
    }

    bool has_chess(size_t x, size_t y) const
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

    size_t board_length() const { return m_y_boundary; }
    size_t board_width() const { return m_x_boundary; }

private:
    void knight_movement(chess &piece, size_t x, size_t y)
    {
        piece.move(*this, piece.go_to_west(), piece.go_to_north(2)).set(x, y);
        piece.move(*this, piece.go_to_west(), piece.go_to_north(2)).set(x, y);
        piece.move(*this, piece.go_to_east(), piece.go_to_north(2)).set(x, y);
        piece.move(*this, piece.go_to_west(2), piece.go_to_north()).set(x, y);
        piece.move(*this, piece.go_to_east(2), piece.go_to_north()).set(x, y);
        piece.move(*this, piece.go_to_west(2), piece.go_to_south()).set(x, y);
        piece.move(*this, piece.go_to_east(2), piece.go_to_south()).set(x, y);
        piece.move(*this, piece.go_to_west(), piece.go_to_south(2)).set(x, y);
        piece.move(*this, piece.go_to_east(), piece.go_to_south(2)).set(x, y);
    }

private:
    const chess_row_set &m_row_set;
    const size_t m_x_boundary;
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
