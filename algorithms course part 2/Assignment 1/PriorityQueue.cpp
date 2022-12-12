#include "priorityQueue.h"

void PriorityQueue::push(int key)
{
	m_queue.addElement(key);
}

int PriorityQueue::pop()
{
	return m_queue.removeElement(0);
}



bool PriorityQueue::empty()
{
	return !m_queue.size();
}
