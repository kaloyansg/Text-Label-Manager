#pragma once
#include "Label.h"
class SimpleLabel : public Label
{
public:
	SimpleLabel(const std::string&);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const override;

	virtual bool setValue(const std::string&) override;

private:
	std::string value;
};
