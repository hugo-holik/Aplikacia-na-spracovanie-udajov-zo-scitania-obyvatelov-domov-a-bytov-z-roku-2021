#pragma once

#include "matrix.h"
#include "../array/array.h"
#include <stdexcept>

#include "../heap_monitor.h"

namespace structures
{
	/// <summary> Implementacia matice v suvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class CoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		CoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		CoherentMatrix(CoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~CoherentMatrix();

		/// <summary>
		/// Ak je to mozne (parametrom je matica, ktora ma rovnake rozmery ako ako aktualna matica),
		/// tak skopiruje vlastnosti z matice odovzdanej ako parameter.
		/// Ak to nie je mozne, vyhodi sa vynimka.
		/// </summary>
		/// <param name = "other"> Odkaz na strukturu, z ktorej maju prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary>
		/// Ak je parametrom matica a obsah porovnavanych matic je rovnaky,
		/// tak vrati hodnotu true. V opacnom pripade vrati hodnotu false.
		/// </summary>
		/// <param name="other"> Odkaz na strukturu, s ktorou sa ma tato matica porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Pocet vsetkych prvkov v matici. </summary>
		/// <returns> Pocet prvkov v matici. </returns>
		size_t size() override;

		/// <summary> Vrati pocet riadkov v matici. </summary>
		/// <returns> Pocet riadkov matice. </returns>
		size_t getRowCount() override;

		/// <summary> Vrati pocet stlpcov matice. </summary>
		/// <returns> Pocet stlpcov matice. </returns>
		size_t getColumnCount() override;

		/// <summary> Vrati odkaz na prvok v danom riadku a stlpci. </summary>
		/// <param name="rowIndex"> Index riadku. </param>
		/// <param name="columnIndex"> Index stlpca. </param>
		/// <returns> Odkaz na prvok na danych indexoch. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index riadku alebo stlpca nepatri do matice. </exception>
		T& at(int rowIndex, int columnIndex) override;

	private:
		size_t rowCount_;
		size_t columnCount_;
		Array<T>* array_;
		
	};

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(size_t rowCount, size_t columnCount) :
		//Matrix<T>(),
		rowCount_(rowCount),
		columnCount_(columnCount),
		array_(new Array<T>(rowCount_ * columnCount_))
	{
		//if (rowCount_ > 0 && columnCount_ > 0)
		//{
		//	array_(new Array<T>(rowCount_* columnCount_));
		//}
		//else
		//{
		//	throw std::invalid_argument("Can't create a matrix with 0 columns/rows");
		//}
	}

	template<typename T>
	inline CoherentMatrix<T>::CoherentMatrix(CoherentMatrix& other) :
		//Matrix<T>(),
		rowCount_(other.rowCount_),
		columnCount_(other.columnCount_),
		array_(new Array<T>(*other.array_))
	{
	}

	template<typename T>
	inline CoherentMatrix<T>::~CoherentMatrix()
	{
		delete array_;
		array_ = nullptr;
		rowCount_ = 0;
		columnCount_ = 0;
	}

	template<typename T>
	inline Structure& CoherentMatrix<T>::assign(Structure& other)
	{
		if (this == &other)
		{
			return *this;
		}
		CoherentMatrix<T>& otherCM = dynamic_cast<CoherentMatrix<T>&>(other);
		if(otherCM.rowCount_ != rowCount_ || otherCM.columnCount_ != columnCount_)
		{
			throw std::range_error("Matrix column/row size differ!");
		}

		//delete array_;
		//array_ = new Array<T>(*otherCM.array_);
		array_->assign(*otherCM.array_);
		//rowCount_ = otherCM.rowCount_;
		//columnCount_ = otherCM.columnCount_;
		return *this;
	}

	template<typename T>
	inline bool CoherentMatrix<T>::equals(Structure& other)
	{
		if (this == &other)
		{
			return true;
		}

		CoherentMatrix<T>* otherCM = dynamic_cast<CoherentMatrix<T>*>(&other);
		if (otherCM == nullptr)
		{
			return false; //ak otherCM == nullptr => nepodaril sa cast
		}

		if (otherCM->rowCount_ != rowCount_ || otherCM->columnCount_ != columnCount_)
		{
			return false;
		}
		else
		{
			return array_->equals(*otherCM->array_);
		}
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::size()
	{
		return (rowCount_ * columnCount_);
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getRowCount()
	{
		return rowCount_;
	}

	template<typename T>
	inline size_t CoherentMatrix<T>::getColumnCount()
	{
		return columnCount_;
	}

	template<typename T>
	inline T& CoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		Utils::rangeCheckExcept(rowIndex, rowCount_, "Invalid index!");
		Utils::rangeCheckExcept(columnIndex, columnCount_, "Invalid index!");
		int indexInArray = ((columnCount_) * rowIndex) + columnIndex;
		return array_->at(indexInArray);
	}
}