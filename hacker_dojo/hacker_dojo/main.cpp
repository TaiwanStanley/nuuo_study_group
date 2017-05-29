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

bool PairForBracket(const char * pChar, size_t &i, stack<char> &stack)
{
    if (stack.empty())
    {
        return false;
    }
    else if (pChar[i] == '*')
    {
        if (stack.top() != '*')
        {
            return false;
        }
        i++;
    }
    else if (pChar[i] == ')')
    {
        if (stack.top() != '(')
        {
            return false;
        }
    }
    else if (pChar[i] == ']')
    {
        if (stack.top() != '[')
        {
            return false;
        }
    }
    else if (pChar[i] == '}')
    {
        if (stack.top() != '{')
        {
            return false;
        }
    }
    else if (pChar[i] == '>')
    {
        if (stack.top() != '<')
        {
            return false;
        }
    }
    return true;
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
            if (PairForBracket(pChar, i, stack))
            {
                stack.pop();
            }
            else
            {
                return char_position;
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