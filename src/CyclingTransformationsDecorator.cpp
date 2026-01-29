#include "CyclingTransformationsDecorator.h"
#include <stdexcept>

CyclingTransformationsDecorator::CyclingTransformationsDecorator(std::unique_ptr<Label> label, 
	const std::vector<std::unique_ptr<TextTransformation>>& transes) : LabelDecorator(std::move(label)), idx(0) 
{
	/*if (transformations.size() == 0) {
		throw std::invalid_argument("vector must not be empty");
	}*/
	for (const std::unique_ptr<TextTransformation>& item : transes) {
		transformations.push_back(item->clone());
	}
}

CyclingTransformationsDecorator::CyclingTransformationsDecorator(const CyclingTransformationsDecorator& other) : 
	LabelDecorator(other), idx(0)
{
	size_t size = other.transformations.size();
	for (size_t i = 0; i < size; i++)
	{
		transformations.push_back(other.transformations[i]->clone());
	}
}

std::string CyclingTransformationsDecorator::getText() const
{
	if (transformations.size() == 0) {
		return LabelDecorator::getText();
	}

	if (idx >= transformations.size()) {
		idx = 0;
	}
	return transformations[idx++]->transform(LabelDecorator::getText());
}

std::unique_ptr<Label> CyclingTransformationsDecorator::clone() const
{
	return std::make_unique<CyclingTransformationsDecorator>(*this);
}
