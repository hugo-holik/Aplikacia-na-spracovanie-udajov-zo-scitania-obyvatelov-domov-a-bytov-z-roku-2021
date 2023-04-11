#pragma once

#include "../structure.h"
#include "../vector/vector.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T>
	class Array : public Structure
	{
	public:
		/// <summary> Konstruktor vytvori pole o velkosti size prvkov. </summary>
		/// <param name = "size"> Pocet prvkov vo vytvorenom poli. </param>
		Array(size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Pole, z ktoreho sa prevezmu vlastnosti. </param>
		Array(Array<T>& other);

		/// <summary> Destruktor. </summary>
		~Array();

		/// <summary> Vrati pocet prvkov v poli. </summary>
		/// <returns> Pocet prvkov v poli. </returns>
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
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& operator[](int index);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& at(int index);

		/// <summary> Skopiruje length prvkov z pola src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojove pole. </param>
		/// <param name = "srcStartIndex"> Index prvku v poli src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielove pole. </param>
		/// <param name = "destStartIndex"> Index prvku v poli dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet prvkov, ktore budu skopirovane z pol src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych poli. </exception>
		static void copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length);

	private:
		/// <summary> Vektor s datami. </summary>
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(int index) const;
	};

	template<typename T>
	Array<T>::Array(size_t size) :
		vector_(new Vector(size * sizeof(T))),
		size_(size)
	{
	}

	template<typename T>
	Array<T>::Array(Array<T>& other) :
		vector_(new Vector(*(other.vector_))),		// *other.vector_ to iste ako *(other.vector_) ... bodka ma vacsiu prioritu ako *
		size_(other.size_)
	{
	}

	template<typename T>
	Array<T>::~Array()
	{
		delete vector_;
		vector_ = nullptr;	// nulujem atributy, aby ak nahodou deletnem objekt nechtiac druhykrat 
		size_ = 0;			// tak ak objekt ma vynulovane atributy, tak si vsimnem v debuggri ze sa snazim zmazat uz neplatny objekt
	}

	template<typename T>
	Structure& Array<T>::assign(Structure& other)
	{
		// ak nie je pole identicke s other tak:
		//	pretypujem other na pole
		//	skontrolujem velkost
		//		ak je rovnaka, tak priradim vektory, ktore patria poliam (assign)
		//		ak je rozna, vyhodte vynimku (polia musia byt rovnakej velkosti - vektory nemusia)
		if (this != &other)
		{
			Array<T>& otherArray = dynamic_cast<Array<T>&>(other);
			if (size_ == otherArray.size_)
			{
				vector_->assign(*otherArray.vector_);
				// alternativne priradenie:
				// vector_->operator=(*otherArray.vector_);
				// *vector_ = *otherArray.vector_;
				// vector_ = otherArray.vector_; ZLE!!!
			}
			else
			{
				throw std::invalid_argument("Array size differ!");
			}
		}

		return *this;
	}

	template<typename T>
	inline bool Array<T>::equals(Structure& other)
	{

		Array<T>* otherArray = dynamic_cast<Array<T>*>(&other);
		if (otherArray != nullptr)
		{
			return vector_->equals(*otherArray->vector_);
			// return vector_->operator==(*otherArray->vector_);
			// return *vector_ == *otherArray->vector_;
			// return vector_ == otherArray->vector_; ZLE!!!

		}
		else
		{
			return false;
		}

	}

	template<typename T>
	size_t Array<T>::size()
	{
		return size_;
	}

	template<typename T>
	T& Array<T>::operator[](int index)
	{
		return at(index);
	}

	template<typename T>
	inline T& Array<T>::at(int index)
	{
		// 1 ziskaj pomocou mapovacej funkcie index vo vektore
		int indexInVector = mapFunction(index);

		// 2 ziskaj ukazovatel na byte vo vektore na indexe z kroku 1
		byte* ptrByte = vector_->getBytePointer(indexInVector);

		// 3 pretypuj ukazovatel z kroku 2 na T (T*)
		T* ptrT = reinterpret_cast<T*>(ptrByte);
		// 4 vrat to, na co ukazovatel z kroku 3 ukazuje (dereferuj pointer)
		return *ptrT;
	}

	template<typename T>
	void Array<T>::copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length)
	{
		//Vector::copy(*src.vector_, mapFunction(srcStartIndex), *dest.vector_, mapFunction(destStartIndex), length * sizeof(T));
		Vector::copy(*src.vector_, srcStartIndex * sizeof(T), *dest.vector_, destStartIndex * sizeof(T), length * sizeof(T));
	}

	template<typename T>
	inline int Array<T>::mapFunction(int index) const
	{
		//Utils::rangeCheckExcept(index, size_, "Invalid index!");
		// - pri builde hodi error "cannot resolve symbol Utils" ale iba tu, v inych triedach to resolvnut vie WTF????!!!
		if (index > size_ || index < 0)
		{
			std::out_of_range("Invalid index!");
		}
		return index * sizeof(T);
	}
}


