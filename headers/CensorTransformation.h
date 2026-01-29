#pragma once
#include "TextTransformation.h"
class CensorTransformation : public TextTransformation
{
public:	
	CensorTransformation(const std::string&);
	virtual std::string transform(const std::string&) const override;
	virtual std::unique_ptr<TextTransformation> clone() const override;

	std::string getWordCensor() const;

private:
	std::string w;
};

