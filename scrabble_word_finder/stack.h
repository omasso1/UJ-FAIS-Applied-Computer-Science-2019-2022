#pragma once
#include <memory>

template<typename T>
class Stack
{
public:
	std::unique_ptr<T[]> mArray;
	size_t mSize;
	size_t mCapacity;
public:
	Stack() = delete;
	Stack(size_t size);
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


template<typename T>
Stack<T>::Stack(size_t size)
	:mSize(0), mCapacity(size)
{
	mArray = std::make_unique<T[]>(size);
}

template<typename T>
Stack<T>::Stack(Stack<T>& copy)
	:mSize(copy.mSize), mCapacity(copy.mCapacity) {
	mArray = std::make_unique<T[]>(size);

	for (size_t i = 0; i < copy.mSize; ++i) {
		mArray[i] = copy.mArray[i];
	}
}

template<typename T>
Stack<T>::Stack(Stack<T>&& copy)
	:mSize(copy.mSize), mCapacity(copy.mCapacity) {
	mArray = copy.mArray.release();
	copy.mSize = 0;
}

template<typename T>
Stack<T>::~Stack() {
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& copy) {
	if (&copy != this) {
		mArray.reset();
		mArray = std::make_unique<T[]>(size);
		mSize = copy.mSize;
		mCapacity = copy.mCapacity;
		for (size_t i = 0; i < copy.mSize; ++i) {
			mArray[i] = copy.mArray[i];
		}
	}
	return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& copy) {
	if (&copy != this) {
		mArray = copy.mArray.release();
		mArray = copy.mArray;
		mSize = copy.mSize;
		mCapacity = copy.mCapacity;
		copy.mSize = 0;
	}
	return *this;
}

template<typename T>
template<typename U>
void Stack<T>::push(U&& x) {

	mArray[mSize] = std::forward<U>(x);
	++mSize;
}

template<typename T>
T Stack<T>::pop() {
	if (mSize == 0)
		throw std::out_of_range("Stos jest pusty");

	--mSize;
	return mArray[mSize];
}

template<typename T>
T& Stack<T>::top() {
	if (mSize == 0)
		throw std::out_of_range("Stos jest pusty");
	return mArray[mSize - 1];
}

template<typename T>
size_t Stack<T>::size() {
	return mSize;
}


template<typename T>
bool Stack<T>::empty() {
	return !mSize;
}
