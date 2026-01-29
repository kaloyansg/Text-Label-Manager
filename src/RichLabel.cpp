#include "RichLabel.h"

RichLabel::RichLabel(const std::string& string, 
	const std::string& color, size_t fontSize, const std::string& fontName) :
	SimpleLabel(string), color(color), fontSize(fontSize), fontName(fontName) {}

std::string RichLabel::getText() const
{
	return SimpleLabel::getText();
}

std::unique_ptr<Label> RichLabel::clone() const
{
	return std::make_unique<RichLabel>(*this);
}
