#include <map>
#include <string>

class CStandardNumberCompiler
{
public:
    CStandardNumberCompiler();

    static CStandardNumberCompiler CreateCompilerInstance();

    const unsigned char LookupTable(const unsigned char ch);

    static std::string ToStandardForm(const std::string& tel_number);

private:
    std::map<unsigned char, unsigned char> m_memoralbeTeleNumberMap;
};