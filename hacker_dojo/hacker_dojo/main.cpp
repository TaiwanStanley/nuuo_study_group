#include <iostream>
#include <string>
#include <stack>

using namespace std;

stack<char> g_stack;

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

void printStack()
{
    stack<char> temp(g_stack);
    size_t size = temp.size();
    for (size_t i = 0; i < size; i++)
    {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}

size_t parseBrackets(const string& str)
{
    const char *pChar = str.c_str();
    size_t char_position = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        char_position++;
        if (IsOpenBracket(pChar[i]))
        {
            if (pChar[i] == '(' && (pChar[i+1]) == '*')
            {
                g_stack.push('*');
                i++;
            }
            else
            {
                g_stack.push(pChar[i]);
            }
        }
        else if (IsCloseBracket(pChar[i]) || (pChar[i] == '*' && (pChar[i+1]) == ')'))
        {
            if (g_stack.empty())
            {
                return char_position;
            }

            if (pChar[i] == '*')
            {
                if (g_stack.top() != '*')
                {
                    return char_position;
                }
                g_stack.pop();

                i++;
            }
            else if (pChar[i] == ')')
            {
                if (g_stack.top() != '(')
                {
                    return char_position;
                }
                g_stack.pop();
            }
            else if (pChar[i] == ']')
            {
                if (g_stack.top() != '[')
                {
                    return char_position;
                }
                g_stack.pop();
            }
            else if (pChar[i] == '}')
            {
                if (g_stack.top() != '{')
                {
                    return char_position;
                }
                g_stack.pop();
            }
            else if (pChar[i] == '>')
            {
                if (g_stack.top() != '<')
                {
                    return char_position;
                }
                g_stack.pop();
            }
        }
    }

    if (!g_stack.empty())
    {
        while (!g_stack.empty())
        {
            char_position++;
            g_stack.pop();
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
        while (!g_stack.empty())
        {
            g_stack.pop();
        }
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