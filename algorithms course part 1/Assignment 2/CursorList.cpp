#include <iostream>
#include "CursorList.hpp"

#include <vector>


int main() {
	try {
		CursorList<int> cursorList;

		char x;
		int counter;
		int a;
		int b;
		CursorList<int>::Iterator it;
		std::cin >> counter;
		while (counter--) {
			std::cin >> x;
			switch (x) {
			case 'F':
				std::cin >> a;
				cursorList.push_front(a);
				break;
			case 'B':
				std::cin >> a;
				cursorList.push_back(a);
				break;
			case 'f':
				if (cursorList.empty())
					std::cout << "EMPTY"<<std::endl;
				else
					std::cout << cursorList.pop_front() << std::endl;
				break;
			case 'b':
				if (cursorList.empty())
					std::cout << "EMPTY" << std::endl;
				else
					std::cout << cursorList.pop_back() << std::endl;
				break;
			case 'R':
				std::cin >> a;
				std::cin >> b;
				it = cursorList.find(a);
				if (it == cursorList.end())
					std::cout << "FALSE" << std::endl;
				else {
					it = cursorList.insert(it, b);
					it++;
					cursorList.erase(it);
					std::cout << "TRUE" << std::endl;
				}
				break;
			case 'S':
				std::cout << cursorList.size() << std::endl;
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
