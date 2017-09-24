#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

static inline unsigned int reverse_integer(unsigned int input)
{
    unsigned int r_value = 0;
    while (input > 0)
    {
        int last_digital = input % 10;
        r_value = r_value * 10 + last_digital;
        input = input / 10;
    }
    return r_value;
}

void cal_digital_palindrome(unsigned int &result, int& times)
{
    unsigned int r_value = reverse_integer(result);

    while (r_value != result || (times == 0))
    {
        if ((times >= 1000) || (result >= 4294967295))
        {
            return;
        }

        result += r_value;
        times++;
        r_value = reverse_integer(result);
    }
}

string testcases(unsigned int result)
{
    int times = 0;
    cal_digital_palindrome(result, times);
    ostringstream oss;
    oss << times << " " << result;
    return oss.str();
}

int main()
{
    int lines;

    cin >> lines;
    cin.ignore(1, '\n');

    while (lines--)
    {
        string str;
        getline(cin, str);
        cout << testcases(stoi(str)) << endl;
    }

    return 0;
}
