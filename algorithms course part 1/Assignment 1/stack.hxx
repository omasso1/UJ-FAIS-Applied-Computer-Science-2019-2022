#pragma once
#include <array>


template<typename T, size_t N>
class Stack
{
public:
	T* mArray;
	size_t mSize;
	size_t mCapacity;
public:
	Stack();
	Stack(Stack& copy);
	Stack(Stack&& copy);
	~Stack();
	Stack& operator=(const Stack& copy);
	Stack& operator=(Stack&& copy);

	template<class U>   // Uniwersalne referencje
	void push(U&& x);   // Wstawia element x na stos
	T pop();            // Usuwa element ze stosu i zwraca jego wartoœæ
	T& top();           // Zwraca referencjê do najm³odszego elementu
	size_t size();      // Zwraca liczbê elementów na stosie
	bool empty();       // Sprawdza czy stos jest pusty

};


template<typename T, size_t N>
Stack<T,N>::Stack()
	:mSize(0), mCapacity(N)
{
	mArray = new T[N];
}

template<typename T, size_t N>
Stack<T,N>::Stack(Stack<T, N>& copy)
	:mSize(copy.mSize), mCapacity(copy.mCapacity) {
	mArray = new T[mSize];

	for (size_t i = 0; i < copy.mSize; ++i) {
		mArray[i] = copy.mArray[i];
	}
}

template<typename T, size_t N>
Stack<T,N>::Stack(Stack<T, N>&& copy)
	:mSize(copy.mSize), mCapacity(copy.mCapacity) {
	mArray = copy.mArray;
	copy.mArray = nullptr;
	copy.mSize = 0;
}

template<typename T, size_t N>
Stack<T,N>::~Stack() {
	delete[] mArray;
}

template<typename T, size_t N>
Stack<T, N>& Stack<T,N>::operator=(const Stack<T, N>& copy) {
	if (&copy != this) {
		delete[] mArray;
		mArray = new T[copy.mCapacity];
		mSize = copy.mSize;
		mCapacity = copy.mCapacity;
		for (size_t i = 0; i < copy.mSize; ++i) {
			mArray[i] = copy.mArray[i];
		}
	}
	return *this;
}

template<typename T, size_t N>
Stack<T, N>& Stack<T,N>::operator=(Stack<T, N>&& copy) {
	if (&copy != this) {
		delete[] mArray;
		mArray = copy.mArray;
		mSize = copy.mSize;
		mCapacity = copy.mCapacity;

		copy.mArray = nullptr;
		copy.mSize = 0;
	}
	return *this;
}

template<typename T,size_t N>
template<typename U>
void Stack<T,N>::push(U&& x) { 
	if (mSize == mCapacity)
		throw std::out_of_range("Stos jest pelny");
	mArray[mSize] = std::forward<U>(x);
	++mSize;
}

template<typename T, size_t N>
T Stack<T,N>::pop() {
	if (mSize == 0)
		throw std::out_of_range("Stos jest pusty");

	--mSize;
	return mArray[mSize];
}

template<typename T, size_t N>
T& Stack<T,N>::top() {
	if (mSize == 0)
		throw std::out_of_range("Stos jest pusty");
	return mArray[mSize - 1];
}

template<typename T, size_t N>
size_t Stack<T,N>::size() {
	return mSize;
}


template<typename T, size_t N>
bool Stack<T,N>::empty() {
	return !mSize;
}