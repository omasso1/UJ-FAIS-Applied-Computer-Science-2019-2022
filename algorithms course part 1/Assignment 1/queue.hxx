#pragma once

template<class T, size_t N>
class Queue{
private:
	T* mArray;
	size_t mTail;
	size_t mHead;
	size_t mCapacity;
	size_t mSize;

public:
	Queue();
	Queue(Queue& copy);
	Queue(Queue&& copy);
	~Queue();
	Queue& operator=(const Queue& copy);
	Queue& operator=(Queue&& copy);


	template<class U>
	void push(U && x);     // Wstawia element x do kolejki (tak�e enqueue)
	T pop();               // Usuwa element z kolejki (tak�e dequeue) i zwraca jego warto��
	T& front();            // Zwraca referencj� do najstarszego elementu (tak�e peek)
	size_t size();         // Zwraca liczb� element�w w kolejce
	bool empty();          // Sprawdza czy kolejka jest pusta
};


template<typename T, size_t N>
Queue<T, N>::Queue()
	:mArray(new T[N]),mTail(0), mHead(0),mCapacity(N),mSize(0)
{

}

template<typename T, size_t N>
Queue<T, N>::Queue(Queue<T, N>& copy)
	:mArray(new T[copy.mCapacity]),mTail(copy.mTail), mHead(copy.mHead),mCapacity(copy.mCapacity),mSize(copy.mSize)  {


	for (size_t i = 0; i < copy.mCapacity; ++i) {
		mArray[i] = copy.mArray[i];
	}
}

template<typename T, size_t N>
Queue<T, N>::Queue(Queue<T, N>&& copy)
	:mArray(new T[copy.mCapacity]),mTail(copy.mTail), mHead(copy.mHead),mCapacity(copy.mCapacity),mSize(copy.mSize) {
	mArray = copy.mArray;
	copy.mArray = nullptr;
	copy.mSize = 0;
	copy.mCapacity = 0;
	copy.mTail = 0;
	copy.mHead = 0;
}

template<typename T, size_t N>
Queue<T, N>::~Queue() {
	delete[] mArray;
}

template<typename T, size_t N>
Queue<T, N>& Queue<T, N>::operator=(const Queue<T, N>& copy) {
	if (&copy != this) {
		delete[] mArray;
		mArray = new T[copy.mCapacity];
		mSize = copy.mSize;
		mCapacity = copy.mCapacity;
		mTail = copy.mTail;
		mHead = copy.mHead;
		for (size_t i = 0; i < copy.mCapacity; ++i) {
			mArray[i] = copy.mArray[i];
		}
	}
	return *this;
}

template<typename T, size_t N>
Queue<T, N>& Queue<T, N>::operator=(Queue<T, N>&& copy) {
	if (&copy != this) {
		delete[] mArray;
		mArray = copy.mArray;
		mSize = copy.mSize;
		mCapacity = copy.mCapacity;
		mTail = copy.mTail;
		mHead = copy.mHead;

		copy.mArray = nullptr;
		copy.mSize = 0;
		copy.mCapacity = 0;
		copy.mTail = 0;
		copy.mHead = 0;
	}
	return *this;
}







template<class T, size_t N>
template<class U>
void Queue<T, N>::push(U&& x) {
	if (mSize == mCapacity)
		throw std::out_of_range("Kolejka jest pelna");

	mArray[mHead] = std::forward<U>(x);
	mHead = (mHead + 1) % mCapacity;
	++mSize;
}



template<class T, size_t N>
T Queue<T, N>::pop(){
	if (mSize == 0)
		throw std::out_of_range("Kolejka jest pusta");

	size_t tempTail = mTail;
	mTail = (mTail + 1) % mCapacity;
	--mSize;
	return mArray[tempTail];
}

template<class T, size_t N>
T& Queue<T, N>::front(){
	if (mSize == 0)
		throw std::out_of_range("Kolejka jest pusta");
	return mArray[mTail];
}

template<class T, size_t N>
size_t Queue<T, N>::size(){
	return mSize;
}

template<class T, size_t N>
bool Queue<T, N>::empty(){
	return !mSize;
}
