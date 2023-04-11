#pragma once

#include "priority_queue.h"
#include "priority_queue_limited_sorted_array_list.h"
#include "../list/linked_list.h"
#include "../list/double_linked_list.h"
#include <cmath>
#include <iostream>
#include <fstream>

namespace structures
{
	/// <summary> Prioritny front implementovany dvojzoznamom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	/// <remarks> Implementacia efektivne vyuziva prioritny front implementovany utriednym ArrayList-om s obmedzenou kapacitou a LinkedList. </remarks>
	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueTwoLists();

		PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vrati pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </summary>
		/// <returns> Pocet prvkov v prioritnom fronte implementovanom dvojzoznamom. </returns>
		size_t size() override;

		/// <summary> Vymaze obsah prioritneho frontu implementovaneho dvojzoznamom. </summary>
		void clear() override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

		/// <summary> Odstrani prvok s najvacsou prioritou z prioritneho frontu implementovaneho dvojzoznamom. </summary>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T pop() override;

		/// <summary> Vrati adresou prvok s najvacsou prioritou. </summary>
		/// <returns> Adresa, na ktorej sa nachadza prvok s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		T& peek() override;

		/// <summary> Vrati prioritu prvku s najvacsou prioritou. </summary>
		/// <returns> Priorita prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je prioritny front implementovany dvojzoznamom prazdny. </exception>
		int peekPriority() override;

	private:
		/// <summary> Smernik na prioritny front ako implementovany utriednym ArrayList-om s obmedzenou kapacitou . </summary>
		/// <remarks> Z pohladu dvojzoznamu sa jedna o kratsi utriedeny zoznam. </remarks>
		PriorityQueueLimitedSortedArrayList<T>* shortList_;

		/// <summary> Smernik na dlhsi neutriedeny zoznam. </summary>
		LinkedList<PriorityQueueItem<T>*>* longList_;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists() :
		shortList_(new PriorityQueueLimitedSortedArrayList<T>()),
		longList_(new LinkedList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(PriorityQueueTwoLists<T>& other) :
		PriorityQueueTwoLists<T>()
	{
		assign(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists()
	{
		clear();
		delete shortList_;
		delete longList_;
		shortList_ = nullptr;
		longList_ = nullptr;
	}

	template<typename T>
	Structure& PriorityQueueTwoLists<T>::assign(Structure& other)
	{
		if (this == &other)
		{
			return *this;
		}

		PriorityQueueTwoLists<T>& otherPQTL = dynamic_cast<PriorityQueueTwoLists<T>&>(other);

		clear();

		shortList_->assign(*otherPQTL.shortList_);
		// longList_->assign(*otherPQTL.longList_);		-> toto nesmies, spravil by si shallow copy
		// a ked mas shallow copy, tak by prvky (longListItem<T>*) otherPQTL.longList_ aj this->longList_ ukazovali na tie iste miesta
		// a napriklad po zruseni otherPQTL.longList_ by sa prvky deletli prvykrat a po zruseni this->longList_ by sa deletli druhykrat
		// cim by si sa snazil deletnut uz neexistujuce objekty -> runtime error
		for (PriorityQueueItem<T>* item : *otherPQTL.longList_)
		{
			longList_->add(new PriorityQueueItem<T>(item->accessData(), item->accessData()));
		}

		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size()
	{
		return shortList_->size() + longList_->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear()
	{
		shortList_->clear();

		for (PriorityQueueItem<T>* item : *longList_)
		{
			delete item;
		}
		longList_->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(int priority, const T& data)
	{

		if (shortList_->size() == 0 || priority < shortList_->minPriority()) // podmienka shortList_->size() == 0 je kvoli tomu, ze ak posles spravu shortList_->minPriority() a shortlist je prazdny, tak ti vyhodi vynimku "Queue is empty!"
		{
			auto removed = shortList_->pushAndRemove(priority, data);
			if (removed != nullptr) // ak este neni plny shortlist, tak removed bude nullptr -> nic sa z neho neodstranilo
			{
				longList_->add(removed); // ak bol shortlist plny, tak sa z neho odstrani prvok z najmensou prioritou a addne sa do longlistu
			}
		}
		else
		{
			PriorityQueueItem<T>* newItem = new PriorityQueueItem<T>(priority, data);
			longList_->add(newItem);
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop()
	{

		if (size() == 0)
		{
			throw std::logic_error("Queue is empty!");
		}

		T popped;
		bool isAlreadyPopped = false;
		if (shortList_->size() != 0)
		{
			popped = shortList_->pop();
			isAlreadyPopped = true;
		}

		// restrukturalizacia
		if (shortList_->size() == 0 && longList_->size() != 0)
		{

			// shortList velkost bude odmocnina z longList velkosti, ale nebude mensia ako 4
			int newShortListCapacity = sqrt(longList_->size());
			if (newShortListCapacity < 4)
			{
				newShortListCapacity = 4;
			}
			shortList_->trySetCapacity(newShortListCapacity);

			LinkedList<PriorityQueueItem<T>*>* tempList = new LinkedList<PriorityQueueItem<T>*>();
			tempList->assign(*longList_);
			//for (PriorityQueueItem<T>* item : *longList_)
			//{
			//	tempList->add(item);
			//	file << "item {" << item->getPriority() << "}" << "\n";
			//}

			longList_->clear(); 

			for (PriorityQueueItem<T>* item : *tempList)
			{
				if (shortList_->size() == 0 || item->getPriority() < shortList_->minPriority()) //toto kvoli pushAndRemove
				{
					auto removed = shortList_->pushAndRemove(item->getPriority(), item->accessData());
					

					delete item; // pushAndRemove si berie len item->getPriority(), item->accessData() ... takze item treba zahodit
					if (removed != nullptr) // ak este neni plny shortlist, tak removed bude nullptr -> nic sa z neho neodstranilo
					{
						longList_->add(removed);
					}
				}
				else
				{
					longList_->add(item);
				}
			}
			delete tempList;
		}

		if (isAlreadyPopped)
		{
			return popped;
		}
		else
		{
			return shortList_->pop();
		}
	}

	template<typename T>
	T& PriorityQueueTwoLists<T>::peek()
	{
		if (size() == 0)
		{
			throw std::logic_error("Queue is empty!");
		}

		return shortList_->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority()
	{
		return shortList_->peekPriority();
	}
}
