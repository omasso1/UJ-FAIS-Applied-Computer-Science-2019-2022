#pragma once

constexpr int maxSize = 3000;
template<class T>
class ArrayList {

private:
	// Zagnie¿d¿ona klasa iteratora
public:
	struct Iterator {
		T* mPtr;
		bool operator==(const Iterator& it);
		bool operator!=(const Iterator& it);
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		T& operator*();
	};

public:
	size_t mSize;
	size_t mCapacity;
	T* mArray;
	

public:

	ArrayList();
	ArrayList(size_t size);
	ArrayList(const ArrayList& copy);
	ArrayList(ArrayList&& copy) noexcept;
	~ArrayList();
	ArrayList& operator=(const ArrayList& copy);
	ArrayList& operator=(ArrayList&& copy) noexcept;

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
	size_t remove(const T& x);									 // Usuwa wyst¹pienia x i zwraca ich liczbê
	size_t size();											 // Zwraca liczbê elementów w liœcie
	bool empty();											 // Zwraca`true`gdy lista jest pusta
	Iterator begin();										 // Zwraca iterator na pierwszy element
	Iterator end();											 // Zwraca iterator na koniec listy,
};

template<class T>
inline bool ArrayList<T>::Iterator::operator==(const Iterator& it)
{
	return mPtr == it.mPtr;
}

template<class T>
inline bool ArrayList<T>::Iterator::operator!=(const Iterator& it)
{
	return !operator==(it);
}

template<class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator++()
{
	++mPtr;
	return *this;
}

template<class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++(int)
{
	Iterator temp = *this;
	++mPtr;
	return temp;
}

template<class T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator--()
{
	  --mPtr;
	  return *this;
}

template<class T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--(int)
{
	  Iterator temp = *this;
	  --mPtr;
	  return temp;
}

template<class T>
T& ArrayList<T>::Iterator::operator*()
{
	return *mPtr;
}

template<class T>
 ArrayList<T>::ArrayList()
	 :mSize(0),mCapacity(maxSize),mArray(new T[maxSize])
{
}

 template<class T>
 ArrayList<T>::ArrayList(size_t size)
	 : mSize(0), mCapacity(size), mArray(new T[size])
 {
 }

template<class T>
 ArrayList<T>::ArrayList(const ArrayList& copy)
	 :mSize(copy.mSize),mCapacity(copy.mCapacity),mArray(new T[copy.mCapacity])
{
	 for (size_t i = 0; i < copy.mCapacity; ++i) {
		 mArray[i] = copy.mArray[i];
	 }
}

template<class T>
 ArrayList<T>::ArrayList(ArrayList&& copy) noexcept
	 :mSize(copy.mSize), mCapacity(copy.mCapacity), mArray(copy.mArray)
{
	 copy.mSize = 0;
	 copy.mArray = nullptr;
}

template<class T>
 ArrayList<T>::~ArrayList()
{
	 delete[] mArray;
}

template<class T>
 ArrayList<T>& ArrayList<T>::operator=(const ArrayList& copy)
{
	 if (&copy != this) {
		 delete[] mArray;
		 mSize = copy.mSize;
		 mCapacity = copy.mCapacity;
		 mArray = new T[mCapacity];
		

		 for (size_t i = 0; i < copy.mCapacity; ++i) {
			 mArray[i] = copy.mArray[i];
		 }
	 }
	 return *this;
}

template<class T>
 ArrayList<T>& ArrayList<T>::operator=(ArrayList&& copy) noexcept
{
	 if (&copy != this) {
		 delete[] mArray;
		 mSize = copy.mSize;
		 mCapacity = copy.mCapacity;
		 mArray = copy.mArray;
		
		 copy.mSize = 0;
		 copy.mArray = nullptr;

		
	 }
	 return *this;
}

template<class T>
template<class U>
 void ArrayList<T>::push_front(U&& x)
{
	 if (mSize == mCapacity)
		 throw std::out_of_range("Lista jest pelna");

	 for (size_t i = mSize; i > 0; --i) {
		 mArray[i] = std::move(mArray[i-1]);
	 }
	 ++mSize;
	 mArray[0] = std::forward<U>(x);
}

template<class T>
 T ArrayList<T>::pop_front()
{
	 if (empty())
		 throw std::out_of_range("Lista jest pusta");

	 T temp = std::move(mArray[0]);
	 for (size_t i =0; i <mSize-1; ++i) {
		 mArray[i] = std::move(mArray[i+1]);
	 }
	 --mSize;
	 return temp;
}


 template<class T>
 template<class U>
 void ArrayList<T>::push_back(U&& x)
 {
	 if (mSize == mCapacity)
		 throw std::out_of_range("Lista jest pelna");

	 mArray[mSize++] = std::forward<U>(x);
 }


template<class T>
 T ArrayList<T>::pop_back()
{
	 if (empty())
		 throw std::out_of_range("Lista jest pusta");

	 T temp = std::move(mArray[--mSize]);
	 return temp;
}

template<class T>
typename ArrayList<T>::Iterator ArrayList<T>::find(const T& x)
{
	Iterator returnIt;
	for (returnIt = begin(); returnIt != end(); ++returnIt) {
		if (*returnIt == x) break;
	}
	return returnIt;
}


template<class T>
typename ArrayList<T>::Iterator ArrayList<T>::erase(Iterator it)
{
	if (it == end())
		return it;

	for (Iterator it2 = it; it2 != end(); ) {
		Iterator temp = it2;
		*temp = std::move(*(++it2));
	}
	--mSize;
	return it;
}


//TODO: zrobic to lepiej, razem z erase
template<class T>
 size_t ArrayList<T>::remove(const T& x)
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
size_t ArrayList<T>::size()
{
	return mSize;
}

template<class T>
 bool ArrayList<T>::empty()
{
	return !mSize;
}

template<class T>
typename ArrayList<T>::Iterator ArrayList<T>::begin()
{
	return ArrayList<T>::Iterator{mArray};
}

template<class T>
typename ArrayList<T>::Iterator ArrayList<T>::end()
{
	return  ArrayList<T>::Iterator{ mArray + mSize };
}


template<class T>
template<class U>
typename ArrayList<T>::Iterator ArrayList<T>::insert(Iterator it, U&& x)
{
	if (mSize == mCapacity)
		throw std::out_of_range("Lista jest pelna");

	for (Iterator it2 = end(); it2 != it;) {
		Iterator temp = it2;
		*temp = std::move(*(--it2));
	}
	*it = std::forward<U>(x);
	mSize++;
	return it;
}
