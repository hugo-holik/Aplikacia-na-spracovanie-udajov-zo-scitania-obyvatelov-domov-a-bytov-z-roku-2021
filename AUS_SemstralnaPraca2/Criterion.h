#pragma once
#include "heap_monitor.h"

template <typename T, typename O>
class Criterion
{
public:
	virtual T evaluate(O& o) = 0;
};
