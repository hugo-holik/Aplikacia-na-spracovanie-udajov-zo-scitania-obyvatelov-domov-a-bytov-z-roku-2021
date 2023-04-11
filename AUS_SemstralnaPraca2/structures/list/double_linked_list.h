#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include "../utils.h"
#include "../heap_monitor.h"

namespace structures
{
    /// <summary> Prvok dvojstranne zretazeneho zoznamu. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    template<typename T>
    class DoubleLinkedListItem : public DataItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        DoubleLinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok dvojstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        DoubleLinkedListItem(DoubleLinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        DoubleLinkedListItem<T>* getNext();

        /// <summary> Getter predchadzajuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Predchadzajuci prvok zretazeneho zoznamu. </returns>
        DoubleLinkedListItem<T>* getPrevious();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setNext(DoubleLinkedListItem<T>* next);

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name´= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setPrevious(DoubleLinkedListItem<T>* previous);

    private:
        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        DoubleLinkedListItem<T>* next_;
        /// <summary> Predchadzajuci prvok zretazeneho zoznamu. </summary>
        DoubleLinkedListItem<T>* previous_;
    };

	// implementacne tipy: 
	//  - namiesto triedy List<T> mozete v triede DoubleLinkedList<T> 
	//    zdedit jednostranne zretazeny zoznam (LinkedList<T>).
	//    ak tak urobite, mozete mnoho metod odstranit a prekryt iba tie, 
	//    ktore maju z pohladu obojsmerne zretazeneho zoznamu vyznam a
	//    zvysok nechat na predka.
	//  - nezabudnite si vytvorit triedu pre prvok obojstranne zretazeneho zoznamu.
	//    opat tento prvok mozete zdedit z prvku jednostranne zretazeneho zoznamu.
	//  - ak vyuzijete dedicnost, budete moct vyuzit predkove iteratory, 
	//    takze ich nebudete musiet implementovat.
	
