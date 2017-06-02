#include <vector>
#include <sstream>
#include "Parallelogram.h"

using namespace std;

void CParallelogram::split_each_podoubles(const string& line)
{
    stringstream ss(line);
    string point;

    CVertex vtex;
    int count = 0;

    while (getline(ss, point, ' '))
    {
        count++;
        if (count % 2 == 0)
        {
            vtex.y = stod(point);
            insert_vertex(make_pair(vtex.x, vtex.y));
        }
        else /*if (count % 2 == 1)*/
        {
            vtex.x = stod(point);
        }
    }
}

tuple<double, double> CParallelogram::get_fourth_podouble()
{
    vector<pair<double, double>> except_duplicate_vertices;
    for (auto it : m_vertices)
    {
        if (m_duplicate_vertices != it)
        {
            except_duplicate_vertices.push_back(it);
        }
    }

    CVertex vMid;
    if (except_duplicate_vertices.size() == 2)
    {
        vMid.x = get_middle_point(except_duplicate_vertices[0].first, except_duplicate_vertices[1].first);
        vMid.y = get_middle_point(except_duplicate_vertices[0].second, except_duplicate_vertices[1].second);
    }

    return make_tuple((vMid.x * 2 - m_duplicate_vertices.first), (vMid.y * 2 - m_duplicate_vertices.second));
}

void CParallelogram::insert_vertex(const pair<double, double>& pV)
{
    if (m_vertices.find(pV) != m_vertices.end())
    {
        m_duplicate_vertices = pV;
    }
    else
    {
        m_vertices.insert(pV);
    }
}
