#include "SimpleLabel.h"

SimpleLabel::SimpleLabel(const std::string& string) : value(string) {}

std::string SimpleLabel::getText() const
{
	return value;
}

std::unique_ptr<Label> SimpleLabel::clone() const
{
	return std::make_unique<SimpleLabel>(*this);
}

bool SimpleLabel::setValue(const std::string& str)
{
	value = str;
	return true;
}
