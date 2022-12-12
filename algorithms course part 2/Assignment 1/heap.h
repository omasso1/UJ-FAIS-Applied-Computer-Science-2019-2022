#include <utility>
#include <vector>
#include <algorithm>

class HeapMax {
	/*pair <key, value*>*/
	std::vector<int> mArray;
	
	int getParent(int index);
	int getLeftChild(int index);
	int getRightChild(int index);

public:
	HeapMax();
	
	void addElement(int newElement);
	int removeElement(int index);
	void heapifyUp(int index);
	void heapifyDown(int index);
	void printHeap();
	inline int size() {
		return mArray.size();
	}
};