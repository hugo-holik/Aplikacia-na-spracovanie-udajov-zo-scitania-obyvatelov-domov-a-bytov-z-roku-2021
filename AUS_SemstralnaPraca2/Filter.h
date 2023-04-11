#pragma once
#include "Criterion.h"
#include "heap_monitor.h"

template <typename V>
class Filter
{
public:
	virtual bool passFilter(V& o) = 0;
	virtual ~Filter() = default; // pred tym som tento riadok s virtual destruktorom nemal
};

template <typename T, typename V> // T - ValueType , V - ObjectType 
class FilterWithCriterion : public Filter<V>
{
protected:
	Criterion<T, V>* criterion_;
public:
	FilterWithCriterion(Criterion<T, V>* criterion) :
		criterion_(criterion)
	{
	}
	virtual ~FilterWithCriterion()
	{
		delete criterion_;
	}
};

template <typename T, typename V>
class FilterByValue : public FilterWithCriterion<T, V>
{
protected:
	T value_;
public:
	FilterByValue(Criterion<T, V>* criterion, T value) :
		FilterWithCriterion<T, V>(criterion),
		value_(value)
	{
	}

	bool passFilter(V& o) override
	{
		return FilterWithCriterion<T, V>::criterion_->evaluate(o) == value_;
	}
};

template <typename T, typename V>
class FilterByInterval : public FilterWithCriterion<T, V>
{
protected:
	T min_;
	T max_;
public:
	FilterByInterval(Criterion<T, V>* criterion, T min, T max) :
		FilterWithCriterion<T, V>(criterion),
		min_(min),
		max_(max)
	{
	}

	bool passFilter(V& o) override
	{
		T filteredValue = FilterWithCriterion<T, V>::criterion_->evaluate(o);
		return filteredValue >= min_ && filteredValue <= max_;
	}
		
};

