#include "Data.h"

#include <codecvt>
#include <fstream>
#include <iostream>
#include <sstream>
#include <Windows.h>

#include "Kraj.h"
#include "Obec.h"
#include "Okres.h"
#include "structures/array/array.h"


// class Data

Data::Data(Stat* stat)
{
	stat_ = stat;
}

Data::~Data()
{
	delete stat_;
	stat_ = nullptr;
}

void Data::loadDataFromFile(std::string filenameObec, std::string filenameOkres, std::string filenameKraj)
{
	dataLoader* dataLoader = new ::dataLoader(stat_, filenameObec, filenameOkres, filenameKraj);
	delete dataLoader;
}

Stat* Data::getStat()
{
	return stat_;
}



// class dataLoader

dataLoader::dataLoader(Stat* stat, std::string filenameObec, std::string filenameOkres, std::string filenameKraj)
{
	std::wifstream fileObec(filenameObec);
	std::wifstream fileOkres(filenameOkres);
	std::wifstream fileKraj(filenameKraj);

	std::wstring krajLine;
	std::getline(fileKraj, krajLine); //skip hlavicky
	while (std::getline(fileKraj, krajLine))
	{
		Kraj* newKraj = loadKrajFromString(krajLine);
		newKraj->setParent(stat);
		stat->insertChild(newKraj);
	}

	

	std::wstring okresLine;
	std::getline(fileOkres, okresLine); //skip hlavicky
	while (std::getline(fileOkres, okresLine))
	{
		Okres* newOkres = loadOkresFromString(okresLine);
		bool prislucha = false;

		for (auto krajTableItem : stat->getChildren()) //prehladam kraje, nastavim okresu parenta(kraj) do ktoreho prislucha
		{
			TerritorialUnit* kraj = krajTableItem->accessData();
			if (kraj->getCode() == newOkres->getCode().substr(0, 5))
			{
				prislucha = true;
				newOkres->setParent(kraj);
				kraj->insertChild(newOkres);
			}
		}

		if (prislucha == false)
		{
			std::wcout << newOkres->getName() << newOkres->getCode() << L"\n";
			delete newOkres;
		}
	}

	std::wstring obecLine; // - sem getLine hadze zo streamu
	std::getline(fileObec, obecLine); //skip hlavicky
	while (std::getline(fileObec, obecLine))
	{
		Obec* newObec = loadObecFromString(obecLine);
		//bool prislucha = false;

		for (auto krajTableItem : stat->getChildren()) //v kazdom kraji prejdem okresy
		{

			TerritorialUnit* kraj = krajTableItem->accessData();
			for (auto okresTableItem : kraj->getChildren()) // prehladam okresy, nastavujem parentov(okresy) obciam
			{
				TerritorialUnit* okres = okresTableItem->accessData();
				if (okres->getCode() == newObec->getCode().substr(0, 6))
				{
					//prislucha = true;
					newObec->setParent(okres);
					okres->insertChild(newObec);

					//priscitovanie poctov ludi do okresu a kraju obce
					for (int i = 0; i < 8; i++)
					{
						int countInObec = newObec->getEducationCount(i);
						int countInOkres = okres->getEducationCount(i);
						int countInKraj = kraj->getEducationCount(i);
						okres->setEducationCount(i, countInOkres + countInObec);
						kraj->setEducationCount(i, countInKraj + countInObec);
					}
				}
			}

		}

		
	}
}

Obec* dataLoader::loadObecFromString(std::wstring line)
{
	std::wstring code;
	std::wstring name;
	std::wstring countStr;
	structures::Array<int>* educationCount = new structures::Array<int>(8);

	std::wstring skipped; //preskocene (useless) stringy
	std::wistringstream lineStream(line);


	getline(lineStream, code, L';');
	getline(lineStream, name, L';');
	for (int i = 0; i < 8; i++)
	{
		getline(lineStream, countStr, L';');
		educationCount->at(i) = stoi(countStr);
	}

	
	Obec* newObec = new Obec(name, code);
	//nacitanie data o vzdelani
	for (int i = 0; i < educationCount->size(); i++)
	{
		newObec->setEducationCount(i, educationCount->at(i));
	}

	//std::wcout << code << L" " << name << L"\n";

	delete educationCount;
	return newObec;
}

Okres* dataLoader::loadOkresFromString(std::wstring line)
{
	std::wstring code;
	std::wstring name;

	std::wstring skipped; //preskocene (useless) stringy
	std::wistringstream lineStream(line);


	getline(lineStream, skipped, L';');
	getline(lineStream, code, L';');
	getline(lineStream, skipped, L';');
	getline(lineStream, name, L';');
	getline(lineStream, skipped, L';');
	getline(lineStream, skipped, L';');

	//std::wcout << code << L" " << name << L"\n";

	return new Okres(name, code);
}

Kraj* dataLoader::loadKrajFromString(std::wstring line)
{
	std::wstring code;
	std::wstring name;

	std::wstring skipped; //preskocene (useless) stringy
	std::wistringstream lineStream(line);


	getline(lineStream, skipped, L';');
	getline(lineStream, skipped, L';');
	getline(lineStream, name, L';');
	getline(lineStream, skipped, L';');
	getline(lineStream, skipped, L';');
	getline(lineStream, code, L';');

	if (code.length() >= 5 + 5)
	{
		code = code.substr(5, 5); //orezanie stringu - vysledkom je kod kraja
	}

	//std::wcout << code << L" " << name << L"\n";
	return new Kraj(name, code);
}


