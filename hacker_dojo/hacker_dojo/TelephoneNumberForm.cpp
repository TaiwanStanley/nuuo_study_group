#include "TelephoneNumberForm.h"
#include "StandardNumberCompiler.h"
#include <iostream>
using namespace std;

CTelephoneNumberForm::CTelephoneNumberForm()
{
    m_has_duplicates = false;
}

void CTelephoneNumberForm::ToStandardForm(const string& tel_number)
{
    string standard_form = "";
    CStandardNumberCompiler pNumCompiler = CStandardNumberCompiler::CreateCompilerInstance();
    for (size_t i = 0; i < tel_number.length(); i++)
    {
        string ch = string(1, pNumCompiler.LookupTable(tel_number.at(i)));
        if (ch != "-" && ch != " ")
        {
            standard_form += ch;
            if (standard_form.length() == 3)
            {
                standard_form += '-';
            }
        }
    }
    InsertStardardFormNumberTable(standard_form);
}

void CTelephoneNumberForm::PrintDuplicatesStandardFormNumber()
{
    map<string, unsigned int>::iterator it = m_standard_form.begin();
    for (; it != m_standard_form.end(); it++)
    {
        if (it->second > 1)
        {
            cout << it->first << " " << it->second << endl;
        }
    }
}

void CTelephoneNumberForm::HasDuplicatesNum() const
{
    if (!m_has_duplicates)
    {
        cout << "No duplicates." << endl;
    }
}

void CTelephoneNumberForm::InsertStardardFormNumberTable(const string& standard_form)
{
    map<string, unsigned int>::iterator it = m_standard_form.find(standard_form);
    if (it != m_standard_form.end())
    {
        it->second++;
        m_has_duplicates = true;
    }
    else
    {
        m_standard_form[standard_form] = 1;
    }
}
