#include <iostream>
#include <string>
#include <charconv>
#include <array>
#include <cstring>

constexpr size_t SIZE = 100000000;

void RadixSort256(unsigned int*& arr, int n){
	unsigned int* output = new unsigned int[SIZE]; 
	int* count = new int[256];
	int counts[256] = {};
	for (int s = 0; s < 32; s += 8){
		memcpy(count, counts, 256 * sizeof(int));
		for (int i = 0; i < n; i++)
			++count[(arr[i] >> s) & 0xff];

		for (int i = 1; i < 256; ++i)
			count[i] += count[i - 1];

		for (int i = n - 1; i >= 0; --i){
			int idx = (arr[i] >> s) & 0xff;
			output[--count[idx]] = arr[i];
		}

		unsigned int* tmp = arr;
		arr = output;
		output = tmp;
	}
	
	delete[] output;
	delete[] count;
}


unsigned int fast_atoi(std::string& s) {
	int i = 0;
	unsigned int number = 0;
	while (s[i] != '\0') {
		number = number * 10 + (int)s[i++] - (int)'0';
	}
	return number;
}


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	unsigned int* arr = new unsigned int[SIZE];
	int i = 0;
	for (std::string line; std::getline(std::cin, line);) {
		arr[i++] = fast_atoi(line);
	}

	RadixSort256(arr, i);

	char* buffer = new char[SIZE*11];
	size_t shift = 0;
	for (int j = 0; j < i; j++) {
		std::to_chars_result ch = std::to_chars(buffer + shift, buffer + sizeof(char) * SIZE * 11, arr[j]);
		*ch.ptr = '\n';
		shift = ch.ptr - buffer + 1;
	}
	std::cout.write(buffer, shift);
	std::cout.flush();

	delete[] arr;
	delete[] buffer;
	return 0;
}