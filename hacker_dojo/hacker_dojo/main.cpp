#include <iostream>
#include <bitset>
#include <map>
#include <string>
using namespace std;

static const int bit_size = 10;

class Saxophone
{
public:
    static bitset<bit_size> press(char c)
    {
        switch (c)
        {
        case 'a': return bitset<bit_size>("0000000110");
        case 'b': return bitset<bit_size>("0000000010");
        case 'c': return bitset<bit_size>("1111001110");
        case 'd': return bitset<bit_size>("0111001110");
        case 'e': return bitset<bit_size>("0011001110");
        case 'f': return bitset<bit_size>("0001001110");
        case 'g': return bitset<bit_size>("0000001110");
        case 'A': return bitset<bit_size>("0000000111");
        case 'B': return bitset<bit_size>("0000000011");
        case 'C': return bitset<bit_size>("0000000100");
        case 'D': return bitset<bit_size>("0111001111");
        case 'E': return bitset<bit_size>("0011001111");
        case 'F': return bitset<bit_size>("0001001111");
        case 'G': return bitset<bit_size>("0000001111");
        default:  return bitset<bit_size>("0000000000");
        }
    }
private:
    Saxophone();
};

class Musician
{
    public:
        Musician() : m_button_state("0000000000")
        {
            for (size_t i = 0; i < bit_size; i++)
            {
                counter[i] = 0;
            }
        }

        void play(char c)
        {
            bitset<bit_size> match = Saxophone::press(c);
            if (!match.none())
            {
                for (size_t i = 0; i < match.size(); i++)
                {
                    if (m_button_state.test(i) && !match.test(i) ||
                        !m_button_state.test(i) && match.test(i))
                    {
                        if (!m_button_state.test(i))
                        {
                            counter[i]++;
                        }
                        m_button_state[i] = match.test(i);
                    }
                }
            }
        }

        map<int, int> get_counter() const
        {
            return counter;
        }

private:
    bitset<bit_size> m_button_state;
    map<int, int> counter;
};

void testcase(const string& line)
{
    Musician player;

    for (auto c : line)
    {
        player.play(c);
    }

    map<int, int> result = player.get_counter();
    for (auto v : result)
    {
        cout << v.second;
        if (v.first != (bit_size-1))
        {
            cout << " ";
        }
    }

    cout << endl;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore();

    while (n--)
    {
        string line;
        getline(cin, line);
        testcase(line);
    }

    return 0;
}