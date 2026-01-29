#include "NormalizeSpaceTransformation.h"

std::string NormalizeSpaceTransformation::transform(const std::string& string) const
{
    std::string result;
    bool previousWasSpace = false;

    for (char c : string) {
        if (c == ' ') {
            if (!previousWasSpace) {
                result += c;
                previousWasSpace = true;
            }
        } else {
            result += c;
            previousWasSpace = false;
        }
    }
    return result;
}

std::unique_ptr<TextTransformation> NormalizeSpaceTransformation::clone() const
{
    return std::make_unique<NormalizeSpaceTransformation>(*this);
}
