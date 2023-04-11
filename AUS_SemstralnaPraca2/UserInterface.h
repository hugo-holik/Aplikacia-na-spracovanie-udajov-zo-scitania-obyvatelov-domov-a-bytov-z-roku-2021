#pragma once
#include <algorithm>
#include <iostream>
#include "heap_monitor.h"

#include "CompositeFilter.h"
#include "Data.h"
#include "FilterMakerUI.h"
#include "Sorter.h"
#include "structures/table/unsorted_sequence_table.h"

class UserInterface
{
private:
	Data* data_;

public:
	UserInterface(Data* data) :
		data_(data)
	{
		int input = 0;
		std::wcout << L"Vyberte si z ponúknutých funkcionalít: " << L"\n";
		std::wcout << L"1. Výpis územných jednotiek (ktoré spĺňajú vami zvolené filtre)  " << L"\n";
		std::wcout << L"2. Výpis a usporiadanie uzemných jednotiek (ktoré spĺňajú vami zvolené filtre)  " << L"\n";

		std::cin >> input;
		switch (input)
		{
		case 1:
			functionality1();
			break;
		case 2:
			functionality2();
			break;
		}
	}

	void functionality1()
	{
		FilterMakerUI* filterMaker = new FilterMakerUI(data_);
		CompositeFilter<TerritorialUnit>* compositeFilter = filterMaker->makeCompositeFilter();

		int input;
		std::wcout << L"\n";
		std::wcout << L"1. filtrovanie AND (územná jednotka musí prejsť každým filtrom)" << L"\n";
		std::wcout << L"2. filtrovanie OR (stačí aby územná jednotka prešla aspoň 1 filtrom)" << L"\n";

		std::wcin >> input;
		switch (input)
		{
		case 1:
			for (auto krajItem : data_->getStat()->getChildren())
			{
				TerritorialUnit* kraj = krajItem->accessData();
				if (compositeFilter->passFilter_AND(*kraj))
				{
					std::wcout << kraj->toString() << L"\n";
				}
				for (auto okresItem : kraj->getChildren())
				{
					TerritorialUnit* okres = okresItem->accessData();
					if (compositeFilter->passFilter_AND(*okres))
					{
						std::wcout << okres->toString() << L"\n";
					}
					for (auto obecItem : okres->getChildren())
					{
						TerritorialUnit* obec = obecItem->accessData();
						if (compositeFilter->passFilter_AND(*obec))
						{
							std::wcout << obec->toString() << L"\n";
						}
					}
				}
			}
			break;
		case 2:
			for (auto krajItem : data_->getStat()->getChildren())
			{
				TerritorialUnit* kraj = krajItem->accessData();
				if (compositeFilter->passFilter_OR(*kraj))
				{
					std::wcout << kraj->toString() << L"\n";
				}
				for (auto okresItem : kraj->getChildren())
				{
					TerritorialUnit* okres = okresItem->accessData();
					if (compositeFilter->passFilter_OR(*okres))
					{
						std::wcout << okres->toString() << L"\n";
					}
					for (auto obecItem : okres->getChildren())
					{
						TerritorialUnit* obec = obecItem->accessData();
						if (compositeFilter->passFilter_OR(*obec))
						{
							std::wcout << obec->toString() << L"\n";
						}
					}
				}
			}
			break;
		}

		delete compositeFilter;
		delete filterMaker;

	}

	int getEdTypeFromUser()
	{
		int educationType;
		std::wcout << "\n";
		std::wcout << L"Zadajte typ vzdelania: " << "\n";
		std::wcout << L"0. bez ukončeného vzdelania – osoby vo veku 0-14 rokov" << L"\n";
		std::wcout << L"1. základné vzdelanie" << L"\n";
		std::wcout << L"2. stredné odborné (učňovské) vzdelanie (bez maturity)" << L"\n";
		std::wcout << L"3. úplné stredné vzdelanie (s maturitou)" << L"\n";
		std::wcout << L"4. vyššie odborné vzdelanie" << L"\n";
		std::wcout << L"5. vysokoškolské vzdelanie" << L"\n";
		std::wcout << L"6. bez školského vzdelania – osoby vo veku 15 rokov a viac" << L"\n";
		std::wcout << L"7. nezistené" << L"\n";

		std::wcin >> educationType;
		return educationType;
	}

	bool sortByAscending()
	{
		int input;
		std::wcout << L"Ako chcete zoradiť? " << L"\n";
		std::wcout << L"1. vzostupne" << L"\n";
		std::wcout << L"2. zostupne" << L"\n";
		std::wcin >> input;

		return input == 1;
	}

