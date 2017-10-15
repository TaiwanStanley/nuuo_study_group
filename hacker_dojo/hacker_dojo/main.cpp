#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

class dominos_util
{
public:

    class domino_set
    {
    public:
        domino_set(size_t dominos) : m_dominos(dominos+1)
        {

        }

        void set_follows(size_t x, size_t y)
        {
            m_dominos.at(x).insert(y);
        }

        const set<size_t> &get_follows(size_t x) const
        {
            return m_dominos.at(x);
        }

        size_t get_size()
        {
            return m_dominos.size();
        }

    private:
        vector<set<size_t>> m_dominos;
    };

public:
    dominos_util(domino_set _dominos) : 
        m_dominos_set(_dominos),
        m_failed(_dominos.get_size(), false)
    {
    }

    void knock(size_t x)
    {
        if (m_failed.at(x)) return;

        m_failed.at(x) = true;

        for (const auto t : m_dominos_set.get_follows(x)) knock(t);

    }

    size_t get_failed_count()
    {
        return count(m_failed.begin(), m_failed.end(), true);
    }

private:
    const domino_set        m_dominos_set;
    vector<bool>            m_failed;
};

void testcase()
{
    size_t n = 0, m = 0, l = 0;
    cin >> n >> m >> l;

    dominos_util::domino_set d_set(n);
    while (m--)
    {
        size_t x = 0, y = 0;
        cin >> x >> y;
        d_set.set_follows(x, y);
    }

    dominos_util d_util(d_set);
    while (l--)
    {
        size_t  x = 0;
        cin >> x;
        d_util.knock(x);
    }
    cout << d_util.get_failed_count() << endl;
}

int main()
{
    size_t testcases = 0;
    cin >> testcases;
    while (testcases--) testcase();
    return 0;
}