#pragma once
#include "TextTransformation.h"
#include <vector>
class CompositeTransformation : public TextTransformation
{
public:
	CompositeTransformation(const std::vector<std::unique_ptr<TextTransformation>>&);
	CompositeTransformation(const CompositeTransformation&);
	virtual std::string transform(const std::string&) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;

private:
	std::vector<std::unique_ptr<TextTransformation>> transformations;
};

