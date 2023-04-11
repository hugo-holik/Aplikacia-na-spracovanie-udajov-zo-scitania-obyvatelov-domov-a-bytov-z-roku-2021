#include "heap_monitor.h"
#include <Windows.h>
//#include <iomanip>
#include <clocale>
#include <codecvt>

#include "Data.h"
#include <functional>
#include <iomanip>
#include <iostream>

#include "CompositeFilter.h"
#include "Stat.h"
#include "FilterTU.h"
#include "UserInterface.h"

using namespace std;

int main()
{
	initHeapMonitor();
	locale::global(locale("slovak"));
	SetConsoleCP(1250);
	SetConsoleOutputCP(1250);

	Stat* slovensko = new Stat(L"Slovensko", L"SK");
	Data* data = new Data(slovensko);
	data->loadDataFromFile("data\\vzdelanie2.csv", "data\\okresy2.csv", "data\\kraje2.csv");




	UserInterface* ui = new UserInterface(data);
	delete ui;

	delete data;

	return 0;
}
