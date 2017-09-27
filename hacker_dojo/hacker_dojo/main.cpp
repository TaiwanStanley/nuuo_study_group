#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

static inline size_t reverse_integer(size_t input)
{
    size_t r_value = 0;
    while (input > 0)
    {
        size_t last_digital = input % 10;
        r_value = r_value * 10 + last_digital;
        input = input / 10;
    }
    return r_value;
}

void cal_digital_palindrome(size_t& result, size_t& times)
{
    size_t r_value = reverse_integer(result);

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

string testcases(size_t result)
{
    size_t times = 0;
    cal_digital_palindrome(result, times);
    ostringstream oss;
    oss << times << " " << result;
    return oss.str();
}

int main()
{
    size_t lines;

    cin >> lines;
    cin.ignore(1, '\n');

    while (lines--)
    {
        string str;
        getline(cin, str);
        cout << testcases(stoul(str)) << endl;
    }

    return 0;
}
