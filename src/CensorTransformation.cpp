#include "CensorTransformation.h"

CensorTransformation::CensorTransformation(const std::string& string) : w(string) {}

std::string CensorTransformation::transform(const std::string& string) const
{
	if (w.empty()) {
		return string;
	}
	size_t l = w.size();
	std::string replacement(l, '*');
	std::string result("");
	for (size_t i = 0; i < string.size();) {
		if (i + l <= string.size() && w == string.substr(i, l)) {
			result.append(replacement);
			i += l;
		}
		else {
			result += string[i];
			++i;
		}
	}

	return result;
}

std::unique_ptr<TextTransformation> CensorTransformation::clone() const
{
	return std::make_unique<CensorTransformation>(*this);
}

std::string CensorTransformation::getWordCensor() const
{
	return w;
}
