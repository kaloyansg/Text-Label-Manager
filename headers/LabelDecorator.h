#pragma once
#include "Label.h"
class LabelDecorator : public Label
{
public:
	LabelDecorator(std::unique_ptr<Label>);
	virtual std::string getText() const override;
	virtual std::unique_ptr<Label> clone() const = 0;

	virtual bool setValue(const std::string&) override;

	template <typename classLabelDecorator>
	static std::unique_ptr<Label> removeDecoratorFrom(std::unique_ptr<Label> label);

	template <typename classLabelDecorator>
	std::shared_ptr<Label> removeDecorator();

protected:
	LabelDecorator(const LabelDecorator&);

private:
	std::unique_ptr<Label> wrappedLabel;
};

template<typename classLabelDecorator>
inline std::unique_ptr<Label> LabelDecorator::removeDecoratorFrom(std::unique_ptr<Label> label)
{
	if (!label) {
		return nullptr;
	}

	if (dynamic_cast<classLabelDecorator*>(label.get())) {
		LabelDecorator* decorator = dynamic_cast<LabelDecorator*>(label.get());

		if (decorator) {
			std::unique_ptr<Label> inner = std::move(decorator->wrappedLabel);
			return removeDecoratorFrom<classLabelDecorator>(std::move(inner));
		}
	}
	else {
		LabelDecorator* decorator = dynamic_cast<LabelDecorator*>(label.get());
		if (decorator) {
			std::unique_ptr<Label> inner = std::move(decorator->wrappedLabel);
			std::unique_ptr<Label> cleanedInner = removeDecoratorFrom<classLabelDecorator>(std::move(inner));
			decorator->wrappedLabel = std::move(cleanedInner);
			return label;
		}
	}
	return label;
}

template<typename classLabelDecorator>
inline std::shared_ptr<Label> LabelDecorator::removeDecorator()
{
	//return removeDecoratorFrom<classLabelDecorator>(this->clone());

	/*if (dynamic_cast<classLabelDecorator*>(this)) {
		LabelDecorator* decorator = dynamic_cast<LabelDecorator*>(this);

		if (decorator)
		{
			std::unique_ptr<Label> inner = std::move(decorator->wrappedLabel);
			decorator = std::move(removeDecoratorFrom<classLabelDecorator>(std::move(inner)));
		}
	}
	else {

		LabelDecorator* decorator = dynamic_cast<LabelDecorator*>(this);
		if (decorator) {
			std::unique_ptr<Label> inner = std::move(decorator->wrappedLabel);
			std::unique_ptr<Label> cleanedInner = removeDecoratorFrom<classLabelDecorator>(std::move(inner));
			decorator->wrappedLabel = std::move(cleanedInner);
		}

	}*/

	LabelDecorator* decorator = dynamic_cast<LabelDecorator*>(this);
		if (decorator) {
			std::unique_ptr<Label> inner = std::move(decorator->wrappedLabel);
			std::unique_ptr<Label> cleanedInner = removeDecoratorFrom<classLabelDecorator>(std::move(inner));
			decorator->wrappedLabel = std::move(cleanedInner);
		}

	return this->clone();
}
