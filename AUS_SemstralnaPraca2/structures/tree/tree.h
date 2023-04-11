#pragma once

#include "../structure.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include <queue>

namespace structures
{
	/// <summary> Vrchol stromu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo vrchole stromu. </typepram>
	template <typename T>
	class TreeNode : public DataItem<T>
	{
	public:
		/// <summary> Vytvori plytku kopiu vrchola (teda skopiruje iba data a smerniky na synov). </summary>
		/// <returns> Vystvorena plytka kopia vrcholu. </returns>
		virtual TreeNode<T>* shallowCopy() = 0;

		/// <summary> Vytvori a vrati hlboku kopiu vrchola (teda skopiruje data a skopiruje celu stromovu strukturu). </summary>
		/// <returns> Hlboka kopia vrchola. </returns>
		virtual TreeNode<T>* deepCopy();

		/// <summary> Test, ci je koren. </summary>
		/// <returns> true, ak je koren, false inak. </returns>
		bool isRoot();

		/// <summary> Test, ci je list. </summary>
		/// <returns> true, ak je list, false inak. </returns>
		virtual bool isLeaf() = 0;

		/// <summary> Spristupni rodica vrcholu. </summary>
		/// <returns> Rodic vrcholu. </returns>
		TreeNode<T>* getParent();

		/// <summary> Nastavi rodica na nullptr. </summary>
		void resetParent();

		/// <summary> Zmeni rodica vrcholu. </summary>
		/// <param name = "parent"> Novy rodic vrcholu. </param>
		void setParent(TreeNode<T>* parent);

		/// <summary> Spristupni brata vrcholu podla jeho pozicie u spolocneho rodica. </summary>
		/// <param name = "brothersOrder"> Poradie brata u rodica. </param>
		/// <exception cref=""> Vyhodena, ak je korenom. </exception>
		/// <returns> Brat vrcholu. </returns>
		virtual TreeNode<T>* getBrother(int brothersOrder);

		/// <summary> Spristupni syna vrcholu podla jeho pozicie v tomto vrchole. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Syn vrcholu. </returns>
		virtual TreeNode<T>* getSon(int order) = 0;

		/// <summary> Vlozi noveho syna vrcholu na dane miesto. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <remarks>
		/// Spravanie sa lisi podla toho, ci sa jedna o vrchol s pevnym alebo variabilnym poctom synov.
		/// Vsetky smerniky zucastnenych vrcholov budu spravne nastavene.
		/// </remarks>
		virtual void insertSon(TreeNode<T>* son, int order) = 0;

		/// <summary> Nahradi syna vrcholu na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je poradie neplatne. </exception>
		/// <returns> Nahradeny syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		virtual TreeNode<T>* replaceSon(TreeNode<T>* son, int order) = 0;

		/// <summary> Odstrani syna na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Odstraneny syn vrcholu. </returns>
		/// <remarks>
		/// Spravanie sa lisi podla toho, ci sa jedna o vrchol s pevnym alebo variabilnym poctom synov.
		/// Vsetky smerniky zucastnenych vrcholov budu spravne nastavene.
		/// </remarks>
		virtual TreeNode<T>* removeSon(int order) = 0;

		/// <summary> Vrati stupen vrcholu. </summary>
		/// <returns> Stupen vrcholu. </returns>
		virtual int degree() = 0;

		/// <summary> Vrati pocet vrcholov v podstrome. </summary>
		/// <returns> Pocet vrcholov v podstrome. </returns>
		virtual size_t sizeOfSubtree();

	protected:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		TreeNode(const T& data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol stromu, z ktoreho sa prevezmu vlastnosti. </param>
		TreeNode(TreeNode<T>& other);

		/// <summary> Odkaz na rodica. </summary>
		TreeNode<T>* parent_;
	};

	/// <summary> Strom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strome. </typepram>
	template <typename T>
	class Tree : public Structure, public Iterable<T>
	{
	public:
		/// <summary> Konstruktor, inicializuje prazdny strom. </summary>
		Tree();

