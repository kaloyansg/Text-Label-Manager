#pragma once
#include "Label.h"
class HelpLabel : public Label
{
public:
	HelpLabel(std::unique_ptr<Label>, const std::string&);
	HelpLabel(const HelpLabel&);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const override;

	virtual bool setValue(const std::string&) override;

	virtual std::string getHelpText() const;

private:
	/*mutable*/ std::unique_ptr<Label> label = nullptr;
	std::string helpText;
};

