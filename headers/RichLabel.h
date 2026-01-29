#pragma once
#include "SimpleLabel.h"
class RichLabel : public SimpleLabel
{
public:
	RichLabel(const std::string& string, const std::string&, size_t, const std::string&);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const override;

private:
	std::string color;
	size_t fontSize;
	std::string fontName;
};
