#include "utils.h"

#include <random>
#include <stdexcept>

namespace structures
{
    void Utils::rangeCheckExcept(const int index, const size_t size, const std::string& exceptionMessage)
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range(exceptionMessage);
        }
    }

    int Utils::randomNumberInRange(const int min, const int max)
    {
        //generovanie cisla (vo vacsom range ako <0, 32767>)
        std::random_device rd;
        std::default_random_engine eng{ rd() };
        std::uniform_int_distribution<> dist(min, max);

        return dist(eng);
    }

    //Array<int>* Utils::shuffledArray(const int size)
    //{
    //    Array<int>* arr = new Array<int>(size);
    //    Array<int>* arr1 = new Array<int>(size);
    //    Array<int>* index_arr = new Array<int>(size);
    //    int index;

    //    for (int i = 0; i < size; i++)
    //    {
    //        arr->at(i) = i;
    //        index_arr->at(i) = 0;
    //    }
    //    for (int i = 0; i < size; i++) 
    //    {
    //        do 
    //        {
    //            //index = rand() % size;
    //            index = randomNumberInRange(0, size);
    //        }
    //    	while (index_arr->at(index) != 0);
    //        index_arr->at(index) = 1;
    //        arr1->at(i) = arr->at(index);
    //    }
    //    delete arr;
    //    delete index_arr;

    //    return arr1;
    //}
}