#pragma once

constexpr int maxSize = 3000;

template<class T>
class LinkedList {

public:
	struct Node {
		Node(T value, Node* prev, Node* next);
		Node() = default;
		T mValue;
		Node* mPrev;
		Node* mNext;
	};

public:
	struct Iterator {
		Node* mPtr;
		bool operator==(const Iterator& it);
		bool operator!=(const Iterator& it);
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		T& operator*();
	};



private:
	size_t mSize;
	Node* mGuard;

public:

	LinkedList();
	LinkedList(const LinkedList& copy);
	LinkedList(LinkedList&& copy) noexcept;
	~LinkedList();
	LinkedList& operator=(const LinkedList& copy);
	LinkedList& operator=(LinkedList&& copy) noexcept;

	template<class U>										 // Uniwersalna referencja 
	void push_front(U&& x);									 // Wstawia element na pocz¹tek listy
	T pop_front();											 // Usuwa element z pocz¹tku listy i zwraca jego wartoœæ lub wyrzuca wyj¹tek gdy lista jest pusta
	template<class U>
	void push_back(U&& x);									 // Wstawia element na koniec listy
	T pop_back();											 // Usuwa element z koñca listy i zwraca jego wartoœæ lub wyrzuca wyj¹tek gdy lista jest pusta
	Iterator find(const T& x);							     // Wyszukuje element o wartoœci`x`// i zwraca jego pozycjê
	Iterator erase(Iterator it);							 // Usuwa element wskazywany przez iterator// i zwraca iterator do kolejnego elementu
	template<class U>
	Iterator insert(Iterator it, U&& x);					 // Wstawia element x przed pozycjê// it i zwraca pozycjê x
	size_t remove(const T& x);								 // Usuwa wyst¹pienia x i zwraca ich liczbê
	size_t size();											 // Zwraca liczbê elementów w liœcie
	bool empty();											 // Zwraca`true`gdy lista jest pusta
	Iterator begin();										 // Zwraca iterator na pierwszy element
	Iterator end();											 // Zwraca iterator na koniec listy,
};

template<class T>
inline bool LinkedList<T>::Iterator::operator==(const Iterator& it)
{
	return mPtr == it.mPtr;
}

template<class T>
inline bool LinkedList<T>::Iterator::operator!=(const Iterator& it)
{
	return !operator==(it);
}

template<class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
{
	this->mPtr = this->mPtr->mNext;
	return *this;
}

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
	Iterator temp = *this;
	this->mPtr = this->mPtr->mNext;
	return temp;
}

template<class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator--()
{
	*(this->mPtr) = this->mPtr->mPrev;
	return *this;
}

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(int)
{
	Iterator temp = *this;
	*(this->mPtr) = this->mPtr->mPrev;
	return temp;
}

template<class T>
T& LinkedList<T>::Iterator::operator*()
{
	return mPtr->mValue;
}

template<class T>
LinkedList<T>::LinkedList()
	:mSize(0),mGuard(new Node(T(),nullptr,nullptr))
{
	mGuard->mNext = mGuard;
	mGuard->mPrev = mGuard;
}



template<class T>
LinkedList<T>::LinkedList(const LinkedList& copy)
	: mSize(copy.mSize),mGuard(new Node(T(),nullptr,nullptr))
{
	mGuard->mNext = mGuard;
	mGuard->mPrev = mGuard;
	
	Node* ptr = copy.mGuard->mNext;
	for (; ptr != copy.mGuard; ptr = ptr->mNext) {
		push_back(ptr->mValue);
	}
}

