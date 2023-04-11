#pragma once

#include "matrix.h"
#include "../array/array.h"
#include <stdexcept>

#include "../heap_monitor.h"

namespace structures
{
	/// <summary> Implementacia matice v nesuvislej pamati. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v matici. </typepram>
	template<typename T>
	class IncoherentMatrix
		: public Matrix<T>
	{
	public:
		/// <summary>
		///	Konstruktor. Vytvori maticu o danom pocte riadkov a stlpcov.
		/// Polozky su inicializovane na "nulovu" hodnotu typu T.
		/// </summary>
		/// <param name="rowCount"> Pocet riadkov. </param>
		/// <param name="columnCount"> Pocet stlpcov. </param>
		IncoherentMatrix(size_t rowCount, size_t columnCount);

		/// <summary> Inicializuje tuto maticu ako kopiu matice odovzdanej ako parameter. </summary>
		/// <param name = "other"> Odkaz na maticu, z ktorej sa prevezmu vlastnosti. </param>
		IncoherentMatrix(IncoherentMatrix& other);

		/// <summary> Destruktor. </summary>
		~IncoherentMatrix();

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
		Array<Array<T>*>* data_;
	};

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(size_t rowCount, size_t columnCount) :
		rowCount_(rowCount),
		columnCount_(columnCount)
	{
		data_ = new Array<Array<T>*>(rowCount_);

		for (int i = 0; i < rowCount_; i++)
		{
			//data_->at(i)->assign(*(new Array<T>(columnCount_)));
			data_->at(i) = new Array<T>(columnCount_);
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::IncoherentMatrix(IncoherentMatrix& other) :
		rowCount_(other.rowCount_),
		columnCount_(other.columnCount_)
	{
		data_ = new Array<Array<T>*>(rowCount_);

		for (int i = 0; i < rowCount_; i++)
		{
			//data_->at(i)->assign(*other.data_->at(i));
			data_->at(i) = new Array<T>(columnCount_);
			data_->at(i)->assign(*other.data_->at(i));
		}
	}

	template<typename T>
	inline IncoherentMatrix<T>::~IncoherentMatrix()
	{
		for (int i = 0; i < rowCount_; i++)
		{
			delete data_->at(i);
		}
		delete data_;
		data_ = nullptr;
		columnCount_ = 0;
		rowCount_ = 0;
	}

	template<typename T>
	inline Structure& IncoherentMatrix<T>::assign(Structure& other)
	{
		if (this == &other)
		{
			return *this;
		}

		IncoherentMatrix<T>& otherIM = dynamic_cast<IncoherentMatrix<T>&>(other);

		if (otherIM.rowCount_ != rowCount_ || otherIM.columnCount_ != columnCount_)
		{
			throw std::range_error("Matrix column/row size differ!");
		}

		//for (int i = 0; i < rowCount_; i++)
		//{
		//	delete data_[i];
		//}
		//delete data_;


		for (int i = 0; i < rowCount_; i++)
		{
			data_->at(i)->assign(*otherIM.data_->at(i));
		}
		return *this;
	}

	template<typename T>
	inline bool IncoherentMatrix<T>::equals(Structure& other)
	{
		if (this == &other)
		{
			return true;
		}

		IncoherentMatrix<T>* otherIM = dynamic_cast<IncoherentMatrix<T>*>(&other);

		if (otherIM == nullptr)
		{
			return false;
		}

		if (otherIM->rowCount_ != rowCount_ || otherIM->columnCount_ != columnCount_)
		{
			return false;
		}

		//porovnavanie riadkov (vnorenych arrayov) medzi sebou a otherIM
		for (int i = 0; i < rowCount_; i++)
		{
			if (data_->at(i)->equals(*otherIM->data_->at(i)) == false)
			{
				return false;
			}
		}

		//ak prejde for bez return false => vsetky riadky (vnorene arraye) sa rovnaju
		return true;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::size()
	{
		return columnCount_ * rowCount_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getRowCount()
	{
		return rowCount_;
	}

	template<typename T>
	inline size_t IncoherentMatrix<T>::getColumnCount()
	{
		return columnCount_;
	}

	template<typename T>
	inline T& IncoherentMatrix<T>::at(int rowIndex, int columnIndex)
	{
		//int hodnota = 5;
		//int* smernikNaHodnotu = &hodnota;
		//int** smernikNaSmernikNaHodnotu = &smernikNaHodnotu;

		//int*& referenciaNaSmernik = *smernikNaSmernikNaHodnotu;

		Utils::rangeCheckExcept(rowIndex, rowCount_, "Invalid index!");
		Utils::rangeCheckExcept(columnIndex, columnCount_, "Invalid index!");

		return data_->at(rowIndex)->at(columnIndex);
	}
}