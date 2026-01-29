#pragma once
#include "SimpleLabel.h"
class ProxyLabel : public Label
{
public://default constructor (nullptr)
	ProxyLabel(std::unique_ptr<Label>);
	ProxyLabel(const ProxyLabel&);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const override;

	virtual bool setValue(const std::string&) override;

	void timeOut() const; //cnt times called getText

private:
	mutable std::unique_ptr<Label> label;
	mutable bool timeOutCheck = 0;
	mutable bool initial = 1;
};

