#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

unsigned int reverse_integer(unsigned int input)
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
    if ((times >= 1000) || (result >= 4294967295))
    {
        return;
    }

    unsigned int r_value = reverse_integer(result);

    if (r_value == result && times > 0)
        return;

    result += r_value;

    cal_digital_palindrome(result, ++times);
}

string testcases(const string& str)
{
    int times = 0;
    unsigned int result = stoi(str);

    cal_digital_palindrome(result, times);
    ostringstream oss;
    oss << times << " " << result;
    return oss.str();
}

int main()
{
    int lines;

    cin >> lines;
    cin.ignore();

    while (lines--)
    {
        string str;
        getline(cin, str);
        cout << testcases(str) << endl;
    }

    return 0;
}
