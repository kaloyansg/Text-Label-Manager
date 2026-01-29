#pragma once
#include "TextTransformation.h"
class ReplaceTransformation : public TextTransformation
{
public:
	ReplaceTransformation(const std::string&, const std::string&);
	virtual std::string transform(const std::string&) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;

private:
	std::string oldStr;
	std::string newStr;
};

