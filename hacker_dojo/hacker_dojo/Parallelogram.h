#pragma once 
#include <string>
#include <set>
#include <tuple>

template<class T>
T get_middle_point(T T1, T T2)
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
    void split_each_podoubles(const std::string& line);

    std::tuple<double, double> get_fourth_podouble();

private:
    void insert_vertex(const std::pair<double, double>& pV);

private:
    std::set<std::pair<double, double>> m_vertices;
    std::pair<double, double> m_duplicate_vertices;
};
