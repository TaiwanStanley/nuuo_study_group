#include <iostream>
#include <string>
#include <stack>

using namespace std;


bool IsOpenBracket(char ch)
{
    if (ch =='(' || ch == '[' || ch == '{' || ch == '<')
    {
        return true;
    }
    return false;
}

bool IsCloseBracket(char ch)
{
    if (ch == ')' || ch == ']' || ch == '}' || ch == '>')
    {
        return true;
    }
    return false;
}

size_t parseBrackets(const string& str)
{
    const char *pChar = str.c_str();
    size_t char_position = 0;
    stack<char> stack;
    for (size_t i = 0; i < str.length(); i++)
    {
        char_position++;
        if (IsOpenBracket(pChar[i]))
        {
            if (pChar[i] == '(' && (pChar[i+1]) == '*')
            {
                stack.push('*');
                i++;
            }
            else
            {
                stack.push(pChar[i]);
            }
        }
        else if (IsCloseBracket(pChar[i]) || (pChar[i] == '*' && (pChar[i+1]) == ')'))
        {
            if (stack.empty())
            {
                return char_position;
            }

            if (pChar[i] == '*')
            {
                if (stack.top() != '*')
                {
                    return char_position;
                }
                stack.pop();

                i++;
            }
            else if (pChar[i] == ')')
            {
                if (stack.top() != '(')
                {
                    return char_position;
                }
                stack.pop();
            }
            else if (pChar[i] == ']')
            {
                if (stack.top() != '[')
                {
                    return char_position;
                }
                stack.pop();
            }
            else if (pChar[i] == '}')
            {
                if (stack.top() != '{')
                {
                    return char_position;
                }
                stack.pop();
            }
            else if (pChar[i] == '>')
            {
                if (stack.top() != '<')
                {
                    return char_position;
                }
                stack.pop();
            }
        }
    }

    if (!stack.empty())
    {
        while (!stack.empty())
        {
            char_position++;
            stack.pop();
        }
        return char_position;
    }

    return 0;
}
    
int main(void)
{
    string str;
    while (getline(cin, str))
    {
        size_t t =parseBrackets(str);
        if (t == 0)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO " << t << endl;
        }
    }

    system("pause");

    return 0;
}