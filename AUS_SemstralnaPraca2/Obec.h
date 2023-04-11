#pragma once
#include "TerritorialUnit.h"

class Obec :
	public TerritorialUnit
{
public:
	Obec(std::wstring name, std::wstring code) :
		TerritorialUnit(name, code, TerritorialUnitType::Obec)
	{
	}

	std::wstring toString() override
	{
		std::wstringstream stream;

		stream << name_ << L"\n";
		stream << L"Okres: " << parent_->getName() << L" | ";
		stream << L"Kraj: " << parent_->getParent()->getName() << L" | ";
		stream << L"Stat: " << parent_->getParent()->getParent()->getName() << L"\n";

		stream << TerritorialUnit::toString();

		return stream.str();
	}
};



