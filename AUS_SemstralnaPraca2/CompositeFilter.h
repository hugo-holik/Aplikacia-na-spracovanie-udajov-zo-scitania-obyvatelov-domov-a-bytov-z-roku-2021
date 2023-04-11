#pragma once
#include "heap_monitor.h"
#include "Filter.h"
#include "structures/list/array_list.h"
#include "structures/list/double_linked_list.h"

template <typename V> // V = ObjectType
class CompositeFilter
{
private:
	structures::ArrayList<Filter<V>*>* filters_; 
public:
	CompositeFilter()
	{
		filters_ = new structures::ArrayList<Filter<V>*>();
	}

	~CompositeFilter()
	{
		for (Filter<V>* element : *filters_) {
			delete element;
		}
		delete filters_;
	}

	void insertFilter(Filter<V>* filter)
	{
		filters_->add(filter);
	}

	bool passFilter_AND(V& o)
	{
		for (auto filter : *filters_)
		{
			if (!filter->passFilter(o))
			{
				return false;
			}
		}
		return true;
	}

	bool passFilter_OR(V& o)
	{
		for (auto filter : *filters_)
		{
			if (filter->passFilter(o))
			{
				return true;
			}
		}
		return false;
	}
};

