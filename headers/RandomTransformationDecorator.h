#pragma once
#include "LabelDecorator.h"
#include "TextTransformation.h"
#include <vector>
class RandomTransformationDecorator : public LabelDecorator
{
public:
	RandomTransformationDecorator(std::unique_ptr<Label>, const std::vector<std::unique_ptr<TextTransformation>>&);
	RandomTransformationDecorator(const RandomTransformationDecorator&);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const override;
private:
	std::vector<std::unique_ptr<TextTransformation>> transformations;
};

