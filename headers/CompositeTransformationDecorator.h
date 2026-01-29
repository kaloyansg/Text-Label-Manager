#pragma once
#include "LabelDecorator.h"
#include "TextTransformation.h"
#include <vector>
class CompositeTransformationDecorator : public LabelDecorator
{
public:
	CompositeTransformationDecorator(std::unique_ptr<Label>, const std::vector<std::unique_ptr<TextTransformation>>&);
	CompositeTransformationDecorator(const CompositeTransformationDecorator&);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const override;

private:
	std::vector<std::unique_ptr<TextTransformation>> transformations;
};

