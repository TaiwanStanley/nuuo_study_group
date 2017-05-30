#pragma once
#include <string>
#include <map>

class CTelephoneNumberForm
{
public:
    CTelephoneNumberForm();

    void ToStandardForm(const std::string& tel_number);

    void PrintDuplicatesStandardFormNumber();

    void HasDuplicatesNum() const;

private:
    void InsertStardardFormNumberTable(const std::string& standard_form);

private:
    std::map<std::string, unsigned int> m_standard_form;
    bool m_has_duplicates;
};
