#pragma once
#include "heap_monitor.h"
#include "Criterion.h"
#include "TerritorialUnit.h"

template <typename T> // T = ValueType
class CriterionTU :
	public Criterion<T, TerritorialUnit>
{
public:
	T evaluate(TerritorialUnit& territorialUnit) override = 0;
};

class CriterionTUName :
	public CriterionTU<std::wstring>
{
public:
	std::wstring evaluate(TerritorialUnit& territorialUnit) override
	{
		return territorialUnit.getName();
	}
};

class CriterionTUType :
	public CriterionTU<TerritorialUnit::TerritorialUnitType>
{
public:
	TerritorialUnit::TerritorialUnitType evaluate(TerritorialUnit& territorialUnit) override
	{
		return territorialUnit.getType();
	}
};

class CriterionTUMembership :
	public CriterionTU<bool>
{
private:
	TerritorialUnit& upperTerritorialUnit_;

public:
	CriterionTUMembership(TerritorialUnit& upperTerritorialUnit) :
		upperTerritorialUnit_(upperTerritorialUnit)
	{
	}

	bool evaluate(TerritorialUnit& territorialUnit) override
	{
		return territorialUnit.isMemberOf(upperTerritorialUnit_);
	}

};

class CriterionTUEducationCount :
	public CriterionTU<int>
{
private:
	int educationType_;

public:
	CriterionTUEducationCount(int educationType) :
		educationType_(educationType)
	{
	}

	int evaluate(TerritorialUnit& territorialUnit) override
	{
		return territorialUnit.getEducationCount(educationType_);
	}

};

class CriterionTUEducationRatio :
	public CriterionTU<double>
{
private:
	int educationType_;

public:
	CriterionTUEducationRatio(int educationType) :
		educationType_(educationType)
	{
	}

	double evaluate(TerritorialUnit& territorialUnit) override
	{
		return territorialUnit.educationRatio(educationType_);
	}

};



