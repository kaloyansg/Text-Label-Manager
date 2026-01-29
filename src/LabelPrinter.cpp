#include "LabelPrinter.h"
#include <iostream>

void LabelPrinter::print(const Label& label)
{
	std::cout << "Here is a label: " << label.getText() << "\n";
}

void LabelPrinter::printWithHelpText(const HelpLabel& helpLabel)
{
	print(helpLabel);
	std::cout << "Some help information about this label: " << helpLabel.getHelpText() << "\n";

}
