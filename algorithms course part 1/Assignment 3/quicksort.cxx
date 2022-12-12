#include <iostream>
#include <vector>
#include "stack.h"

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}


void quicksort(std::vector<int>& arr){
    Stack<size_t> leftStack(arr.size());
    Stack<size_t> rightStack(arr.size());
    leftStack.push(0);
    rightStack.push(arr.size() - 1);
    while (!leftStack.empty()) {
        int left = leftStack.pop();
        int right = rightStack.pop();
        int pivot = arr[(left + right) / 2];
        int i = left;
        int j = right;
        do
        {
            while (arr[i] < pivot)
                i++;

            while (arr[j] > pivot)
                j--;

            if (i <= j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        } while (i <= j);

        if (left < j) {
            leftStack.push(left);
            rightStack.push(j);
        }
        if (right > i) {
            leftStack.push(i);
            rightStack.push(right);
        }
    }
}

int main() {
    std::vector<int> arr;
    int a;
    while (std::cin >> a) {
        arr.push_back(a);
    }
    quicksort(arr);
    for (auto it : arr) {
        std::cout << it << std::endl;
    }

	return 0;
}