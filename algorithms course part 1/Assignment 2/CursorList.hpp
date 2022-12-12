#pragma once

constexpr int maxSize = 3000;

template<class T>
class CursorList {

public:
	struct Node {
		Node()
			:mValue(T()), mNext(0) {}

		Node(T v, size_t n)
			:mValue(v), mNext(n) {}
		T mValue;
		size_t mNext;
	};

public:
	struct Iterator {
		size_t mPtr;
		Node* mArrayPtr;

		Iterator(size_t index, Node* arrayPtr);
		Iterator() = default;
		bool operator==(const Iterator& it);
		bool operator!=(const Iterator& it);
		Iterator& operator++();
		Iterator operator++(int);
		T& operator*();
	};



public:
	size_t mHead;
	size_t mTail;
	size_t mSpare;
	size_t mSize;
	Node mArray[maxSize] = {};
public:

	CursorList();
	CursorList(const CursorList& copy) noexcept;
	CursorList(CursorList&& copy) noexcept;
	~CursorList();
	CursorList& operator=(const CursorList& copy) noexcept;
	CursorList& operator=(CursorList&& copy) noexcept;

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
 CursorList<T>::CursorList()
	 :mHead(maxSize),mTail(maxSize),mSpare(0),mSize(0),mArray()
{
	 for (size_t i = 0; i < maxSize; ++i) {
		 mArray[i].mNext = i + 1;
	 }
}

template<class T>
 CursorList<T>::CursorList(const CursorList& copy) noexcept(true)
	 : mSize(copy.mSize), mHead(copy.mHead), mTail(copy.mTail), mSpare(copy.mSpare), mArray{Node()}
{
	 for (size_t i = 0; i < maxSize; ++i) {
		 mArray[i].mValue = copy.mArray[i].mValue;
		 mArray[i].mNext = copy.mArray[i].mNext;
	 }
}

template<class T>
CursorList<T>::CursorList(CursorList&& copy) noexcept
	:mArray{Node()}, mSize(copy.mSize), mHead(copy.mHead), mTail(copy.mTail), mSpare(copy.mSpare)
{
	 for (size_t i = 0; i < maxSize; ++i) {
		 mArray[i].mValue = copy.mArray[i].mValue;
		 mArray[i].mNext = copy.mArray[i].mNext;
	 }

	 for (size_t i = 0; i < maxSize; ++i) {
		 copy.mArray[i].mNext = i + 1;
	 }
	 copy.mHead = maxSize;
	 copy.mTail = maxSize;
	 copy.mSpare = 0;
	 copy.mSize = 0;
}

template<class T>
 CursorList<T>::~CursorList()
{
}

template<class T>
 CursorList<T>& CursorList<T>::operator=(const CursorList& copy) noexcept(true)
{
	 mHead = copy.mHead;
	 mTail = copy.mTail;
	 mSize = copy.mSize;
	 mSpare = copy.mSpare;
	 for (size_t i = 0; i < maxSize; ++i) {
		 mArray[i] = copy.mArray[i];
	 }
	 return *this;
}

template<class T>
 CursorList<T>& CursorList<T>::operator=(CursorList&& copy) noexcept(true)
{

	 mHead = copy.mHead;
	 mTail = copy.mTail;
	 mSize = copy.mSize;
	 mSpare = copy.mSpare;

	 for (size_t i = 0; i < maxSize; ++i) {
		 mArray[i] = copy.mArray[i];
	 }

	 for (size_t i = 0; i < maxSize; ++i) {
		 copy.mArray[i] = Node(T(),i + 1);
	 }

	 copy.mHead = maxSize;
	 copy.mTail = maxSize;
	 copy.mSpare = 0;
	 copy.mSize = 0;
	 return *this;
}

template<class T>
 T CursorList<T>::pop_front()
{
	 if (empty())
		 throw std::out_of_range("Lista pusta");


	 size_t tempHead = mArray[mHead].mNext;
	 mArray[mHead].mNext = mSpare;
	 mSpare = mHead;
	 mHead = tempHead;
	 mSize--;
	 
	 
	 if (mSize == 0)
		 mTail = maxSize;
	 
	 return mArray[mSpare].mValue;
}

template<class T>
 T CursorList<T>::pop_back()
{
	 if (empty())
		 throw std::out_of_range("Lista pusta");

	 if (mHead == mTail) {
		 T temp = mArray[mHead].mValue;
		 mArray[mHead].mNext = mSpare;
		 mHead = mTail = maxSize;
		 mSize--;
		 return temp;
	 }

	 Iterator it = begin();
	 for (size_t i = 0; i < mSize - 2; ++i, ++it);
	 mArray[mArray[it.mPtr].mNext].mNext = mSpare;
	 mSpare = mArray[it.mPtr].mNext;
	 mTail = it.mPtr;
	 mArray[it.mPtr].mNext = maxSize;


	 mSize--;
	 return mArray[mSpare].mValue;
}

