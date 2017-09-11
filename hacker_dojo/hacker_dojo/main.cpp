// you can use includes, for example:
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>
#include <set>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

using namespace std;

// string solution(string &S, string &C) {
//     // write your code in C++14 (g++ 6.2.0)
//     vector<string> result;
//     istringstream iss(S);
//     string str = "";
// 
//     while (getline(iss, str, ';'))
//     {
//         transform(str.begin(), str.end(), str.begin(), [](unsigned char c) -> unsigned char { return tolower(c); });
// 
//         istringstream iss2(str);
//         string str2 = "";
//         vector<string> person;
// 
//         while (getline(iss2, str2, ' '))
//         {
//             if (!str2.empty())
//             {
//                 string::size_type n;
//                 n = str2.find('-');
//                 if (n != std::string::npos)
//                 {
//                     str2.erase(str2.begin() + n);
//                 }
//                 person.push_back(str2);
//             }
//         }
// 
//         str2.clear();
//         if (person.size() == 2)
//         {
//             str2.append(person[1] + "_" + person[0]);
//         }
//         else if (person.size() == 3)
//         {
//             str2.append(person[2] + "_" + person[0] + "_" + person[1].at(0));
//         }
// 
// 
//         while (1)
//         {
//             int index = 1;
//             vector<string>::iterator iter;
//             iter = std::find(result.begin(), result.end(), str2);
//             if (iter != result.end())
//             {
//                 str2.append(to_string(++index));
//             }
//             else
//             {
//                 result.push_back(str2);
//                 break;
//             }
//         }
//     }
// 
//     transform(C.begin(), C.end(), C.begin(), [](unsigned char b) -> unsigned char { return tolower(b); });
// 
//     string output = "";
//     for (const auto &v : result)
//     {
//         output.append(v + +"@" + C + ".com;" + "\r\n");
//     }
//     output.append(".");
//     return output;
// }
// 
// 
// 
// void evevator_movement(vector<int> &in_evevator, int &stop_times, int &current_weight, int &current_people_count)
// {
//     //start transport
//     set<int> val;
//     for (size_t i = 0; i < in_evevator.size(); i++)
//     {
//         val.insert(in_evevator[i]);
//     }
//     stop_times += val.size() + 1;
//     current_weight = 0;
//     current_people_count = 0;
//     in_evevator.clear();
// }
// 
// int solution(vector<int> &A, vector<int> &B, int M, int X, int Y) {
//     // write your code in C++14 (g++ 6.2.0)
//     int current_weight = 0;
//     int current_people_count = 0;
//     int stop_times = 0;
//     vector<int> in_evevator;
//     for (size_t i = 0; i < A.size(); i++)
//     {
//         if ((current_weight + A[i]) > Y ||
//             (current_people_count + 1) > X)
//         {
//             evevator_movement(in_evevator, stop_times, current_weight, current_people_count);
//         }
// 
//         current_weight += A[i];
//         current_people_count++;
//         in_evevator.push_back(A[i]);
//     }
//     evevator_movement(in_evevator, stop_times, current_weight, current_people_count);
// 
//     return stop_times;
// }

bool solution(string &S, string &T) {
    // write your code in C++14 (g++ 6.2.0)

    int ignore = 0;

    for (size_t i = 0; i < S.size(); i++)
    {
        if (!isalpha(S.at(i)))
        {
            ignore = static_cast<int>(S.at(i)) - 48;
        }

        if (!isalpha(T.at(i)))
        {
            ignore = static_cast<int>(T.at(i)) - 48;
        }

        if (ignore > 0)
        {
            ignore--;
            continue;
        }
        else
        {
            if (S.at(i) != T.at(i))
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
//     string s = "John Doe; Peter Benjamin Parker; Mary Jane Watson-Parker; John Elvis Doe; John Evan Doe; Jane Doe; Peter Brian Parker";
//     string c = "Example";
//     cout << solution(s, c);
// 
//     vector<int> A;
//     A.push_back(40);
//     A.push_back(40);
//     A.push_back(100);
//     A.push_back(80);
//     A.push_back(20);
// 
//     vector<int> B;
//     B.push_back(3);
//     B.push_back(3);
//     B.push_back(2);
//     B.push_back(2);
//     B.push_back(3);
// 
//     cout << solution(A, B, 3, 5, 200);

//     string a = "A2Le";
//     string b = "2pL1";
//     solution(a, b);
    string a1 = "a10";
    string b1 = "10a";
    solution(a1, b1);

    system("pause");

    return 0;
}