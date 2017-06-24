#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
class CPoint
{

public:
    CPoint() :x(0), y(0){}
    CPoint(const T& _x, const T& _y) :x(_x), y(_y){ }

    bool operator==(const CPoint<T>& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }

    void operator=(const CPoint<T>& rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }

    bool operator>(const CPoint<T>& rhs)
    {
        return x > rhs.x || y > rhs.y;
    }

    friend istream &operator >>(istream &is, CPoint<T>& point)
    {
        is >> point.x >> point.y;
        return is;
    }

    friend ostream &operator <<(ostream &os, const CPoint<T>& _point)
    {
        os << _point.x << " " << _point.y;
        return os;
    }

public:
    T x, y;
};

using SPoint = CPoint<unsigned int>;
         
class COrientablePoint
{
    enum DIRECTION
    {
        NORTH = 0,
        EAST,
        SOUTH,
        WEST
    };

public:
    COrientablePoint(SPoint _point, unsigned char ch) :
        m_position(_point), 
        m_direction_word({{ NORTH, 'N' }, { EAST, 'E' }, { SOUTH, 'S' }, { WEST, 'W' }}),
        m_direction_size(sizeof(DIRECTION))
    {
        set_direction(ch);
    }     

    void set_direction(unsigned char ch)
    {
        switch (ch)
        {
        case 'N':
            m_direction = NORTH;
            break;
        case 'E':
            m_direction = EAST;
            break;
        case 'S':
            m_direction = SOUTH;
            break;
        case 'W':
            m_direction = WEST;
            break;
        default:
            break;
        }
    }

    SPoint get_position() const
    {
        return m_position;
    }

    void set_position(const SPoint& pos)
    {
        m_position = pos;
    }

    void turn_right()
    {
        m_direction = (DIRECTION)((m_direction + m_direction_size + 1) % m_direction_size);
    }

    void turn_left()
    {
        m_direction = (DIRECTION)((m_direction + m_direction_size - 1) % m_direction_size);
    }

    void forward()
    {
        switch (m_direction)
        {
        case NORTH:
            m_position.y++;
            break;
        case EAST:
            m_position.x++;
            break;
        case SOUTH:
            m_position.y--;
            break;
        case WEST:
            m_position.x--;
            break;
        default:
            break;
        }
    }

    unsigned char get_direction_char()
    {
        return m_direction_word[m_direction];
    }

private:
    SPoint m_position;
    DIRECTION m_direction;
    map<DIRECTION, unsigned char> m_direction_word;
    unsigned int m_direction_size;
};

class CRobot
{
public:
    CRobot(const SPoint& _point, const char orientation) :
        m_instructions(""), m_lost(false), m_orientable_point(_point, orientation){}

    void insert_instructions(const string& ins)
    {
        m_instructions = ins;
    }

    string get_instructions() const
    {
        return m_instructions;
    }

    void set_position(const SPoint& pos)
    {
        m_orientable_point.set_position(pos);
    }

    SPoint get_position() const
    {
        return m_orientable_point.get_position();
    }

    unsigned char get_orientation()
    {
        return m_orientable_point.get_direction_char();
    }

    void excute_instruction(const char ch)
    {
        switch (ch)
        {
        case 'F':
            m_orientable_point.forward();
            break;
        case 'R':
            m_orientable_point.turn_right();
            break;
        case 'L':
            m_orientable_point.turn_left();
            break;
        default:
            break;
        }
    }

    void set_lost(bool b)
    {
        m_lost = b;
    }

    bool get_lost() const
    {
        return m_lost;
    }

private:
    string m_instructions;
    bool m_lost;
    COrientablePoint m_orientable_point;
};


class CGrid
{
public:
    CGrid(const SPoint& point) :m_boundary(point) {}

    void put_selfwalking_robot(CRobot& robot)
    {
        string instructions = robot.get_instructions();
        for (size_t i = 0; i < instructions.length(); i++)
        {
            SPoint previousPoint = robot.get_position();
            robot.excute_instruction(instructions.at(i));
            if (robot.get_position() > m_boundary)
            {
                vector<SPoint>::iterator iter = find(m_droppingPoints.begin(), m_droppingPoints.end(), previousPoint);
                // go back to previous position
                robot.set_position(previousPoint);
                if (iter == m_droppingPoints.end())
                {
                    robot.set_lost(true);
                    m_droppingPoints.push_back(previousPoint);
                    return;
                }
            }
        }
    }

private:
    SPoint m_boundary;
    vector<SPoint> m_droppingPoints;
};

void robot_test_case(CGrid& grid, const SPoint& _point)
{
    char c;
    cin >> c;
    CRobot robot(_point, c);

    string str;
    cin >> str;
    robot.insert_instructions(str);

    grid.put_selfwalking_robot(robot);

    cout << robot.get_position() << " " << robot.get_orientation();

    if (robot.get_lost())
    {
        cout << " LOST";
    }

    cout << endl;
}

int main()
{
    SPoint _point;
    cin >> _point;
    CGrid grid(_point);

    while (cin >> _point)
    {
        robot_test_case(grid, _point);
    }

    return 0;
}
