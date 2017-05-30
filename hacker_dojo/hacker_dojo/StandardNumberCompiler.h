#pragma  once
#include <map>
#include <string>

class CStandardNumberCompiler
{
public:
    CStandardNumberCompiler();

    static CStandardNumberCompiler CreateCompilerInstance();

    const unsigned char LookupTable(const unsigned char ch);

private:
    std::map<unsigned char, unsigned char> m_memoralbeTeleNumberMap;
};