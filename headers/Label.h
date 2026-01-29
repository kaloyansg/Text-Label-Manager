#pragma once
#include <string>
#include <memory>
class Label
{
public:
	virtual std::string getText() const = 0;
	virtual std::unique_ptr<Label> clone() const = 0;
	virtual ~Label() = default;

	virtual bool setValue(const std::string&) = 0;
};
