#include <iostream>
#include "ArrayList.hpp"



int main() {
	try {
		ArrayList<int> arrayList;

		char x;
		int counter;
		int a;
		int b;
		std::cin >> counter;
		ArrayList<int>::Iterator it;
		while (counter--) {
			std::cin >> x;
			switch (x) {
			case 'F':
				std::cin >> a;
				arrayList.push_front(a);
				break;
			case 'B':
				std::cin >> a;
				arrayList.push_back(a);
				break;
			case 'f':
				if (arrayList.empty())
					std::cout << "EMPTY"<<std::endl;
				else
					std::cout << arrayList.pop_front() << std::endl;
				break;
			case 'b':
				if (arrayList.empty())
					std::cout << "EMPTY" << std::endl;
				else
					std::cout << arrayList.pop_back() << std::endl;
				break;
			case 'R':
				std::cin >> a;
				std::cin >> b;
				it = arrayList.find(a);
				if (it == arrayList.end())
					std::cout << "FALSE" << std::endl;
				else {
					it = arrayList.insert(it, b);
					it++;
					arrayList.erase(it);
					std::cout << "TRUE" << std::endl;
				}
				break;
			case 'S':
				std::cout << arrayList.size() << std::endl;
				break;
			}
		}

	}
	catch (std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Nieobslugiwany blad" << std::endl;
	}
	return 0;
}
