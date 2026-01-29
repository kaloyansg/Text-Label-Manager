#include "CompositeTransformationDecorator.h"

CompositeTransformationDecorator::CompositeTransformationDecorator(std::unique_ptr<Label> label, 
	const std::vector<std::unique_ptr<TextTransformation>>& transes) : LabelDecorator(std::move(label))
{
	for (const std::unique_ptr<TextTransformation>& currT : transes) {
		transformations.push_back(currT->clone());
	}
}

CompositeTransformationDecorator::CompositeTransformationDecorator(const CompositeTransformationDecorator& other) : 
	LabelDecorator(other)
{
	size_t size = other.transformations.size();
	for (size_t i = 0; i < size; i++)
	{
		transformations.push_back(other.transformations[i]->clone());
	}
}

std::string CompositeTransformationDecorator::getText() const
{
	if (transformations.size() == 0) {
		return LabelDecorator::getText();
	}
	std::string result = LabelDecorator::getText();
	for (const std::unique_ptr<TextTransformation>& currT : transformations) {
		result = currT->transform(result);
	}
	return result;
}

std::unique_ptr<Label> CompositeTransformationDecorator::clone() const
{
	return std::make_unique<CompositeTransformationDecorator>(*this);
}