		/// <summary> Kopirovaci konstruktor. </summary>
		Tree(Tree<T>& other);

		/// <summary> Destruktor. </summary>
		~Tree();

		/// <summary> Zisti, ci je struktura prazdna. </summary>
		/// <returns> true, ak je struktura prazdna, false inak. </returns>
		bool isEmpty() override;

		/// <summary> Vrati pocet vrcholov v strome. </summary>
		/// <returns> Pocet vrcholov v strome. </returns>
		size_t size() override;

		/// <summary> Vymaze strom. </summary>
		virtual void clear();

		/// <summary> Spristupni koren stromu. </summary>
		/// <returns> Koren stromu. </returns>
		TreeNode<T>* getRoot();

		/// <summary> Nahradi koren stromu. </summary>
		/// <param name = "newRoot">  Novy koren stromu. </param>
		/// <returns> Povodny koren stromu. </returns>
		virtual TreeNode<T>* replaceRoot(TreeNode<T>* newRoot);

		/// <summary> Vytvori a vrati instanciu vrcholu stromu. </summary>
		/// <returns> Vytvorena instancia vrcholu stromu. </returns>
		/// <remarks>
		/// Kazdy strom spravuje vrcholy ineho typu, mali by vsak byt jednotne v celom strome.
		/// Tato tovarenska metoda by mala byt pretazena v kazdom potomkovi stromu tak, aby vracala vrcholy, ktore ten strom ocakava.
		/// Instance vrcholov by mali byt vytvarane vyhradne pomocou tejto metody.
		/// </remarks>
		virtual TreeNode<T>* createTreeNodeInstance() = 0;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() override;

	protected:
		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assignTree(Tree<T>& other);

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equalsTree(Tree<T>* other);

	private:
		/// <summary> Koren stromu. </summary>
		TreeNode<T>* root_;

	protected:
		/// <summary> Iterator pre Tree. </summary>
		class TreeIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			TreeIterator();

			/// <summary> Destruktor. </summary>
			~TreeIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator=(Iterator<T>& other) override;

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

		protected:
			/// <summary> Prehliadka stromu. </summary>
			std::queue<TreeNode<T>*>* path_;
		};

	public:
		class PreOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			PreOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi preorder. </summary>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};

		class PostOrderTreeIterator: public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			PostOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi postorder. </summary>
			/// <param name = "path"> Cesta stromom, ktoru zostavuje. </param>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};

