#include "CapitalizeTransformation.h"

std::string CapitalizeTransformation::transform(const std::string& string) const
{
    if (string.size() < 1) {
        return "";
    }
    std::string result(string);
    if (result[0] >= 'a' && result[0] <= 'z')
        result[0] = std::toupper(result[0]);
    return result;
}

std::unique_ptr<TextTransformation> CapitalizeTransformation::clone() const
{
    return std::make_unique<CapitalizeTransformation>(*this);
}
