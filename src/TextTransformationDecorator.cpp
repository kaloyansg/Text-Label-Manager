#include "TextTransformationDecorator.h"

TextTransformationDecorator::TextTransformationDecorator(std::unique_ptr<Label> label, 
	std::unique_ptr<TextTransformation> trans) : LabelDecorator(std::move(label)), 
	transformation(std::move(trans)) {}

TextTransformationDecorator::TextTransformationDecorator(const TextTransformationDecorator& other) : 
	LabelDecorator(other), transformation(other.transformation->clone()) {}

std::string TextTransformationDecorator::getText() const
{
	return transformation->transform(LabelDecorator::getText());
}

std::unique_ptr<Label> TextTransformationDecorator::clone() const
{
	return std::make_unique<TextTransformationDecorator>(*this);
}
