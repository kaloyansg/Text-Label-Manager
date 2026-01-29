#include "RandomTransformationDecorator.h"
#include <stdexcept>

RandomTransformationDecorator::RandomTransformationDecorator(std::unique_ptr<Label> label, 
	const std::vector<std::unique_ptr<TextTransformation>>& transes) : LabelDecorator(std::move(label))
{
	/*if (transformations.size() == 0) {
		throw std::invalid_argument("vector must not be empty");
	}*/
	for (const std::unique_ptr<TextTransformation>& item : transes) {
		transformations.push_back(item->clone());
	}
}

RandomTransformationDecorator::RandomTransformationDecorator(const RandomTransformationDecorator& other) : 
	LabelDecorator(other)
{
	size_t size = other.transformations.size();
	for (size_t i = 0; i < size; i++)
	{
		transformations.push_back(other.transformations[i]->clone());
	}
}

std::string RandomTransformationDecorator::getText() const
{
	if (transformations.size() == 0) {
		return LabelDecorator::getText();
	}

	size_t randomIdx = rand() % transformations.size();
	return transformations[randomIdx]->transform(LabelDecorator::getText());
}

std::unique_ptr<Label> RandomTransformationDecorator::clone() const
{
	return std::make_unique<RandomTransformationDecorator>(*this);
}
