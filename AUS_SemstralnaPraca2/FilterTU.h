#pragma once
#include "heap_monitor.h"
#include "CriterionTU.h"
#include "Filter.h"
#include "TerritorialUnit.h"

template<typename T>
class FilterByValueTU :
	public FilterByValue<T, TerritorialUnit>
{
public:
	FilterByValueTU(Criterion<T, TerritorialUnit>* criterion, T value) :
		FilterByValue<T, TerritorialUnit>(criterion, value)
	{
	}
};

template<typename T>
class FilterByIntervalTU :
	public FilterByInterval<T, TerritorialUnit>
{
public:
	FilterByIntervalTU(Criterion<T, TerritorialUnit>* criterion, T min, T max) :
		FilterByInterval<T, TerritorialUnit>(criterion, min, max)
	{
	}
};

class FilterTUName :
	public FilterByValueTU<std::wstring>
{
public:
	FilterTUName(CriterionTUName* criterion, std::wstring name) :
		FilterByValueTU<std::wstring>(criterion, name)
	{
	}
};

class FilterTUType :
	public FilterByValueTU<TerritorialUnit::TerritorialUnitType>
{
public:
	FilterTUType(CriterionTUType* criterion, TerritorialUnit::TerritorialUnitType type) :
		FilterByValueTU<TerritorialUnit::TerritorialUnitType>(criterion, type)
	{
	}
};

class FilterTUMembership :
	public FilterByValueTU<bool> // hodnotu davam na true, potom vo FilterByValue sa porovna, ci vysledok najdenia prislusnosti (vysledok kriteria CriterionTUMembership je bool) sa rovna tej hodnote
{
public:
	FilterTUMembership(CriterionTUMembership* criterion, bool value) :
		FilterByValueTU<bool>(criterion, value)
	{
	}
};

class FilterTUEducationCount :
	public FilterByIntervalTU<int>
{
public:
	FilterTUEducationCount(CriterionTUEducationCount* criterion, int min, int max) :
		FilterByIntervalTU<int>(criterion, min, max)
	{
	}
};

class FilterTUEducationRatio :
	public FilterByIntervalTU<double>
{
public:
	FilterTUEducationRatio(CriterionTUEducationRatio* criterion, double min, double max) :
		FilterByIntervalTU<double>(criterion, min, max)
	{
	}
};



