#pragma once
#include "CensorTransformation.h"
#include <map>

class CensorTransformationFactory
{
public:
	static std::shared_ptr<CensorTransformation> createCensorTransformation(const std::string&);
private:
	CensorTransformationFactory() = delete;
private:
	static std::map<std::string, std::shared_ptr<CensorTransformation>> cencores;
};

