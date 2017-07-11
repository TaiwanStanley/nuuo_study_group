#include <iostream>

#include <vector>
using namespace std;

void test_case()
template<typename T>
class CNode
{
public:
    CNode(T v) : m_previous(nullptr), m_next_sibling(nullptr), m_previous_sibling(nullptr), m_value(v) {}
    ~CNode()
    {
        delete m_previous;
        for ( auto &child : m_children)
        {
            delete child;
        }
    }

    CNode<T>* m_previous;
    CNode<T>* m_next_sibling;
    CNode<T>* m_previous_sibling;
    vector<CNode<T>*> m_children;

    T m_value;
protected:

private:

};

template<typename T>
class ILinklist
{
public:
    ILinklist(){}
    virtual ~ILinklist(){}
    virtual void insert_child(T value) = 0;
};

template<typename T>
class CTreeList : public ILinklist<T>
{
public:
    CTreeList() : m_present(nullptr), m_root(nullptr) {}
    ~CTreeList()
    { 

    };

    void insert_child(T value)
    {
        CNode<T>* newNode = new CNode<T>(value);
        if (m_present != nullptr)
        {
            m_present->m_children.push_back(newNode);
            newNode->m_previous = m_present;
            
            if (m_present->m_children.size() > 1)
            {
                CNode<T>* sibling = m_present->m_children[m_present->m_children.size() - 2]; // index start from 0
                newNode->m_previous_sibling = sibling;
                sibling->m_next_sibling = newNode;
            }
        }
        else
        {
            m_root = newNode;
        }
        
        m_present = newNode;
    }

    CNode<T>* get_root()
    {
        return m_root;
    }

    void set_present(CNode<T>* node)
    {
        m_present = node;
    }

    CNode<T>* get_present()
    {
        return m_present;
    }

    void goto_previous_level()
    {
        CNode<T>* node = m_present->m_previous;
        m_present = node;
    }

private:
    CNode<T>* m_present;
    CNode<T>* m_root;
};
}

int main()
{
    int cases = 0;
    cin >> cases;
    while (cases--)
    {
        test_case();
    }

    return 0;
}