 template<class T>
 template<class U>
 void CursorList<T>::push_front(U&& x)
 {
	 if (mSize == maxSize)
		 throw std::out_of_range("Lista pelna");
	 
	 mArray[mSpare].mValue = std::forward<U>(x);

	 size_t temp = mSpare;
	 mSpare = mArray[mSpare].mNext;
	 mArray[temp].mNext = mHead;
	 mHead = temp;
	 if (mSize == 0)
		 mTail = temp;
	 mSize++;
 }

 template<class T>
 template<class U>
 void CursorList<T>::push_back(U&& x)
 {
	 if (mSize == maxSize)
		 throw std::out_of_range("Lista pelna");

	 mArray[mSpare].mValue = std::forward<U>(x);

	 size_t temp = mSpare;
	 mSpare = mArray[mSpare].mNext;
	 if(mSize!=0)
		mArray[mTail].mNext = temp;
	 mTail = temp;
	 mArray[mTail].mNext = maxSize;
	 if (mSize == 0)
		 mHead = temp;
	 mSize++;
 }


template<class T>
typename CursorList<T>::Iterator CursorList<T>::find(const T& x)
{
	Iterator returnIt;
	for (returnIt = begin(); returnIt != end(); ++returnIt) {
		if (*returnIt == x) break;
	}
	return returnIt;
}

template<class T>
typename  CursorList<T>::Iterator CursorList<T>::erase(Iterator it)
{
	if (it == end())
		return it;

	//poniewaz trzeba dobrze poprzepinac head i tail to sprawdzam to
	//sprawdzenie czy usuwamy pierwszy element
	if (it == begin()) {
		pop_front();
		return Iterator(mHead, mArray);
	}
	//sprawdzenie czy usuwamy ostatni element
	
	if (it.mPtr == mTail) {
		pop_back();
		return Iterator(mTail, mArray);
	}


	Iterator it2 = begin();
	while (mArray[it2.mPtr].mNext != it.mPtr) 
		it2++;

	mArray[it2.mPtr].mNext = mArray[it.mPtr].mNext;
	Iterator iReturn(mArray[it.mPtr].mNext, mArray);
	mArray[it.mPtr].mNext = mSpare;
	mSpare = it.mPtr;
		
	mSize--;
	return iReturn;
}

template<class T>
 size_t CursorList<T>::remove(const T& x)
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
 size_t CursorList<T>::size()
{
	 return mSize;
}

template<class T>
 bool CursorList<T>::empty()
{
	return !mSize;
}

template<class T>
typename  CursorList<T>::Iterator CursorList<T>::begin()
{
	Iterator a = Iterator(mHead, mArray);
	return a;
}

template<class T>
typename CursorList<T>::Iterator CursorList<T>::end()
{
	return Iterator(maxSize,mArray);
}



template<class T>
template<class U>
typename  CursorList<T>::Iterator CursorList<T>::insert(Iterator it, U&& x)
{

	if (mSize == maxSize)
		throw std::out_of_range("Lista jest pelna");

	//poniewaz trzeba dobrze poprzepinac head i tail to sprawdzam to
	//sprawdzenie czy usuwamy pierwszy element
	if (it == begin()) {
		push_front(std::forward<U>(x));
		return Iterator(mHead, mArray);
	}
	//sprawdzenie czy usuwamy ostatni element

	if (it.mPtr == mTail) {
		push_back(std::forward<U>(x));
		return Iterator(mTail, mArray);
	}

	Iterator it2 = begin();
	while (mArray[it2.mPtr].mNext != it.mPtr)
		it2++;
	
	mArray[mSpare].mValue = std::forward<U>(x);

	size_t temp = mSpare;
	mSpare = mArray[mSpare].mNext;
	mArray[temp].mNext = it.mPtr;
	mArray[it2.mPtr].mNext = temp;
	mSize++;
	return Iterator(temp, mArray);
}



template<class T>
CursorList<T>::Iterator::Iterator(size_t index, Node* arrayPtr)
	:mPtr(index), mArrayPtr(arrayPtr) 
{}
	

template<class T>
inline bool CursorList<T>::Iterator::operator==(const Iterator& it)
{
	return mPtr == it.mPtr;
}

template<class T>
inline bool CursorList<T>::Iterator::operator!=(const Iterator& it)
{
	return !operator==(it);
}

template<class T>
typename CursorList<T>::Iterator& CursorList<T>::Iterator::operator++()
{
	mPtr = (mArrayPtr + mPtr)->mNext;
	return *this;
}

template<class T>
typename CursorList<T>::Iterator CursorList<T>::Iterator::operator++(int)
{
	Iterator temp = *this;
	mPtr = (mArrayPtr + mPtr)->mNext;
	return temp;
}


template<class T>
T& CursorList<T>::Iterator::operator*()
{
	return (mArrayPtr + mPtr)->mValue;
}