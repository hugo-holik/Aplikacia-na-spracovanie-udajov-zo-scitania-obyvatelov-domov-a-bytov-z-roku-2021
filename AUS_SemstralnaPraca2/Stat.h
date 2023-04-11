#pragma once
#include "TerritorialUnit.h"

class Stat :
	public TerritorialUnit
{
public:
	Stat(std::wstring name, std::wstring code) :
		TerritorialUnit(name, code, TerritorialUnitType::Stat)
	{
	}
};


