#pragma once

#include "priority_queue_list.h"
#include "../list/array_list.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Prioritny front implementovany utriednym ArrayList-om. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prioritnom fronte. </typepram>
	template<typename T>
	class PriorityQueueSortedArrayList : public PriorityQueueList<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		PriorityQueueSortedArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prioritny front implementovany utriednym ArrayList-om, z ktoreho sa prevezmu vlastnosti. </param>
		PriorityQueueSortedArrayList(PriorityQueueSortedArrayList<T>& other);

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Vlozi prvok s danou prioritou do prioritneho frontu implementovaneho utriednym ArrayList-om. </summary>
		/// <param name = "priority"> Priorita vkladaneho prvku. </param>
		/// <param name = "data"> Vkladany prvok. </param>
		void push(int priority, const T& data) override;

	protected:
		/// <summary> Vrati index v utriedenom ArrayList-e, na ktorom sa nachadza prvok s najvacsou prioritou. </summary>
		/// <returns> Index prvku s najvacsou prioritou. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak je zoznam prazdny. </exception>
		int indexOfPeek() override;
	};

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList() :
		PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>())
	{
	}

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList(PriorityQueueSortedArrayList<T>& other) :
		PriorityQueueSortedArrayList<T>()
	{
		assign(other);
	}

	template<typename T>
	inline Structure& PriorityQueueSortedArrayList<T>::assign(Structure& other)
	{
		return PriorityQueueList<T>::assignPrioQueueList(dynamic_cast<PriorityQueueList<T>&>(other)); 
	}

	template<typename T>
	inline void PriorityQueueSortedArrayList<T>::push(int priority, const T& data)
	{
		//hladanie indexu metodou bisekcie

		PriorityQueueItem<T>* item = new PriorityQueueItem<T>(priority, data);
		int leftIndex = 0;
		int rightIndex = PriorityQueueList<T>::size();
		while (leftIndex < rightIndex)
		{
			int middleIndex = leftIndex + ((rightIndex - leftIndex) / 2);
			if (priority < PriorityQueueList<T>::list_->at(middleIndex)->getPriority())
			{
				leftIndex = middleIndex + 1;
			}
			else
			{
				rightIndex = middleIndex;
			}
		}
		PriorityQueueList<T>::list_->insert(item, leftIndex);



		// hladanie for eachom

		//if (PriorityQueueList<T>::list_->size() == 0) 
		//{
		//	PriorityQueueList<T>::list_->add(new PriorityQueueItem<T>(priority, data));
		//	return;
		//}
		//else 
		//{
		//	if (priority >= PriorityQueueList<T>::list_->at(0)->getPriority()) 
		//	{
		//		PriorityQueueList<T>::list_->insert(new PriorityQueueItem<T>(priority, data), 0);
		//		return;
		//	}
		//	if (priority <= PriorityQueueList<T>::peekPriority()) 
		//	{
		//		PriorityQueueList<T>::list_->add(new PriorityQueueItem<T>(priority, data));
		//		return;
		//	}

		//	int index = 0;
		//	for (size_t i = 0; i < PriorityQueueList<T>::list_->size(); i++)
		//	{
		//		if (PriorityQueueList<T>::list_->at(i)->getPriority() >= priority)
		//		{
		//			index = i;
		//		}
		//	}

		//	PriorityQueueList<T>::list_->insert(new PriorityQueueItem<T>(priority, data), index);
		//}
	}

	template<typename T>
	inline int PriorityQueueSortedArrayList<T>::indexOfPeek()
	{
		if (PriorityQueueList<T>::size() == 0)
		{
			throw std::logic_error("Queue is empty!");
		}

		//z konca sa maze v arrayliste O(1), inde O(n) .. preto je najv. priorita na konci
		return PriorityQueueList<T>::size() - 1;
	}
}