#include "CompositeTransformation.h"

CompositeTransformation::CompositeTransformation(const std::vector<std::unique_ptr<TextTransformation>>& transes)
{
	for (const std::unique_ptr<TextTransformation>& currT : transes) {
		transformations.push_back(currT->clone());
	}
}

CompositeTransformation::CompositeTransformation(const CompositeTransformation& other)
{
	size_t size = other.transformations.size();
	for (size_t i = 0; i < size; i++)
	{
		transformations.push_back(other.transformations[i]->clone());
	}
}

std::string CompositeTransformation::transform(const std::string& string) const
{
	std::string result = string;
	for (const std::unique_ptr<TextTransformation>& currT : transformations) {
		result = currT->transform(result);
	}
	return result;
}

std::unique_ptr<TextTransformation> CompositeTransformation::clone() const
{
	return std::make_unique<CompositeTransformation>(*this);
}
