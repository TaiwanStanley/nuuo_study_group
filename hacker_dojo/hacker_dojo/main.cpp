#include <iostream>

#include <vector>
#include <regex>
#include <string>
using namespace std;

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

class DOMParsing
{
    enum eDOOR
    {
        OPENING,
        CLOSING
    };
public:
    DOMParsing():
        m_opening_template("\'(.+)\'")
    {};
    ~DOMParsing(){};
    
    void parsing_line(const string& line)
    {
        string value;
        eDOOR door(CLOSING);
        if ( (value = get_value(line)) != string(""))
        {
            door = OPENING;
        }

        if (door == CLOSING)
        {
            m_tree.goto_previous_level();
        }
        else
        {
            m_tree.insert_child(value);
        }
    }

    void read_to_search()
    {
        m_tree.set_present(m_tree.get_root());
    }

    string do_search(const string& instruction)
    {
        string value("");
        CNode<string>* present = m_tree.get_present();
        CNode<string>* node = present;
        if (instruction == "first_child")
        {
            if (present->m_children.size() > 0)
            {
                node = present->m_children[0];
            }
        }
        else if (instruction == "next_sibling")
        {
            if (present->m_next_sibling != nullptr)
            {
                node = present->m_next_sibling;
            }
        }
        else if (instruction == "previous_sibling")
        {
            if (present->m_previous_sibling != nullptr)
            {
                node = present->m_previous_sibling;
            }
        }
        else if (instruction == "parent")
        {
            if (present->m_previous != nullptr)
            {
                node = present->m_previous;
            }
        }
        m_tree.set_present(node);
        value = node->m_value;
        return value;
    }

private:
    string get_value(const string& str)
    {
        smatch pieces_match;
        if (regex_search(str, pieces_match, m_opening_template))
        {
            return string(pieces_match[1]);
        }
        return string("");
    }

private:
    CTreeList<string> m_tree;
    regex m_opening_template;
};

void build_tree_each_node(int dom_lines, DOMParsing &dom)
{
    string sline;
    while (dom_lines--)
    {
        getline(cin, sline);
        dom.parsing_line(sline);
    }
}

void do_search(DOMParsing &dom)
{
    static int cases = 1;

    string sline;
    cout << "Case " << cases << ":" << endl;

    dom.read_to_search();

    int lines = 0;
    cin >> lines;
    cin.ignore();

    while (lines--)
    {
        getline(cin, sline);
        cout << dom.do_search(sline) << endl;
    }
    cases++;
}

void test_case(int dom_lines)
{
    DOMParsing dom;
    build_tree_each_node(dom_lines, dom);
    do_search(dom);
}

int main()
{
    int dom_lines = 0;
    cin >> dom_lines;
    cin.ignore();

    while (dom_lines > 0)
    {
        test_case(dom_lines);
        cin >> dom_lines;
        cin.ignore();
    }

    return 0;
}