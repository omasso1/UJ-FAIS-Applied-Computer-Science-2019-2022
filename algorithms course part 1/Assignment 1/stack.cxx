#include <iostream>
#include "stack.hxx"

#include <vector>


int main() {
	try {
		
		Stack<int, 1000000> s;
		
		char x;
		int a;
		int c;
		std::cin >> a;
		while (a--) {
			std::cin >> x;
			switch (x) {
				case 'A': 
					std::cin >> c; s.push(c); 
					break;

				case 'D': 
					if (s.empty())
						std::cout << "EMPTY" << std::endl;
					else
						std::cout << s.pop() << std::endl;
					break;

				case 'S': std::cout << s.size() <<std::endl; break;
				default: break;
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