	void functionality2()
	{
		FilterMakerUI* filterMaker = new FilterMakerUI(data_);
		CompositeFilter<TerritorialUnit>* compositeFilter = filterMaker->makeCompositeFilterForSorting();

		structures::UnsortedSequenceTable<std::wstring, TerritorialUnit*>* filteredTerritorialUnits = new structures::UnsortedSequenceTable<std::wstring, TerritorialUnit*>();
		filterTerritorialUnitsIntoTable(filteredTerritorialUnits, compositeFilter);


		std::wcout << L"Podľa čoho sa majú zoradiť? " << L"\n";
		std::wcout << L"1. Názov " << L"\n";
		std::wcout << L"2. Počet obyvatelov s daným typom vzdelania" << L"\n";
		std::wcout << L"3. Podiel obyvatelov s daným typom vzdelania " << L"\n";
		int choice;
		std::wcin >> choice;
		switch (choice) {
		case 1:
		{
			CriterionTUName* criterion = new CriterionTUName();
			Sorter<std::wstring>* sorter = new Sorter<std::wstring>();
			sorter->sort(*filteredTerritorialUnits, *criterion, sortByAscending());
			for (auto item : *filteredTerritorialUnits) {
				//std::wcout << item->getKey() << L"\n";
				std::wcout << item->accessData()->toString() << L"\n";
				
			}
			delete sorter;
			delete criterion;
			break;
		}
		case 2:
		{
			CriterionTUEducationCount* criterion = new CriterionTUEducationCount(getEdTypeFromUser());
			Sorter<int>* sorter = new Sorter<int>();
			sorter->sort(*filteredTerritorialUnits, *criterion, sortByAscending());
			for (auto item : *filteredTerritorialUnits) 
			{
				//std::wcout << item->getKey() << L"\n";
				std::wcout << item->accessData()->toString() << L"\n";
			}
			delete sorter;
			delete criterion;
			break;
		}
		case 3:
		{
			CriterionTUEducationRatio* criterion = new CriterionTUEducationRatio(getEdTypeFromUser());
			Sorter<double>* sorter = new Sorter<double>();
			sorter->sort(*filteredTerritorialUnits, *criterion, sortByAscending());
			for (auto item : *filteredTerritorialUnits) 
			{
				//std::wcout << item->getKey() << L"\n";
				std::wcout << item->accessData()->toString() << L"\n";
			}
			delete sorter;
			delete criterion;
			break;
		}
		}

		delete compositeFilter;
		delete filteredTerritorialUnits; // TerritorialUnits sa do tabulky len indexuju, netreba mazat itemy
		delete filterMaker;
	}

	void filterTerritorialUnitsIntoTable(structures::UnsortedSequenceTable<std::wstring, TerritorialUnit*>*  filteredTerritorialUnits, CompositeFilter<TerritorialUnit>*  compositeFilter)
	{
		int input;
		std::wcout << L"\n";
		std::wcout << L"1. filtrovanie AND (územná jednotka musí prejsť každým filtrom)" << L"\n";
		std::wcout << L"2. filtrovanie OR (stačí aby územná jednotka prešla aspoň 1 filtrom)" << L"\n";

		std::wcin >> input;

		switch (input)
		{
		case 1:
			// pridanie aj statu
			/*if(compositeFilter->passFilter_AND(*data_->getStat()))
			{
				filteredTerritorialUnits->insert(data_->getStat()->getName(), data_->getStat());
			}*/

			for (auto krajItem : data_->getStat()->getChildren())
			{
				TerritorialUnit* kraj = krajItem->accessData();
				if (compositeFilter->passFilter_AND(*kraj))
				{
					filteredTerritorialUnits->insert(krajItem->getKey(), krajItem->accessData());
				}
				for (auto okresItem : kraj->getChildren())
				{
					TerritorialUnit* okres = okresItem->accessData();
					if (compositeFilter->passFilter_AND(*okres))
					{
						filteredTerritorialUnits->insert(okresItem->getKey(), okresItem->accessData());
					}
					for (auto obecItem : okres->getChildren())
					{
						TerritorialUnit* obec = obecItem->accessData();
						if (compositeFilter->passFilter_AND(*obec))
						{
							filteredTerritorialUnits->insert(obecItem->getKey(), obecItem->accessData());
						}
					}
				}
			}
			break;
		case 2:
			// pridanie aj statu
			/*if(compositeFilter->passFilter_OR(*data_->getStat()))
			{
				filteredTerritorialUnits->insert(data_->getStat()->getName(), data_->getStat());
			}*/

			for (auto krajItem : data_->getStat()->getChildren())
			{
				TerritorialUnit* kraj = krajItem->accessData();
				if (compositeFilter->passFilter_OR(*kraj))
				{
					filteredTerritorialUnits->insert(krajItem->getKey(), krajItem->accessData());
				}
				for (auto okresItem : kraj->getChildren())
				{
					TerritorialUnit* okres = okresItem->accessData();
					if (compositeFilter->passFilter_OR(*okres))
					{
						filteredTerritorialUnits->insert(okresItem->getKey(), okresItem->accessData());
					}
					for (auto obecItem : okres->getChildren())
					{
						TerritorialUnit* obec = obecItem->accessData();
						if (compositeFilter->passFilter_OR(*obec))
						{
							filteredTerritorialUnits->insert(obecItem->getKey(), obecItem->accessData());
						}
					}
				}
			}
			break;
		}
	}
};

