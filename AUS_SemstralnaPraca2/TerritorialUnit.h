#pragma once
#include <iomanip>
#include <sstream>
#include <string>
#include "heap_monitor.h"

#include "structures/array/array.h"
#include "structures/table/sorted_sequence_table.h"

class TerritorialUnit
{
public:
	enum class TerritorialUnitType
	{
		Stat,
		Kraj,
		Okres,
		Obec
	};

protected:
	std::wstring name_;
	std::wstring code_;
	TerritorialUnitType type_;
	structures::Array<int>* educationCount_;

	TerritorialUnit* parent_;
	structures::SortedSequenceTable<std::wstring, TerritorialUnit*>* children_;

public:
	TerritorialUnit(std::wstring name, std::wstring code, TerritorialUnitType type) :
		name_(name),
		code_(code),
		type_(type),
		educationCount_(new structures::Array<int>(8)),
		children_(new structures::SortedSequenceTable<std::wstring, TerritorialUnit*>),
		parent_(nullptr)
	{
	}

	~TerritorialUnit()
	{
		delete educationCount_;
		educationCount_ = nullptr;

		for (auto tableItem : *children_)
		{
			delete tableItem->accessData();
			tableItem = nullptr;
		}
		delete children_;
		children_ = nullptr;
	}

	void setEducationCount(int type, int count)
	{
		structures::Utils::rangeCheckExcept(type, educationCount_->size(), "this type of education doesnt exist!");
		educationCount_->at(type) = count;
	}

	int getEducationCount(int type)
	{
		structures::Utils::rangeCheckExcept(type, educationCount_->size(), "this type of education doesnt exist!");
		return educationCount_->at(type);
	}

	std::wstring getName()
	{
		return name_;
	}

	std::wstring getCode()
	{
		return code_;
	}

	structures::SortedSequenceTable<std::wstring, TerritorialUnit*>& getChildren()
	{
		return *children_;
	}

	void insertChild(TerritorialUnit* child)
	{
		children_->insert(child->getName(), child);
	}

	TerritorialUnit* getParent()
	{
		return parent_;
	}

	void setParent(TerritorialUnit* parent)
	{
		parent_ = parent;
	}

	TerritorialUnitType getType()
	{
		return type_;
	}

	bool isMemberOf(TerritorialUnit& territorialUnit)
	{
		//pripad ci patri do statu
		if (territorialUnit.getType() == TerritorialUnitType::Stat) 
		{
			if (type_ != TerritorialUnitType::Stat)
			{
				return true;
			}
		}

		if (type_ == TerritorialUnitType::Okres)
		{
			if (parent_ == &territorialUnit) //patri do kraja?
			{
				return true;
			}
		}

		if (type_ == TerritorialUnitType::Obec)
		{
			if (parent_ == &territorialUnit) //patri do okresu?
			{
				return true;
			}
			else if (parent_->getParent() == &territorialUnit) //patri do kraja?
			{
				return true;
			}
		}

		return false;
	}

	double educationRatio(int educationType) 
	{
		double sum = 0.0;
		for (int i = 0; i < educationCount_->size(); i++)
		{
			sum += getEducationCount(i);
		}

		double ratio = ( getEducationCount(educationType) / sum) * 100.0;

		return ratio;
	}



	virtual std::wstring toString()
	{
		std::wstringstream stream;

		int peopleCount = 0;
		for (int i = 0; i < educationCount_->size(); i++)
		{
			peopleCount += educationCount_->at(i);
		}

		stream << L"Počet obyvateľov: " << peopleCount << L"\n";

		for (int i = 0; i < educationCount_->size(); i++)
		{
			stream << L"počet ľudí s typom vzdelania " << i << L": " << getEducationCount(i) << L" (" << std::setprecision(2) << educationRatio(i) << L"%)" << L"\n";
		}

		return stream.str();
	}

	
};
