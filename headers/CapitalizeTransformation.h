#pragma once
#include "TextTransformation.h"
class CapitalizeTransformation : public TextTransformation
{
public:
	virtual std::string transform(const std::string&) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;
};
