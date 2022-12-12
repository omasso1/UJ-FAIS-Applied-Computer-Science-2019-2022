#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>

constexpr size_t NUMBER_OF_CHARACTERS = 26;

constexpr std::pair<char, int> POINTS_FOR_LETTER[] = {
	{'A', 1}, {'B', 3}, {'C', 3}, {'D', 2},
	{'E', 1}, {'F', 4}, {'G', 2}, {'H', 4},
	{'I', 1}, {'J', 8},	{'K', 5}, {'L', 1},
	{'M', 3}, {'N', 1}, {'O', 1}, {'P', 3},
	{'Q', 10},{'R', 1}, {'S', 1}, {'T', 1},
	{'U', 1}, {'V', 4}, {'W', 4}, {'X', 8},
	{'Y', 4}, {'Z', 10}
};
class TreeBasedDictionary {
	struct Node {
		bool mIsWord;
		std::vector<Node*>  mCharacters;

		Node();
		~Node();
		Node(bool isWord);
		Node* addCharacter(char character);
		bool isWord();
		void isWord(bool flag);
		bool hasMoreChildren();
		std::vector<std::pair<std::string,int>> searchForWords(std::string availableCharacters, std::string currentWord, int currentPoints);
		std::set<char> availableLetters(std::string& availableCharacters);
	};

	Node _mRoot;

public:
	TreeBasedDictionary(const std::string& pathToFileWithWords);
	~TreeBasedDictionary();

	void addWord(const std::string& word);
	void deleteWord(const std::string& word);
	bool wordExists(const std::string& word);
	std::vector<std::pair<std::string,int>> createWords(std::string availableCharacters);

};