template<class T>
LinkedList<T>::LinkedList(LinkedList&& copy) noexcept
	:mSize(copy.mSize)
{
	mGuard = copy.mGuard;
	copy.mGuard = new Node(T(), nullptr, nullptr);
	copy.mGuard->mNext = copy.mGuard;
	copy.mGuard->mPrev = copy.mGuard;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	Node* ptr = mGuard->mPrev;
	while ((ptr = ptr->mPrev) != mGuard)
		delete ptr->mNext;
	delete mGuard;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& copy)
{
	if (this != &copy) {
		this->~LinkedList();
		mGuard = new Node(T(), nullptr, nullptr);
		mGuard->mNext = mGuard;
		mGuard->mPrev = mGuard;

		Node* ptr = copy.mGuard->mNext;
		mSize = 0;
		for (; ptr != copy.mGuard; ptr = ptr->mNext) {
			push_back(ptr->mValue);
		}
	}
	return *this;
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& copy) noexcept
{
	if (this != &copy) {
		this->~LinkedList();

		mGuard = copy.mGuard;
		copy.mGuard = new Node(T(), nullptr, nullptr);
		copy.mGuard->mNext = copy.mGuard;
		copy.mGuard->mPrev = copy.mGuard;
		mSize = copy.mSize;
		copy.mSize = 0;
	}
	return *this;
}

template<class T>
template<class U>
void LinkedList<T>::push_front(U&& x)
{
	if (mSize == maxSize)
		throw std::out_of_range("lista jest pelna");
	Node* n = new Node{ std::forward<U>(x),this->mGuard,this->mGuard->mNext };
	mGuard->mNext->mPrev = n;
	mGuard->mNext = n;
	mSize++;
}

template<class T>
T LinkedList<T>::pop_front()
{
	if (empty())
		throw std::out_of_range("Lista jest pusta");

	//Usuwany node
	Node* ptr = mGuard->mNext;
	T temp = ptr->mValue;

	mGuard->mNext = ptr->mNext;
	ptr->mNext->mPrev = mGuard;
	delete ptr;

	mSize--;
	return temp;
}


template<class T>
template<class U>
void LinkedList<T>::push_back(U&& x)
{
	if (mSize == maxSize)
		throw std::out_of_range("lista jest pelna");
	Node* n = new Node(std::forward<U>(x),this->mGuard->mPrev,this->mGuard);
	mGuard->mPrev->mNext = n;
	mGuard->mPrev = n;
	mSize++;

}


template<class T>
T LinkedList<T>::pop_back()
{
	if (empty())
		throw std::out_of_range("Lista jest pusta");

	//Usuwany node
	Node* ptr = mGuard->mPrev;
	T temp = ptr->mValue;

	mGuard->mPrev = ptr->mPrev;
	ptr->mPrev->mNext = mGuard;
	delete ptr;

	mSize--;
	return temp;
}

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::find(const T& x)
{
	Iterator it;
	for (it = begin(); it != end(); ++it) {
		if (*it == x) break;
	}
	return it;

}

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::erase(Iterator it)
{
	if (it == end())
		return it;

	it.mPtr->mNext->mPrev = it.mPtr->mPrev;
	it.mPtr->mPrev->mNext = it.mPtr->mNext;
	Iterator it2{ it.mPtr->mNext };
	delete it.mPtr;

	
	--mSize;
	return it2;
}


//TODO: zrobic to lepiej
template<class T>
size_t LinkedList<T>::remove(const T& x)
{
	size_t n = 0;
	Iterator it;
	while ((it = find(x)) != end()) {
		erase(it);
		++n;
	}
	return n;
}

template<class T>
size_t LinkedList<T>::size()
{
	return mSize;
}

template<class T>
bool LinkedList<T>::empty()
{
	return !mSize;
}

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin()
{
	return LinkedList<T>::Iterator{ mGuard->mNext };
}

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::end()
{
	return  LinkedList<T>::Iterator{mGuard};
}


template<class T>
template<class U>
typename LinkedList<T>::Iterator LinkedList<T>::insert(Iterator it, U&& x)
{
	if (mSize == maxSize)
		throw std::out_of_range("lista jest pelna");

	Node* temp = new Node{ std::forward<U>(x),it.mPtr->mPrev,it.mPtr };
	it.mPtr->mPrev->mNext = temp;
	it.mPtr->mPrev = temp;
	mSize++;
	Iterator it2{ temp };
	return it2;
}

template<class T>
inline LinkedList<T>::Node::Node(T value, Node* prev, Node* next)
	:mValue(value),mPrev(prev),mNext(next)
{
}
