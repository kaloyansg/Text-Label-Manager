#include "ReplaceTransformation.h"

ReplaceTransformation::ReplaceTransformation(const std::string& a, const std::string& b) : 
	oldStr(a), newStr(b) {}

std::string ReplaceTransformation::transform(const std::string& string) const
{
	if (oldStr.empty()) {
		return string;
	}
	std::string result("");
	for (size_t i = 0; i < string.size();)
	{
		size_t idx = string.substr(i, string.size() - i).find(oldStr);
		if (idx == std::string::npos) {
			result.append(string.substr(i, string.size() - i));
			break;
		}
		else {
			result.append(string.substr(i, idx));
			result.append(newStr);
			i += (idx)+oldStr.size();
		}
	}
	return result;
}

std::unique_ptr<TextTransformation> ReplaceTransformation::clone() const
{
	return std::make_unique<ReplaceTransformation>(*this);
}
