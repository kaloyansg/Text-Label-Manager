#include "RightTrimTransformation.h"

std::string RightTrimTransformation::transform(const std::string& string) const
{
    if (string.empty()) {
        return string;
    }

    size_t i = string.size();
    while (i > 0 && (string[i - 1] == ' ' || string[i - 1] == '\0')) {
        --i;
    }

    if (i == 0) {
        return "";
    }

    if (i == string.size()) {
        return string;
    }
    return string.substr(0, i);
}

std::unique_ptr<TextTransformation> RightTrimTransformation::clone() const
{
    return std::make_unique<RightTrimTransformation>(*this);
}
