#pragma once
#include "LabelDecorator.h"
#include "TextTransformation.h"
class TextTransformationDecorator : public LabelDecorator
{
public:
	TextTransformationDecorator(std::unique_ptr<Label>, std::unique_ptr<TextTransformation>);
	TextTransformationDecorator(const TextTransformationDecorator&);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const override;
private:
	std::unique_ptr<TextTransformation> transformation;
};
