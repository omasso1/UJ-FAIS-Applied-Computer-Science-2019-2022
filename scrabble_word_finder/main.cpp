#include <iostream>
#include <exception>
#include "TreeBasedDictionary.h"


#define WINDOWS 1
#define LINUX 2

#define OPERATING_SYSTEM LINUX
#define SYSTEM(x)  if(system(x)!=0) throw new std::runtime_error("funkcja 'system' error");


#if OPERATING_SYSTEM == WINDOWS
#define CLEAN() SYSTEM("cls")
#elif OPERATING_SYSTEM == LINUX
#define CLEAN() SYSTEM("clear")
#endif


void dodajSlowo(TreeBasedDictionary&);
void usunSlowo(TreeBasedDictionary&);
void sprawdzSlowo(TreeBasedDictionary&);
void stworzSlowa(TreeBasedDictionary&);
void cleanWord(std::string&);

int main(int argc, char* args[]) {
	try {
		CLEAN();
		std::string path = "./CollinsScrabbleWords2019.txt";

		if (argc == 2) {
			path = args[1];
		}

		TreeBasedDictionary a(path);

		bool flag = true;
		char wybor;
		while (flag) {
			std::cout << "MENU" << std::endl;
			std::cout << "1. Dodaj slowo" << std::endl;
			std::cout << "2. Usun slowo" << std::endl;
			std::cout << "3. Sprawdz slowo" << std::endl;
			std::cout << "4. Stworz slowa" << std::endl;
			std::cout << "5. Zakoncz" << std::endl;
			wybor = getchar();
			switch (wybor) {
			case '1': dodajSlowo(a);	break;
			case '2': usunSlowo(a);		break;
			case '3': sprawdzSlowo(a);  break;
			case '4': stworzSlowa(a);	break;
			case '5': flag = false;		break;
			default: break;
			}
			CLEAN();
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}







void cleanWordExceptQuestionMark(std::string& word) {
	for (int i = word.size() - 1; i >= 0; i--) {
		if ((word[i] < 'A' || word[i] > 'Z') && (word[i] < 'a' || word[i] > 'z') && word[i] != '?')
			word.replace(i, 1, "");
	}
}


std::string inputWord() {
	std::cout << "Podaj slowo: " << std::endl;
	std::string word;
	std::cin >> word;
	cleanWord(word);
	return word;
}

void dodajSlowo(TreeBasedDictionary& dictionary) {
	CLEAN();
	std::string word = inputWord();
	std::cout << word<<std::endl;
	dictionary.addWord(word);
}
void usunSlowo(TreeBasedDictionary& dictionary) {
	CLEAN();
	std::string word = inputWord();
	dictionary.deleteWord(word);
}
void sprawdzSlowo(TreeBasedDictionary& dictionary) {
	CLEAN();
	std::string word = inputWord();
	std::cout << (dictionary.wordExists(word) ? "Slowo jest w slowniku" : "Slowo nie istnieje") << std::endl;
	SYSTEM("pause");
}

void stworzSlowa(TreeBasedDictionary& dictionary) {
	CLEAN();
	std::cout << "Podaj litery(? dla dowolnej litery): " << std::endl;
	std::string word;
	std::cin >> word;
	cleanWordExceptQuestionMark(word);
	auto results = dictionary.createWords(word);
	for (auto it : results) {
		std::cout << it.first << " za " << it.second << " punktow\n";
	}
	std::cout<<std::endl;
	SYSTEM("pause");
}