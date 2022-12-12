#include <iostream>
#include "LinkedList.hpp"



int main() {
	try {
		LinkedList<int> linkedList;
		LinkedList<int>::Iterator it;
		char x;
		int counter;
		int a;
		int b;

		std::cin >> counter;
		while (counter--) {
			std::cin >> x;
			switch (x) {
			case 'F':
				std::cin >> a;
				linkedList.push_front(a);
				break;
			case 'B':
				std::cin >> a;
				linkedList.push_back(a);
				break;
			case 'f':
				if (linkedList.empty())
					std::cout << "EMPTY"<<std::endl;
				else
					std::cout << linkedList.pop_front() << std::endl;
				break;
			case 'b':
				if (linkedList.empty())
					std::cout << "EMPTY" << std::endl;
				else
					std::cout << linkedList.pop_back() << std::endl;
				break;
			case 'R':
				std::cin >> a;
				std::cin >> b;
				it = linkedList.find(a);
				if (it == linkedList.end())
					std::cout << "FALSE" << std::endl;
				else {
					it = linkedList.insert(it, b);
					it++;
					linkedList.erase(it);
					std::cout << "TRUE" << std::endl;
				}
				break;
			case 'S':
				std::cout << linkedList.size() << std::endl;
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
