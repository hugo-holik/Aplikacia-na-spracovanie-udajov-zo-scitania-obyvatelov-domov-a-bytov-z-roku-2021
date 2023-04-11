#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{
	/// <summary> Triedenie Shell sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class ShellSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Shell sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;

	private:
		void shell(int step);

	private:
		UnsortedSequenceTable<K, T>& table_;
	};


	template<typename K, typename T>
	inline void ShellSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		shell(3);
	}

	template <typename K, typename T>
	void ShellSort<K, T>::shell(int step)
	{
		for (int delta = 0; delta < (step - 1); delta++)
		{
			for (int i = delta; i < (table_.size() - 1); i += step)
			{
				int j = i;
				while (j - step >= delta && table_.getItemAtIndex(j).getKey() < table_.getItemAtIndex(j - step).getKey())
				{
					auto temp = table_.getItemAtIndex(j);
					table_.swap(j, (j - 1));
					j -= step;
				}
			}
		}
		if (step > 1)
		{
			shell(step - 1);
		}
	}
}
