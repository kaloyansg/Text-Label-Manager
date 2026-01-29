#include <iostream>
#include <vector>
#include "Label.h"
#include "SimpleLabel.h"
#include "TextTransformationDecorator.h"
#include "RandomTransformationDecorator.h"
#include "CapitalizeTransformation.h"
#include "RightTrimTransformation.h"
#include "CensorTransformation.h"
#include "ProxyLabel.h"
#include "HelpLabel.h"
#include "LabelPrinter.h"
#include "CensorTransformationFactory.h"

int main()
{
	SimpleLabel label("texexexext    ");

	CensorTransformation cens("exe");
	TextTransformationDecorator ttd(std::make_unique<SimpleLabel>(label), 
		std::make_unique<CensorTransformation>(cens));

	std::cout << ttd.getText() << '\n';

	std::vector<std::unique_ptr<TextTransformation>> transes;
	CapitalizeTransformation c;
	RightTrimTransformation r;
	transes.push_back(std::make_unique<CapitalizeTransformation>(c));
	transes.push_back(std::make_unique<RightTrimTransformation>(r));

	RandomTransformationDecorator rtt(std::make_unique<TextTransformationDecorator>
		(std::make_unique<SimpleLabel>(label), std::make_unique<CensorTransformation>("exe")), transes);
	std::cout << rtt.getText() << "-" << '\n';
	std::cout << rtt.getText() << "-" << '\n';
	std::cout << rtt.getText() << "-" << '\n';
	std::cout << rtt.getText() << "-" << '\n';
	std::cout << rtt.getText() << "-" << '\n';
	std::cout << rtt.getText() << "-" << '\n';
	std::cout << rtt.getText() << "-" << '\n';
	std::cout << rtt.getText() << "-" << '\n';

	std::cout << ttd.getText() << '\n';
	std::cout << transes[0]->transform("aaa") << '\n';

	std::unique_ptr<Label> cleaned = 
		LabelDecorator::removeDecoratorFrom<TextTransformationDecorator>(rtt.clone());
	std::cout << cleaned->getText() << "-\n";
	std::cout << cleaned->getText() << "-\n";
	std::cout << cleaned->getText() << "-\n";

	std::shared_ptr<Label> cleanedRTT = rtt.removeDecorator<TextTransformationDecorator>();
	std::cout << cleanedRTT->getText() << "-\n";
	std::cout << rtt.getText() << "-\n";

	ProxyLabel pl(rtt.clone());
	std::cout << pl.getText() << "\n";
	std::cout << pl.getText() << "\n";
	pl.timeOut();
	std::cout << pl.getText() << "\n";
	std::cout << pl.getText() << "\n";

	HelpLabel hl(pl.clone(), "HELP TEXT.");
	std::cout << hl.getText() << " " << hl.getHelpText() << "\n";

	LabelPrinter::print(hl);
	LabelPrinter::printWithHelpText(hl);

	std::shared_ptr<CensorTransformation> ct1 = CensorTransformationFactory::createCensorTransformation("e");
	std::cout << ct1->transform(label.getText());
	std::shared_ptr<CensorTransformation> ct2 = CensorTransformationFactory::createCensorTransformation("e");
	std::cout << ct1->transform(label.getText());
}