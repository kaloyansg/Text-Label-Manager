#include "LeftTrimTransformation.h"

std::string LeftTrimTransformation::transform(const std::string& string) const
{
	if (string.empty()) {
		return string;
	}

	if (string[0] != ' ') {
		return string;
	}

	size_t i = 0;
	while (string[i] == ' ') {
		++i;
	}
    return string.substr(i,string.size()-i);
}

std::unique_ptr<TextTransformation> LeftTrimTransformation::clone() const
{
	return std::make_unique<LeftTrimTransformation>(*this);
}
