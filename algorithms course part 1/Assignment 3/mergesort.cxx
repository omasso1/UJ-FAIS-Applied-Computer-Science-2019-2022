#include <iostream>
#include <vector>


int min(int x, int y) { return (x < y) ? x : y; }

template<typename T>
void merge(std::vector<T>& arr, std::vector<T>& aux, size_t l, size_t m, size_t r) {
    for (size_t i = l; i <= m; i++)
        aux[i] = arr[i];

    for (size_t i = m + 1; i <= r; i++)
        aux[i] = arr[r + m - i + 1];


    for (size_t k = l, i = l, j = r; k <= r; k++)
        arr[k] = (aux[j] < aux[i]) ? aux[j--] : aux[i++];

}

void mergesort(std::vector<int>& arr)
{
    size_t curr_size;
    size_t left_start;
    std::vector<int> aux(arr.size());
    for (curr_size = 1; curr_size <= arr.size() - 1; curr_size = 2 * curr_size)
    {
        for (left_start = 0; left_start < arr.size() - 1; left_start += 2 * curr_size) {
            size_t mid = min(left_start + curr_size - 1, arr.size() - 1);
            size_t right_end = min(left_start + 2 * curr_size - 1, arr.size() - 1);
            merge(arr, aux, left_start, mid, right_end);
        }
    }
}




int main() {
    std::vector<int> arr;
    int a;
    while (std::cin >> a) {
        arr.push_back(a);
    }
    mergesort(arr);
    for (auto it : arr) {
        std::cout << it << std::endl;
    }



	return 0;
}