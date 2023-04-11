#pragma once
#include "TerritorialUnit.h"

class Kraj :
	public TerritorialUnit
{

public:
	Kraj(std::wstring name, std::wstring code) :
		TerritorialUnit(name, code, TerritorialUnitType::Kraj)
	{
	}

	std::wstring toString() override
	{
		std::wstringstream stream;

		stream << name_ << L"\n";
		stream << L"Stat: " << parent_->getName() << L"\n";

		stream << TerritorialUnit::toString();

		return stream.str();
	}
};
