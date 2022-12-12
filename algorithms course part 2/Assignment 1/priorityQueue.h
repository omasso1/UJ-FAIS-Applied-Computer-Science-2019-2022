#pragma once
#include "heap.h"

class PriorityQueue {
	HeapMax m_queue;

public:
	void push(int key);
	int pop();
	bool empty();
};