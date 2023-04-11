#pragma once
#include <iostream>

#include "heap_monitor.h"

#include "CompositeFilter.h"
#include "Data.h"
#include "FilterTU.h"
#include "TerritorialUnit.h"

class FilterMakerUI
{
private:
	Data* data_;

public:

	FilterMakerUI(Data* data)
	{
		data_ = data;
	}

	bool filterChoice(std::wstring filtername)
	{
		std::wcout << L"\n" << L"Aplikovať filter " << filtername << L" ?" << L"\n";
		std::wcout << L"1. Áno" << L"\n";
		std::wcout << L"2. Nie" << L"\n";

		int input;
		std::wcin >> input;
		return input == 1;
	}

	void makeFilterName(CompositeFilter<TerritorialUnit>* compositeFilter)
	{
		if (!filterChoice(L"UJNázov"))
		{
			return;
		}

		std::wstring name;
		std::wcout << L"Zadajte názov: " << L"\n";

		//std::wcin >> name;
		std::wcin >> std::ws;
		std::getline(std::wcin, name, L'\n');
		//

		compositeFilter->insertFilter(new FilterTUName(new CriterionTUName(), name));
	}

	void makeFilterType(CompositeFilter<TerritorialUnit>* compositeFilter)
	{
		if (!filterChoice(L"UJTyp"))
		{
			return;
		}

		std::wcout << L"\n" << L"Zvoľte typ územnej jednotky: " << "\n";
		std::wcout << L"\n" << L"1. Kraj" << "\n";
		std::wcout << L"\n" << L"2. Okres" << "\n";
		std::wcout << L"\n" << L"3. Obec" << "\n";

		TerritorialUnit::TerritorialUnitType type;
		int input;
		std::wcin >> input;
		switch (input)
		{
		case 1:
			type = TerritorialUnit::TerritorialUnitType::Kraj;
			break;
		case 2:
			type = TerritorialUnit::TerritorialUnitType::Okres;
			break;
		case 3:
			type = TerritorialUnit::TerritorialUnitType::Obec;
			break;
		}

		compositeFilter->insertFilter(new FilterTUType(new CriterionTUType(), type));
	}

	void makeFilterMembership(CompositeFilter<TerritorialUnit>* compositeFilter)
	{
		if (!filterChoice(L"UJPríslušnosť"))
		{
			return;
		}

		std::wcout << L"\n" << L"Zadajte územnú jednotku, do ktorej má patriť     (zadajte 'ok' ak nechcete ďalej vyberať): " << L"\n";
		

		
		TerritorialUnit* chosenTU = data_->getStat();
		std::wstring input = L"foo";

		while (chosenTU->getType() != TerritorialUnit::TerritorialUnitType::Okres && input != L"ok")
		{
			std::wcout << "\n" << "Vybraná územná jednotka: " << chosenTU->getName() << L"     (zadajte 'ok' ak nechcete ďalej vyberať)" << "\n" << "\n";

			for (auto item : chosenTU->getChildren())
			{
				std::wcout << item->accessData()->getName() << L"\n";
			}

			std::wcin >> std::ws;
			std::getline(std::wcin, input, L'\n');

			if (input != L"ok")
			{
				chosenTU = chosenTU->getChildren().find(input);
			}
		}

		compositeFilter->insertFilter(new FilterTUMembership(new CriterionTUMembership(*chosenTU), true));

	}

	void makeFilterEducationCount(CompositeFilter<TerritorialUnit>* compositeFilter)
	{
		if (!filterChoice(L"UJVzdelaniePočet"))
		{
			return;
		}

		int educationType;
		int min;
		int max;

		std::wcout << L"Zadajte typ vzdelania: " << "\n";
		printEducationTypes();
		std::wcin >> educationType;

		std::wcout << L"Zadajte minimálny počet: " << "\n";
		std::wcin >> min;

		std::wcout << L"Zadajte minimálny počet: " << "\n";
		std::wcin >> max;

		compositeFilter->insertFilter(new FilterTUEducationCount(new CriterionTUEducationCount(educationType), min, max));
	}

	void makeFilterEducationRatio(CompositeFilter<TerritorialUnit>* compositeFilter)
	{
		if (!filterChoice(L"UJVzdelaniePodiel"))
		{
			return;
		}

		int educationType;
		double min;
		double max;

		std::wcout << L"Zadajte typ vzdelania: " << "\n";
		printEducationTypes();
		std::wcin >> educationType;

		std::wcout << L"Zadajte minimálny počet: " << "\n";
		std::wcin >> min;

		std::wcout << L"Zadajte minimálny počet: " << "\n";
		std::wcin >> max;

		compositeFilter->insertFilter(new FilterTUEducationRatio(new CriterionTUEducationRatio(educationType), min, max));
	}

	void printEducationTypes()
	{
		std::wcout << L"0. bez ukončeného vzdelania – osoby vo veku 0-14 rokov" << L"\n";
		std::wcout << L"1. základné vzdelanie" << L"\n";
		std::wcout << L"2. stredné odborné (učňovské) vzdelanie (bez maturity)" << L"\n";
		std::wcout << L"3. úplné stredné vzdelanie (s maturitou)" << L"\n";
		std::wcout << L"4. vyššie odborné vzdelanie" << L"\n";
		std::wcout << L"5. vysokoškolské vzdelanie" << L"\n";
		std::wcout << L"6. bez školského vzdelania – osoby vo veku 15 rokov a viac" << L"\n";
		std::wcout << L"7. nezistené" << L"\n";
	}

	CompositeFilter<TerritorialUnit>* makeCompositeFilter()
	{
		CompositeFilter<TerritorialUnit>* compositeFilter = new CompositeFilter<TerritorialUnit>();
		makeFilterName(compositeFilter);
		makeFilterType(compositeFilter);
		makeFilterMembership(compositeFilter);
		makeFilterEducationCount(compositeFilter);
		makeFilterEducationRatio(compositeFilter);

		return compositeFilter;
		
	}

	CompositeFilter<TerritorialUnit>* makeCompositeFilterForSorting()
	{
		CompositeFilter<TerritorialUnit>* compositeFilter = new CompositeFilter<TerritorialUnit>();
		makeFilterType(compositeFilter);
		makeFilterMembership(compositeFilter);

		return compositeFilter;
	}
};

