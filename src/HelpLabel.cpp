#include "HelpLabel.h"

HelpLabel::HelpLabel(std::unique_ptr<Label> label, const std::string& str) : 
	label(std::move(label)), helpText(str) {}

HelpLabel::HelpLabel(const HelpLabel& other) : helpText(other.helpText) {
	if (other.label) {
		label = other.label->clone();
	}
}

std::string HelpLabel::getText() const
{
	return label->getText();
}

std::unique_ptr<Label> HelpLabel::clone() const
{
	return std::make_unique<HelpLabel>(*this);
}

bool HelpLabel::setValue(const std::string& string)
{
	label->setValue(string);
	return true;
}

std::string HelpLabel::getHelpText() const
{
	return helpText;
}
