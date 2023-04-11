#pragma once
#include <string>
#include "heap_monitor.h"

#include "Kraj.h"
#include "Obec.h"
#include "Okres.h"
#include "Stat.h"

class Data
{
private:
	Stat* stat_;

public:
	Data(Stat* stat);
	~Data();
	void loadDataFromFile(std::string filenameObec, std::string filenameOkres, std::string filenameKraj);
	Stat* getStat();
};

class dataLoader
{
private:
	std::string filenameObec_;
	std::string filenameOkres_;
	std::string filenameKraj_;
public:
	dataLoader(Stat* stat, std::string filenameObec, std::string filenameOkres, std::string filenameKraj);
	Obec* loadObecFromString(std::wstring line);
	Kraj* loadKrajFromString(std::wstring line);
	Okres* loadOkresFromString(std::wstring line);
};
