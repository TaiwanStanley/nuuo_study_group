#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <map>

using namespace std;

struct tree
{
    int x;
    tree *l;
    tree *r;
};

void Preorder(tree *root, vector<char>& nodes) {
    if (root == 0)
    {
        nodes.push_back('E');
        return;
    }

    nodes.push_back(root->x);
    Preorder(root->l, nodes); 
    Preorder(root->r, nodes);
}


int solution3(tree * T) {
    // write your code in C++14 (g++ 6.2.0)
    
    map<char, int> data;
    vector<char> nodes;

    if (T == 0)
        return 0;

    Preorder(T, nodes);
    int ret = 0;
    for (int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i] == 'E')
        {
            
        }
        data[nodes[i]] = 0;
    }
}

int solution2(string &S) {
    // write your code in C++14 (g++ 6.2.0)
    int ret = 0;
    stack<char> tstack;
    bool opening = true;
    for (int i = 0; i < S.length(); i++)
    {
        if (S.at(i) == '(')
        {
            tstack.push(S.at(i));
        }
        else
        {
            break;
        }
    }

    ret = tstack.size();

    for (int i = ret; i < S.length(); i++)
    {
        if (S.at(i) == ')')
        {
            if (tstack.size() > 0)
            {
                tstack.pop();
            }
            else
            {
                ret++;
            }
        }
    }
    return ret;
}


enum timer
{
    HOUR = 0,
    MINUTE,
    SECOND,
};

vector<string> ParseDateTime(string & S)
{
    istringstream iss(S);
    string str;
    vector<string> vtime;
    while (getline(iss, str, ':'))
    {
        vtime.push_back(str);
    }

    return vtime;
}

int solution1(string &S, string &T) {
    // write your code in C++14 (g++ 6.2.0)
    int match_count = 0;
    timer t = MINUTE;
    vector<string> vS = ParseDateTime(S);
    vector<string> vT = ParseDateTime(T);

    // find the most different digital
    int different_length = 0;
    for (size_t i = 0; i < vS.size(); i++)
    {
        string s_element = vS[i];
        string t_element = vT[i];
        int num = 0;
        for (int j = 0; j < s_element.size(); j++)
        {
            if (s_element.at(j) != t_element.at(j))
            {
                num++;
            }
        }

        if (num > different_length)
        {
            different_length = num;
            t = (timer)i;
        }
    }

    int start = stoi(vS[(int)t]);
    int end = stoi(vT[(int)t]);
    for (int i = start; i <= end; i++)
    {
        string s;
        if (i < 10)
            s = "0" + to_string(i);
        else
            s = to_string(i);

        if (different_length == 2)
        {
            return 1;
        }
        else
        {
            match_count++;
        }


    }
    return match_count;
}

int main()
{
    string a = "22:22:21";
    string b = "22:22:23";
    
    cout << solution(a, b) << endl;

    system("pause");
    return 0;
}