    /// <summary> Obojstranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class DoubleLinkedList : public List<T> 
	{
    public:
        /// <summary> Konstruktor. </summary>
        DoubleLinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> DoubleLinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        DoubleLinkedList(DoubleLinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~DoubleLinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;

    private:
        /// <summary> Pocet prvkov v zozname. </summary>
        size_t size_;
        /// <summary> Prvy prvok zoznamu. </summary>
        DoubleLinkedListItem<T>* first_;
        /// <summary> Posledny prvok zoznamu. </summary>
        DoubleLinkedListItem<T>* last_;

    private:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </summary>
        /// <returns> Prvok zoznamu na danom indexe. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        DoubleLinkedListItem<T>* getItemAtIndex(int index);

    private:
        /// <summary> Iterator pre DoubleLinkedList. </summary>
        class DoubleLinkedListIterator : public Iterator<T>
        {
        public:
            /// <summary> Konstruktor. </summary>
            /// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
            DoubleLinkedListIterator(DoubleLinkedListItem<T>* position);

            /// <summary> Destruktor. </summary>
            ~DoubleLinkedListIterator();

            /// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> Vrati seba po priradeni. </returns>
            Iterator<T>& operator= (Iterator<T>& other) override;

            /// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
            bool operator!=(Iterator<T>& other) override;

            /// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
            /// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
            T operator*() override;

            /// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
            /// <returns> Iterator na dalsi prvok v strukture. </returns>
            /// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
            Iterator<T>& operator++() override;

        private:
            /// <summary> Aktualna pozicia v zozname. </summary>
            DoubleLinkedListItem<T>* position_;
        };
	};

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(T data) :
        DataItem<T>(data),
        next_(nullptr),
		previous_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::DoubleLinkedListItem(DoubleLinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_),
		previous_(other.previous_)
    {
    }

    template<typename T>
    inline DoubleLinkedListItem<T>::~DoubleLinkedListItem()
    {
        next_ = nullptr;
        previous_ = nullptr;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getNext()
    {
        return next_;
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedListItem<T>::getPrevious()
    {
        return previous_;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setNext(DoubleLinkedListItem<T>* next)
    {
        next_ = next;
    }

    template<typename T>
    inline void DoubleLinkedListItem<T>::setPrevious(DoubleLinkedListItem<T>* previous)
    {
        previous_ = previous;
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList() :
        size_(0),
        first_(nullptr),
        last_(nullptr)
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList<T>& other) :
        DoubleLinkedList()
    {
        assign(other);
    }

    template<typename T>
    inline DoubleLinkedList<T>::~DoubleLinkedList()
    {
        clear();
    }

    template<typename T>
    inline size_t DoubleLinkedList<T>::size()
    {
        return size_;
    }

    template<typename T>
    inline Structure& DoubleLinkedList<T>::assign(Structure& other)
    {
        if (this != &other)
        {
            DoubleLinkedList<T>& otherLL = dynamic_cast<DoubleLinkedList<T>&>(other);
            //vymazem seba, a postupne do seba z other napcham prvky
            clear();
            for (T data : otherLL)
            {
	            add(data);
            }
        }
        return *this;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::equals(Structure& other)
    {
        if (this == &other)
        {
            return true;
        }

        DoubleLinkedList<T>* otherLL = dynamic_cast<DoubleLinkedList<T>*>(&other);
        if (otherLL == nullptr) // ak sa nepodaril cast -> tak tam bude nullptr
        {
            return false;
        }
        if (size_ != otherLL->size_)
        {
            return false;
        }

        DoubleLinkedListItem<T>* currentThis = first_;
        for (T otherData : *otherLL)
        {
            if (currentThis->accessData() != otherData)
            {
                return false;
            }
            currentThis = currentThis->getNext();
        }
        return true;
    }

    template<typename T>
    inline T& DoubleLinkedList<T>::at(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index!");
        return getItemAtIndex(index)->accessData();
    }

    template<typename T>
    inline void DoubleLinkedList<T>::add(const T& data)
    {
        DoubleLinkedListItem<T>* newDLLI = new DoubleLinkedListItem<T>(data);
        if (size_ == 0)
        {
            first_ = newDLLI;
        }
        else
        {
            last_->setNext(newDLLI);
            newDLLI->setPrevious(last_);
        }
        last_ = newDLLI;
        size_++;
    }

    template<typename T>
    inline void DoubleLinkedList<T>::insert(const T& data, int index)
    {
        //if (index == size_)
        //{
        //    add(data);
        //}
        //else
        //{
        //    Utils::rangeCheckExcept(index, size_, "Invalid index!");
        //    LinkedListItem<T>* newLLI = new LinkedListItem<T>(data);

        //    if (index == 0)
        //    {
        //        newLLI->setNext(first_);
        //        first_ = newLLI;
        //    }
        //    else
        //    {
        //        LinkedListItem<T>* previous = getItemAtIndex(index - 1);
        //        newLLI->setNext(previous->getNext());
        //        previous->setNext(newLLI);
        //    }

        //    size_++;
        //}

        if (index == size_)
        {
            add(data);
        }
        else
        {
            Utils::rangeCheckExcept(index, size_, "Invalid index!");
            DoubleLinkedListItem<T>* newDLLI = new DoubleLinkedListItem<T>(data);

            if (index == 0)
            {
                newDLLI->setNext(first_);
                first_->setPrevious(newDLLI);
                first_ = newDLLI;
            }
            else
            {
                DoubleLinkedListItem<T>* previous = getItemAtIndex(index - 1);
                newDLLI->setNext(previous->getNext());
                previous->getNext()->setPrevious(newDLLI);
                newDLLI->setPrevious(previous);
                previous->setNext(newDLLI);
            }

            size_++;
        }
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::tryRemove(const T& data)
    {
	    int index = getIndexOf(data);
        if(index == -1)
        {
            return false;
        }
	    removeAt(index);
        return true;
    }

    template<typename T>
    inline T DoubleLinkedList<T>::removeAt(int index)
    {
        //LinkedListItem<T>* delItem;

        //if (size_ == 1)
        //{
        //    delItem = first_;
        //    first_ = nullptr;
        //    last_ = nullptr;
        //}
        //else
        //{
        //    Utils::rangeCheckExcept(index, size_, "Invalid index!");
        //    if (index == 0)
        //    {
        //        delItem = first_;
        //        first_ = first_->getNext();
        //    }
        //    else
        //    {
        //        LinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
        //        LinkedListItem<T>* nextItem = prevItem->getNext()->getNext();
        //        delItem = prevItem->getNext();
        //        prevItem->setNext(nextItem);
        //        if (nextItem == nullptr)
        //        {
        //            last_ = prevItem;
        //        }
        //    }
        //}
        //size_--;
        //T result = delItem->accessData();
        //delete delItem;
        //return result;

        DoubleLinkedListItem<T>* delItem;

        if (size_ == 1)
        {
            delItem = first_;
            first_ = nullptr;
            last_ = nullptr;
        }
        else
        {
            Utils::rangeCheckExcept(index, size_, "Invalid index!");
            if (index == 0)
            {
                delItem = first_;
                first_ = first_->getNext();
            }
            else if (index == size_ - 1) //posledny prvok
            {
                delItem = last_;
                last_ = last_->getPrevious();
                last_->setNext(nullptr);
            }
            else
            {
                DoubleLinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
                DoubleLinkedListItem<T>* nextItem = prevItem->getNext()->getNext();
                delItem = prevItem->getNext();
                prevItem->setNext(nextItem);
                nextItem->setPrevious(prevItem); //nextItem nikdy nebude nullptr, lebo hore else if podmienka zabezpecuje mazanie posl prvku
            }
        }
        size_--;
        T result = delItem->accessData();
        delete delItem;
        return result;
    }

    template<typename T>
    inline int DoubleLinkedList<T>::getIndexOf(const T& data)
    {
        DoubleLinkedListItem<T>* current = first_;
        for (int i = 0; i < size_; i++)
        {
            if (current->accessData() == data)
            {
                return i;
            }
            current = current->getNext();
        }
        return -1;

    }

    template<typename T>
    inline void DoubleLinkedList<T>::clear()
    {
        // postupne rusim prvky od zaciatku listu az dokym first_ neni nullptr
        DoubleLinkedListItem<T>* current = first_;

        int testIndex = 0;
        while (first_ != nullptr)
        {
            first_ = current->getNext();
            delete current;
            current = first_;
            testIndex++;
        }

        last_ = nullptr;
        size_ = 0;
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getBeginIterator()
    {
        return new DoubleLinkedListIterator(first_);
    }

    template<typename T>
    inline Iterator<T>* DoubleLinkedList<T>::getEndIterator()
    {
        return new DoubleLinkedListIterator(nullptr);
    }

    template<typename T>
    inline DoubleLinkedListItem<T>* DoubleLinkedList<T>::getItemAtIndex(int index)
    {
        //if (index == size_ - 1) //posledny prvok
        //{
        //    return last_;
        //}

        //LinkedListItem<T>* current = first_;
        //for (int i = 0; i < index; i++)
        //{
        //    current = current->getNext();
        //}

        //return current;

        DoubleLinkedListItem<T>* current;

        if (index < size_ / 2)
        {
            current = first_;
            for (int i = 0; i < index; i++)
			{
			    current = current->getNext();
			}
        }
        else
        {
            current = last_;
            for (int i = 0; i < (size_ - 1) - index; i++) // ekvivalent: for (int i = (size_ - 1); i > index; i--)
            {
                current = current->getPrevious();
            }
        }
        return current;
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedListIterator::DoubleLinkedListIterator(DoubleLinkedListItem<T>* position) :
        position_(position)
    {
    }

    template<typename T>
    inline DoubleLinkedList<T>::DoubleLinkedListIterator::~DoubleLinkedListIterator()
    {
        position_ = nullptr;
    }

    template<typename T>
    inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator=(Iterator<T>& other)
    {
        if (this != &other)
        {
            DoubleLinkedListIterator& otherIterator = dynamic_cast<DoubleLinkedListIterator&>(other);   // pretypovanie cez referencie -> ak sa pretypovanie nepodari, nema zmysel robit priradenie -> dynamiccast vyhodi vynimku
            position_ = otherIterator.position_;
        }
        return *this;
    }

    template<typename T>
    inline bool DoubleLinkedList<T>::DoubleLinkedListIterator::operator!=(Iterator<T>& other)
    {
        DoubleLinkedListIterator* otherIterator = dynamic_cast<DoubleLinkedListIterator*>(&other);
        return otherIterator == nullptr || position_ != otherIterator->position_;
    }

    template<typename T>
    inline T DoubleLinkedList<T>::DoubleLinkedListIterator::operator*()
    {
        return position_->accessData();
    }

    template<typename T>
    inline Iterator<T>& DoubleLinkedList<T>::DoubleLinkedListIterator::operator++()
    {
        position_ = position_->getNext();
        return *this;
    }
}