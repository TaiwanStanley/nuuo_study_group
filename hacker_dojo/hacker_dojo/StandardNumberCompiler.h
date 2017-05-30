#pragma  once
#include <map>
#include <string>

class CStandardNumberCompiler
{
public:
    static CStandardNumberCompiler CreateCompilerInstance();
    const unsigned char LookupTable(const unsigned char ch);

private:
    CStandardNumberCompiler();
    std::map<unsigned char, unsigned char> m_memoralbeTeleNumberMap;
};