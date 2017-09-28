#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

static inline size_t reverse_digital(size_t input)
{
    string s_input = to_string(input);
    reverse(s_input.begin(), s_input.end());
    return stoul(s_input);
}

void cal_digital_palindrome(size_t& result, size_t& times)
{
    try
    {
        size_t r_value = reverse_digital(result);

        do
        {
            if ((times >= 1000) || (result >= 4294967295))
            {
                return;
            }

            result += r_value;
            times++;
            r_value = reverse_digital(result);
        } while (r_value != result);
    }
    catch (...) // std::out_of_range, std::invalid_argument
    {
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
