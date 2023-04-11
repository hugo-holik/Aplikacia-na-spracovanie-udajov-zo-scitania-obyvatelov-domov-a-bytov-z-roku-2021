#pragma once
#include "TerritorialUnit.h"

class Okres :
	public TerritorialUnit
{

public:
	Okres(std::wstring name, std::wstring code) :
		TerritorialUnit(name, code, TerritorialUnitType::Okres)
	{
	}

	std::wstring toString() override
	{
		std::wstringstream stream;

		stream << name_ << L"\n";
		stream << L"Kraj: " << parent_->getName() << L" | ";
		stream << L"Stat: " << parent_->getParent()->getName() << L"\n";

		stream << TerritorialUnit::toString();

		return stream.str();
	}
};


