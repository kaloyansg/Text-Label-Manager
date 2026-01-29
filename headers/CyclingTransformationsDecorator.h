#pragma once
#include "LabelDecorator.h"
#include "TextTransformation.h"
#include <vector>
class CyclingTransformationsDecorator : public LabelDecorator
{
public:
	CyclingTransformationsDecorator(std::unique_ptr<Label>, const std::vector<std::unique_ptr<TextTransformation>>&);
	CyclingTransformationsDecorator(const CyclingTransformationsDecorator&);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const override;

private:
	std::vector<std::unique_ptr<TextTransformation>> transformations;
	mutable size_t idx;
};