		class LevelOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			LevelOrderTreeIterator(TreeNode<T>* startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku stromu v poradi levelorder. </summary>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* current);
		};
	};

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::deepCopy()
	{
		//verzia cviko:


		////?
		//auto result = shallowCopy();
		//int kolkoSynovSpracovanych = 0;

		//for (int i = 0; kolkoSynovSpracovanych < degree(); i++)
		//{
		//	TreeNode<T>* son = getSon(i);
		//	if (son != nullptr)
		//	{
		//		result->replaceSon(son->deepCopy(), i);
		//		kolkoSynovSpracovanych++;
		//	}
		//}

		//return result;


		//verzia 2:

		auto result = shallowCopy();

		int numberOfProcessedSons = 0;
		for (int i = 0; numberOfProcessedSons < degree(); i++)
		{
			auto son = getSon(i);

			if (son != nullptr)
			{

				result->replaceSon(son->deepCopy(), i);
				numberOfProcessedSons++;
			}
		}
		return result;
	}

	template<typename T>
	inline bool TreeNode<T>::isRoot()
	{
		return parent_ == nullptr;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getParent()
	{
		return parent_;
	}

	template<typename T>
	inline void TreeNode<T>::resetParent()
	{
		parent_ = nullptr;
	}

	template<typename T>
	inline void TreeNode<T>::setParent(TreeNode<T>* parent)
	{
		parent_ = parent;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getBrother(int brothersOrder)
	{
		//verzia cviko:

		//if (!isRoot())
		//{
		//	return parent_->getSon(brothersOrder);
		//}
		//else
		//{
		//	throw std::logic_error("Root has no brother!");
		//}


		//verzia 2:

		if (parent_ == nullptr) 
		{
			throw std::logic_error("Root has no brother");
		}

		return parent_->getSon(brothersOrder);
	}

	template<typename T>
	inline size_t TreeNode<T>::sizeOfSubtree()
	{
		// PreOrder(u)
		//		akcia(u) //akcia -> spocitanie synov(sizeOfSubtree())
		//		PrejdiVsetkychSynov(u)
		//			PreOrder(s)

		// ^ rekurzivne spocitam result

		// degree stromu moze byt 5, ale synov moze mat 2 a na ostatnych 3 miestach diery (nullpointre)
		// preto treba ist cez i < kolkoSynovSpracovanych a nie  i < degree()



		//verzia cviko:

		//int result = 1;
		//int kolkoSynovSpracovanych = 0;
		//
		//for (int i = 0; i < kolkoSynovSpracovanych; i++)
		//{
		//	TreeNode<T>* son = getSon(i);
		//	if (son != nullptr)
		//	{
		//		result += son->sizeOfSubtree(); 
		//		kolkoSynovSpracovanych++;
		//	}
		//}

		//return result;



		// verzia 2:

		int numberOfProcessedSons = 0;
		int result = 1;

		for (int i = 0; numberOfProcessedSons < degree(); i++)
		{
			auto son = getSon(i);

			if (son != nullptr)
			{
				result += son->sizeOfSubtree();
				numberOfProcessedSons++;
			}
		}

		return result;
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(const T& data):
		DataItem<T>(data),
		parent_(nullptr)
	{
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(TreeNode<T>& other):
		DataItem<T>(other),
		parent_(other.parent_)
	{
	}

	template<typename T>
	inline Tree<T>::~Tree()
	{
		clear();
	}

	template<typename T>
	inline bool Tree<T>::isEmpty()
	{
		return root_ == nullptr;
	}

	template<typename T>
	inline size_t Tree<T>::size()
	{
		return root_ == nullptr ? 0 : root_->sizeOfSubtree();
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getBeginIterator()
	{
		return new PreOrderTreeIterator(root_);
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getEndIterator()
	{
		return new PreOrderTreeIterator(nullptr);
	}

	template<typename T>
	inline Structure& Tree<T>::assignTree(Tree<T>& other)
	{
		if (this != &other)
		{
			clear();
			if (other.root_ != nullptr)
			{
				root_ = other.root_->deepCopy();
			}
		}

		return *this;
	}

	template<typename T>
	inline bool Tree<T>::equalsTree(Tree<T>* other)
	{
		//verzia cviko: (neda sa prelozit)

		//if (this == other)
		//{
		//	return true;
		//}

		//if (other == nullptr)
		//{
		//	return false;
		//}

		//auto iterThis = getBeginIterator();
		//auto iterOther = other->getBeginIterator();
		//auto endThis = getEndIterator();

		//while (*iterThis != endThis)
		//{
		//	if (*iterThis != *iterOther)
		//	{
		//		return false;
		//	}

		//	++iterThis;
		//	++iterOther;
		//}


		//verzia 2:

		if (other == nullptr)
		{
			return false;
		}

		if (this == other)
		{
			return true;
		}

		auto iteratorThis = this->begin();
		auto iteratorEnd = this->end();
		auto iteratorOther = other->begin();

		while (iteratorThis != iteratorEnd)
		{

			if (*iteratorThis != *iteratorOther) 
			{
				return false;
			}

			++iteratorThis;
			++iteratorOther;

		}


		return !(iteratorOther != other->end());
	}

	template<typename T>
	inline Tree<T>::Tree():
		Structure(),
		Iterable<T>(),
		root_(nullptr)
	{
	}

	template<typename T>
	inline Tree<T>::Tree(Tree<T>& other):
		Tree<T>()
	{
		assignTree(other);
	}

	template<typename T>
	inline void Tree<T>::clear()
	{
		delete root_;
		root_ = nullptr;
	}

	template<typename T>
	inline TreeNode<T>* Tree<T>::getRoot()
	{
		return root_;
	}

	template<typename T>
	inline TreeNode<T>* Tree<T>::replaceRoot(TreeNode<T>* newRoot)
	{
		auto result = root_;

		root_ = newRoot;
		return result;
	}

	template<typename T>
	inline Tree<T>::TreeIterator::TreeIterator():
		Iterator<T>(),
		path_(new std::queue<TreeNode<T>*>()) // sem si mozes dat hocijaky svoj queue, nemusi byt std::
	{
	}

	template<typename T>
	inline Tree<T>::TreeIterator::~TreeIterator()
	{
		delete path_; // zahodi svoj front (queue)
		path_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator=(Iterator<T>& other)
	{
		*path_ = *dynamic_cast<TreeIterator&>(other).path_;
		return *this;
	}

	template<typename T>
	inline bool Tree<T>::TreeIterator::operator!=(Iterator<T>& other)
	{
		return *path_ != *dynamic_cast<TreeIterator&>(other).path_;
	}

	template<typename T>
	inline T Tree<T>::TreeIterator::operator*()
	{
		return path_->front()->accessData();
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator++()
	{
		path_->pop();
		return *this;
	}

	template<typename T>
	inline Tree<T>::PreOrderTreeIterator::PreOrderTreeIterator(TreeNode<T>* startNode):
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::PreOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
		//verzia cviko:

		////if (current != nullptr)
		////{
		////	TreeIterator::path_->push(current);

		////	int kolkoSynovSpracovanych = 0;

		////	for (int i = 0; kolkoSynovSpracovanych < current->degree(); i++)
		////	{
		////		auto son = getSon(i);
		////		if (son != nullptr)
		////		{
		////			populatePath(son);
		////			kolkoSynovSpracovanych++;
		////		}
		////	}
		////}

		//if (current != nullptr)
		//{
		//	TreeIterator::path_->push(current);

		//	int numberOfProcessedSons = 0;
		//	for (int i = 0; numberOfProcessedSons < current->degree(); i++)
		//	{
		//		auto son = current->getSon(i);
		//		if (son != nullptr)
		//		{
		//			populatePath(son);
		//			numberOfProcessedSons++;
		//		}
		//	}
		//}


		//verzia 2

		if (current != nullptr)
		{
			TreeIterator::path_->push(current);

			int numberOfProcessedSons = 0;
			for (int i = 0; numberOfProcessedSons < current->degree(); ++i)
			{
				auto son = current->getSon(i);

				if (son != nullptr)
				{
					populatePath(son);
					numberOfProcessedSons++;
				}

			}
		}
	}

	template<typename T>
	inline Tree<T>::PostOrderTreeIterator::PostOrderTreeIterator(TreeNode<T>* startNode) :
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::PostOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
		//verzia cviko

		////??? pozri nahrate cviko obs
		//if (current != nullptr)
		//{
		//	

		//	int numberOfProcessedSons = 0;
		//	for (int i = 0; numberOfProcessedSons < current->degree(); i++)
		//	{
		//		auto son = current->getSon(i);
		//		if (son != nullptr)
		//		{
		//			populatePath(son);
		//			numberOfProcessedSons++;
		//		}
		//	}

		//	TreeIterator::path_->push(current);
		//}


		//verzia 2:


		if (current != nullptr)
		{
			int processed = 0;

			for (int i = 0; processed < current->degree(); i++)
			{
				auto son = current->getSon(i);
				if (son != nullptr)
				{
					populatePath(son);
					processed++;

				}
			}

			TreeIterator::path_->push(current);
		}
	}

	template<typename T>
	inline Tree<T>::LevelOrderTreeIterator::LevelOrderTreeIterator(TreeNode<T>* startNode) :
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::LevelOrderTreeIterator::populatePath(TreeNode<T>* current)
	{
		//nerobili sme na cviku

		//TODO 07: Tree<T>::LevelOrderTreeIterator
		throw std::runtime_error("Tree<T>::LevelOrderTreeIterator::populatePath: Not implemented yet.");
	}

}

