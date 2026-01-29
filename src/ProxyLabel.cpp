#include "ProxyLabel.h"
#include <iostream>
#include <memory>

ProxyLabel::ProxyLabel(std::unique_ptr<Label> label) : label(std::move(label)) {}

ProxyLabel::ProxyLabel(const ProxyLabel& other)
	: label(other.label ? other.label->clone() : nullptr),
	timeOutCheck(0), initial(1) {}

std::string ProxyLabel::getText() const
{
	if (!initial && !timeOutCheck) {
		return label->getText();
	}

	if (timeOutCheck) {
		timeOutCheck = 0;
		std::cout << "Do you want to change the label's text(\"" << label->getText() << "\")?\n" << "(y/n): ";
		std::string anser;
		std::cin >> anser;
		if (anser != "y")
		{
			return label->getText();
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	initial = 0;
	//label = std::make_unique<SimpleLabel>(SimpleLabel(""));
	std::cout << "Enter label's text: ";
	std::string str;
	//std::cin.ignore();
	std::getline(std::cin, str);
	if (!label->setValue(str)) {
		throw std::logic_error("the label inside the proxy is special type of label");
	}
	return label->getText();
}

std::unique_ptr<Label> ProxyLabel::clone() const
{
	return std::make_unique<ProxyLabel>(*this);
}

bool ProxyLabel::setValue(const std::string&)
{
	return false;
}

void ProxyLabel::timeOut() const
{
	this->timeOutCheck = 1;
}
