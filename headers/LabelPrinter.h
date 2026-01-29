#pragma once
#include "Label.h"
#include "HelpLabel.h"
class LabelPrinter
{
public:
	static void print(const Label&);
	static void printWithHelpText(const HelpLabel&);

private:
	LabelPrinter() = delete;
};

