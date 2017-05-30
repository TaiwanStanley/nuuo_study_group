#include "StandardNumberCompiler.h"
#include <map>
#include <string>
using namespace std;

CStandardNumberCompiler::CStandardNumberCompiler()
{
    m_memoralbeTeleNumberMap['A'] = '2';
    m_memoralbeTeleNumberMap['B'] = '2';
    m_memoralbeTeleNumberMap['C'] = '2';
    m_memoralbeTeleNumberMap['D'] = '3';
    m_memoralbeTeleNumberMap['E'] = '3';
    m_memoralbeTeleNumberMap['F'] = '3';
    m_memoralbeTeleNumberMap['G'] = '4';
    m_memoralbeTeleNumberMap['H'] = '4';
    m_memoralbeTeleNumberMap['I'] = '4';
    m_memoralbeTeleNumberMap['J'] = '5';
    m_memoralbeTeleNumberMap['K'] = '5';
    m_memoralbeTeleNumberMap['L'] = '5';
    m_memoralbeTeleNumberMap['M'] = '6';
    m_memoralbeTeleNumberMap['N'] = '6';
    m_memoralbeTeleNumberMap['O'] = '6';
    m_memoralbeTeleNumberMap['P'] = '7';
    m_memoralbeTeleNumberMap['R'] = '7';
    m_memoralbeTeleNumberMap['S'] = '7';
    m_memoralbeTeleNumberMap['T'] = '8';
    m_memoralbeTeleNumberMap['U'] = '8';
    m_memoralbeTeleNumberMap['V'] = '8';
    m_memoralbeTeleNumberMap['W'] = '9';
    m_memoralbeTeleNumberMap['X'] = '9';
    m_memoralbeTeleNumberMap['Y'] = '9';
}

CStandardNumberCompiler CStandardNumberCompiler::CreateCompilerInstance()
{
    static CStandardNumberCompiler NumberCompiler;
    return NumberCompiler;
}

const unsigned char CStandardNumberCompiler::LookupTable(const unsigned char ch)
{
    map<unsigned char, unsigned char>::iterator it = m_memoralbeTeleNumberMap.find(ch);
    if (it != m_memoralbeTeleNumberMap.end())
    {
        return it->second;
    }
    return ch;
}
