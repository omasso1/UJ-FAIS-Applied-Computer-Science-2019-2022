#include "TreeBasedDictionary.h"
#include <iostream>
#include <fstream>
#include <set>
#include <exception>
#include "stack.h"

void cleanWord(std::string& word) {
	for (int i = word.size() - 1; i >= 0; i--) {
		if ((word[i] < 'A' || word[i] > 'Z') && (word[i] < 'a' || word[i] > 'z'))
			word.replace(i, 1, "");
	}
}


TreeBasedDictionary::TreeBasedDictionary(const std::string& pathToFileWithWords)
	:_mRoot()
{
	std::ifstream file(pathToFileWithWords);
	if (file.good()) {
		std::string word;

		while (std::getline(file, word)) {
			cleanWord(word);
			addWord(word);
		}
		file.close();
	}
	else {
		throw std::invalid_argument("Podano zla sciezke do slownika");
	}
}

TreeBasedDictionary::~TreeBasedDictionary()
{}


char upperCase(char letter) {
	if (letter >= 'a' && letter <= 'z')
		return letter - 32;
	return letter;
}

std::string upperCase(std::string& word) {
	std::string returnString = "";
	for (auto l : word) {
		returnString += upperCase(l);
	}
	return returnString;
}
size_t letterToIndex(char letter) {
	return upperCase(letter) - 'A';
}

std::string deleteOneLetter(std::string str, char letter) {
	auto it = str.find(letter);
	return str.replace(it, 1, "");
}


char indexToLetter(size_t index) {
	return (char)index + 'A';
}


int pointsForLetter(char letter) {
	return POINTS_FOR_LETTER[letterToIndex(letter)].second;
}

void TreeBasedDictionary::addWord(const std::string& word){
	if (word == "")
		return;

	size_t currentIndex = 0;
	Node* ptr = &_mRoot;
	while (word[currentIndex] != '\0') {
		ptr = ptr->addCharacter(word[currentIndex]);
		currentIndex++;
	}
	ptr->isWord(true);
}

void TreeBasedDictionary::deleteWord(const std::string& word)
{
	if (!wordExists(word))
		return;

	Stack<std::pair<Node*, size_t>> stack(16);
	size_t currentIndex = 0;
	Node* ptr = &_mRoot;
	while (word[currentIndex] != '\0') {
		size_t idx = letterToIndex(word[currentIndex]);
		currentIndex++;
		ptr = ptr->mCharacters[idx];
		stack.push(std::pair<Node*, size_t>(ptr, currentIndex));
	}
	ptr->isWord(false);
	

	while (!ptr->hasMoreChildren() && !stack.empty()) {
		auto pair = stack.pop();
		ptr = pair.first;
		delete ptr->mCharacters[pair.second];
		ptr->mCharacters[pair.second] = nullptr;
	}
}

bool TreeBasedDictionary::wordExists(const std::string& word)
{
	Node* ptr = &_mRoot;
	size_t currentIndex = 0;
	while (word[currentIndex] != '\0' && ptr !=nullptr) {
		size_t idx = letterToIndex(word[currentIndex]);
		ptr = ptr->mCharacters[idx];
		currentIndex++;
	}

	if (ptr != nullptr && ptr->isWord())
		return true;
	else
		return false;
}

std::vector<std::pair<std::string,int>> TreeBasedDictionary::createWords(std::string availableCharacters)
{
	return _mRoot.searchForWords(upperCase(availableCharacters),"",0);
}

TreeBasedDictionary::Node::Node()
	:mIsWord(false), mCharacters(NUMBER_OF_CHARACTERS)
{
	
}

TreeBasedDictionary::Node::~Node()
{
	for (auto it : mCharacters)
		delete it;
}

TreeBasedDictionary::Node::Node(bool isWord)
	: mIsWord(isWord)
{
	
}

TreeBasedDictionary::Node* TreeBasedDictionary::Node::addCharacter(char character)
{
	size_t idx = letterToIndex(character);
	if (mCharacters[idx] == nullptr)
		mCharacters[idx] = new Node();
	return mCharacters[idx];
}

bool TreeBasedDictionary::Node::isWord()
{
	return mIsWord;
}

void TreeBasedDictionary::Node::isWord(bool flag){
	mIsWord = flag;
}

bool TreeBasedDictionary::Node::hasMoreChildren()
{
	for (auto it : mCharacters)
		if (it != nullptr)
			return true;
	return false;
}


std::set<char> TreeBasedDictionary::Node::availableLetters(std::string& availableCharacters)
{
	std::set<char> idxs;
	for (int i = availableCharacters.size() - 1 ; i >=0 ; i--) {
		if (availableCharacters[i] != '?') {
			size_t idx = letterToIndex(availableCharacters[i]);
			if (mCharacters[idx] != nullptr) {
				idxs.insert(availableCharacters[i]);
			}
		}
	}
	return idxs;
}



std::vector<std::pair<std::string,int>> TreeBasedDictionary::Node::searchForWords(std::string availableCharacters, std::string currentWord, int currentPoints)
{
	std::vector<std::pair<std::string, int>> words;
	if (this->isWord())
		words.push_back({ currentWord, currentPoints });

	if (availableCharacters.find("?") != std::string::npos) {
		for (char letter = 'A'; letter <= 'Z'; letter++) {
			std::string remainingCharacters;
			int points = currentPoints;
			if (availableCharacters.find(letter) != std::string::npos) {
				remainingCharacters = std::move(deleteOneLetter(availableCharacters, letter));
				points += pointsForLetter(letter);
			}
			else
				remainingCharacters = std::move(deleteOneLetter(availableCharacters, '?'));
			if(mCharacters[letterToIndex(letter)] != nullptr){
				std::vector<std::pair<std::string,int>> newWords = std::move(mCharacters[letterToIndex(letter)]->searchForWords(remainingCharacters, currentWord + letter, points));
				words.insert(words.end(), newWords.begin(), newWords.end());
			}
		}
	}
	else {
		std::set<char> availableLetters = std::move(this->availableLetters(availableCharacters));
		for (auto letter : availableLetters) {
			int points = currentPoints + pointsForLetter(letter);
			std::string remainingCharacters = std::move(deleteOneLetter(availableCharacters, letter));
			std::vector<std::pair<std::string,int>> newWords = std::move(mCharacters[letterToIndex(letter)]->searchForWords(remainingCharacters, currentWord + letter, points));
			words.insert(words.end(), newWords.begin(), newWords.end());
		}
	}	

	return words;
}


