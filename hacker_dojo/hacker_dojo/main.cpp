#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <tuple>
#include <vector>
#include <iomanip>
using namespace std;

template<class T>
T get_middle_podouble(T T1, T T2)
{
    return (T1 + T2) / 2;
}

typedef struct CVertex
{
    double x = 0.0;
    double y = 0.0;
};

class CParallelogram
{

public:
    void split_each_podoubles(const string& line)
    {
        stringstream ss(line);
        string podouble;
        
        CVertex vtex;
        int count = 0;

        while (getline(ss, podouble, ' '))
        {
            count++;
            if (count % 2 == 0)
            {
                vtex.y = stod(podouble);
                insert_vertex(make_pair(vtex.x, vtex.y));
            }
            else /*if (count % 2 == 1)*/
            {
                vtex.x = stod(podouble);
            }
        }
    }

    tuple<double, double> calculate_fourth_podouble()
    {
        if (m_vertices.empty())
        {
            return make_tuple(0, 0);
        }
        
        vector<pair<double, double>> two_vertices;
        for (auto it: m_vertices)
        {
            pair<double, double> v = it;
            
            if (m_duplicate_vertices != v)
            {
                two_vertices.push_back(v);
            }
        }

        CVertex vMid;
        if (two_vertices.size() == 2)
        {
            vMid.x = get_middle_podouble(two_vertices[0].first, two_vertices[1].first);
            vMid.y = get_middle_podouble(two_vertices[0].second, two_vertices[1].second);
        }

        return make_tuple((vMid.x * 2- m_duplicate_vertices.first), (vMid.y * 2- m_duplicate_vertices.second));
    }

private:
    void insert_vertex(const pair<double, double>& pV)
    {
        auto it = m_vertices.find(pV);
        if (it != m_vertices.end())
        {
            m_duplicate_vertices = pV;
        }
        else
        {
            m_vertices.insert(pV);
        }
    }

private:
    set<pair<double, double>> m_vertices;
    pair<double, double> m_duplicate_vertices;

};

void test_case(const string& line)
{
    CParallelogram parallelo;
    parallelo.split_each_podoubles(line);
    CVertex Vtex;
    tie(Vtex.x, Vtex.y) = parallelo.calculate_fourth_podouble();
    cout << fixed << setprecision(3) << Vtex.x << " " << Vtex.y << endl;
}

int main(void)
{
    string line;
    while (getline(cin, line))
    {
        test_case(line);
    }
}