#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)),
		size_(size)
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		memcpy(memory_, other.memory_, size_);
	}

	Vector::~Vector()
	{
		free(memory_);
		memory_ = nullptr;
		size_ = 0;
	}

	size_t Vector::size()
	{
		return size_;
	}

	Structure& Vector::assign(Structure& other)		// navratova hod: Structure& -> referencia, cize pamatove miesto, nie ukazovatel na pamat.
	{
		if(this != &other)
		{
			Vector& otherVector = dynamic_cast<Vector&>(other); // otherVector je referencia (nevytvaram kopiu objektu => nevolam copyconstructor) // dynamic_cast je pretypovanie(NA UROVNI OBJEKTOV!) ... to iste co: (Vector&)other
			size_ = otherVector.size_;
			memory_ = realloc(memory_, size_); // ak sa pamat premiestni(zmeni sa adresa), realloc novy smernik na pamat hadze v navratovej hodnote -> ulozim si do memory_
			memcpy(memory_, otherVector.memory_, size_);

		}

		return *this;	// this je smernik(ukazovatel) na mna(tento objekt Vector), ale navratova hodnota je typu referencia = pamatove miesto ... smernik = ukazovatel na pamatove miesto ... preto treba this dereferovat cez *this
	}

	bool Vector::equals(Structure& other)
	{
		if (this == &other)
		{
			return true;
		}
		else
		{
			Vector* otherVector = dynamic_cast<Vector*>(&other); //ak cast je succesful -> vrati pointer Vector* ... ak cast fails -> vrati nullptr (kedy sa neda vykonat pretypovanie: npr do parametra hodim pole Array<> zdedene od Structures - pole structures ma ten isty typ ako jeden strucutre - takze sa to do parametra hodit dá  ... lenze nemozes pretypovat smernik pole strucures na smernik Vector*) 
			if (otherVector != nullptr)
			{
				return size_ == otherVector->size_ && memcmp(memory_, otherVector->memory_, size_) == 0;	// memcpm spravi xor pamat1, pamat2 -> ak vysledok je 0, tak to znamena ze pamatove miesta sa rovnaju (spomen na sojaz xor eax, eax --> takto vynulujes registre)
				
			}
			else
			{
				return false;	// ak otherVector je nullptr -> znamena ze parameter other je ineho typu ako Vector -> zlyhalo pretypovanie
			}
		}
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index)
	{
		Utils::rangeCheckExcept(0, size_, "Invalid index!");	// vid dokumentaciu Utils
		return *(reinterpret_cast<byte*>(memory_) + index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		Utils::rangeCheckExcept(srcStartIndex, src.size_, "Invalid index!");
		Utils::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Invalid index!");
		Utils::rangeCheckExcept(destStartIndex, src.size_, "Invalid index!");
		Utils::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Invalid index!");

		// ak su src a dest IDENTICKE a zaroven je vzdialenost medzi src StartIndex a destStartIndex mensia ako length
		// tak: memmove (lebo pamate sa prekryvaju)
		// inak: memcpy (pamate sa neprekryvaju)
		// (memmove je pomalsia operacia)
		if (&src == &dest && abs(srcStartIndex - destStartIndex) < length)
		{
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else 
		{
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		Utils::rangeCheckExcept(0, size_, "Invalid index!");	// vid dokumentaciu Utils
		return reinterpret_cast<byte*>(memory_) + index;	// reinterpret_cast je pretypovanie medzi smernikmy (je nebezpecny - kontroluje iba velkost pointrov)
		// memory_ + index -> posuvam smernik, dostavam pamatove miesta na indexe
		// lenze memory_ je typu void* -> prekladac nevie o kolko ma posunut adresu(kebyze je int*, tak posuva adresu o velkost intu (adresa + index*sizeof(int)) ... kebyze je typu word*, tak posuva o velkost wordu, atd...)
		// vector uchovava byty -> takze budeme posuvat adresu o byty (index*sizeof(byte)) -> pretypujem memory_ z void* na byte*
	}
}