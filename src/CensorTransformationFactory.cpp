#include "CensorTransformationFactory.h"

std::map<std::string, std::shared_ptr<CensorTransformation>> CensorTransformationFactory::cencores;

std::shared_ptr<CensorTransformation> CensorTransformationFactory::createCensorTransformation(const std::string& str)
{
    if (str.length() > 4) {
        return std::make_shared<CensorTransformation>(str);
    }

    auto it = cencores.find(str);
    if (it != cencores.end()) {
        return it->second;
    }

    std::shared_ptr<CensorTransformation> newCensor = std::make_shared<CensorTransformation>(str);
    cencores[str] = newCensor;
    return newCensor;
}
