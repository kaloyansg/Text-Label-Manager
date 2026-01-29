#pragma once
#include <string>
#include <memory>
class TextTransformation
{
public:
	virtual std::string transform(const std::string&) const = 0;
	virtual std::unique_ptr<TextTransformation> clone() const = 0;
	virtual ~TextTransformation() = default;
};
