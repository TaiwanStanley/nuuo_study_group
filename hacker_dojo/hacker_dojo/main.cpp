#include <iostream>
#include <string>

using namespace std;

void test_case()
void test_case(const string& line)
{

}

int main(void)
{
    string line;
    while (getline(cin, line))
    {
        test_case(line);
    }
}