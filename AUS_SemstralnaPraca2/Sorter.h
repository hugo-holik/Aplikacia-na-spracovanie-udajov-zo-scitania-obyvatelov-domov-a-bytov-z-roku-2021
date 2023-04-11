#pragma once
#include "heap_monitor.h"
#include "Criterion.h"
#include "TerritorialUnit.h"
#include "structures/table/unsorted_sequence_table.h"

template <typename V> // V - ValueType - co sa porovnava (nazov, pocet/podiel vzdelania)
class Sorter
{
public:
	void sort(structures::UnsortedSequenceTable<std::wstring, TerritorialUnit*>& table, Criterion<V, TerritorialUnit>& criterion, bool ascending)
	{
		quickSort(table, criterion, ascending, 0, table.size() - 1);
	}
private:
	void quickSort(structures::UnsortedSequenceTable<std::wstring, TerritorialUnit*>& table, Criterion<V, TerritorialUnit>& criterion, bool ascending, int min, int max)
	{
		int leftPointer = min;
		int rightPointer = max;

		TerritorialUnit* pivotTU = table.getItemAtIndex((min + max) / 2).accessData();
		V pivot = criterion.evaluate(*pivotTU);

		do
		{
			if (ascending)
			{
				//TerritorialUnit* leftTU = table.getItemAtIndex(leftPointer).accessData();
				//V left = criterion.evaluate(*leftTU);
				while (criterion.evaluate(*(table.getItemAtIndex(leftPointer).accessData())) < pivot)
				{
					leftPointer++;
				}

				//TerritorialUnit* rightTU = table.getItemAtIndex(rightPointer).accessData();
				//V right = criterion.evaluate(*rightTU);
				while (criterion.evaluate(*(table.getItemAtIndex(rightPointer).accessData())) > pivot)
				{
					rightPointer--;
				}
			}
			else
			{
				//TerritorialUnit* leftTU = table.getItemAtIndex(leftPointer).accessData();
				//V left = criterion.evaluate(*leftTU);
				while (criterion.evaluate(*(table.getItemAtIndex(leftPointer).accessData())) > pivot)
				{
					leftPointer++;
				}
				//TerritorialUnit* rightTU = table.getItemAtIndex(rightPointer).accessData();
				//V right = criterion.evaluate(*rightTU);
				while (criterion.evaluate(*(table.getItemAtIndex(rightPointer).accessData())) < pivot)
				{
					rightPointer--;
				}
			}
			if (leftPointer <= rightPointer)
			{
				table.swap(leftPointer, rightPointer);
				leftPointer++;
				rightPointer--;
			}
		} while (leftPointer <= rightPointer);


		if (min < rightPointer)
		{
			quickSort(table, criterion, ascending, min, rightPointer);
		}
		if (max > leftPointer)
		{
			quickSort(table, criterion, ascending, leftPointer, max);
		}

	}
};

