#include <stdexcept>
#include <iostream>

#include "heap.h"


void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int HeapMax::getParent(int index)
{
	return (index - 1) / 2;
}

int HeapMax::getLeftChild(int index)
{
	return (index * 2 + 1) < mArray.size() ? (index * 2 + 1) : index;
}

int HeapMax::getRightChild(int index)
{
	return (index * 2 + 2) < mArray.size() ? (index * 2 + 2) : index;
}

HeapMax::HeapMax()
{
}

void HeapMax::addElement(int newElement)
{
	mArray.push_back(newElement);
	heapifyUp(mArray.size() - 1);
}

int HeapMax::removeElement(int index)
{	
	if (index >= mArray.size())
		throw new std::out_of_range("Index too big");
	int returnValue = mArray[index];
	swap(mArray[mArray.size() - 1], mArray[index]);
	mArray.pop_back();
	heapifyDown(index);
	
	return returnValue;
}

void HeapMax::heapifyUp(int index)
{
	while (index != 0) {
		if (mArray[index] < mArray[getParent(index)]) {
			swap(mArray[index], mArray[getParent(index)]);
			index = getParent(index);
		}
		else return;
	}
}

void HeapMax::heapifyDown(int index)
{
	if (index < mArray.size()) {
		while (mArray[index] > mArray[getLeftChild(index)] || mArray[index] > mArray[getRightChild(index)]) {
			int minIndex = mArray[getLeftChild(index)] < mArray[getRightChild(index)] ? getLeftChild(index) : getRightChild(index);
			swap(mArray[index], mArray[minIndex]);
			index = minIndex;
		}
	}
}


void HeapMax::printHeap() {
	for (auto it : mArray)
		std::cout << it << "\n";
}