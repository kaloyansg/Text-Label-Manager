#include "DecorateTransformation.h"

std::string DecorateTransformation::transform(const std::string& string) const
{
	return "-={ " + string + " }=-";
}

std::unique_ptr<TextTransformation> DecorateTransformation::clone() const
{
	return std::make_unique<DecorateTransformation>(*this);
}
