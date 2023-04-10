#include "simpleai.h"

int readMaxGuess()
{
	int maxGuess;
	cout << endl << "Enter the number of incorrect guesses: ";
	cin >> maxGuess;
	return maxGuess;
}

int readWordLen()
{
	int wordLen;
	cout << endl << "Enter the number characters of your secret word: ";
	cin >> wordLen;
	return wordLen;

}

/***
	Args:
		wordLen (int): The desired length of input word
		vocabulary (vector<string>): The vocabulary
	Returns:
		answer (vector<string>) : A set or word from the vocabulary where the number of character is equal to wordLen
***/
vector<string> filterWordsByLen(int wordlen, const vector<string>& vocabulary)
{
	vector<string> answer;
	//write your code here
	for (string word : vocabulary) {
		if (int(word.length()) == wordlen) {
			answer.push_back(word);
		}
	}
	return answer;
}

/***
	Args:
		selectedChars (set<char>): The predicted characters
	Returns:
		answer (char) : The next character given the provided word is not in the vocabulary
***/

char nextCharWhenWordIsNotInDictionary(const set<char>& selectedChars)
{
	char answer=' ';
	//Write your code here
	
	for (int i = 'a'; i < 'z'; i++) {
		if (selectedChars.count(char(i)) == 0) {
			answer = char(i);
			break;
		}
	}
	return answer;
}

/***
	Args:
		candidateWords (vector<string>): The candidate words for the current given string
	Returns:
		answer (map) : The map which count the occurences of character in the set of candidate words
***/

map<char, int> countOccurrences(const vector<string>& candidateWords)
{
	map<char, int> answer;
	//Write your code here
	for (string word : candidateWords) {
		for (char ch : word) {
			answer[ch]++;
		}
	}
	return answer;
}

/***
	Args:
		occurrences (map<char, int>): The map which count the occurences of character in the set of candidate words
		selectedChars (set<char>): The predicted characters
	Returns:
		answer (char) : The most frequent character
***/

char findMostFrequentChar(const map<char, int>& occurrences, const set<char>& selectedChars)
{
	char answer=' ';
	//Write your code here
	int f = 0;
	for (char ch : selectedChars) {
		if (occurrences.at(ch) > f) {
			f = occurrences.at(ch);
			answer = ch;
		}
	}
	return answer;
}

/***
	Args:
		candidateWords (vector<string>): The candidate words for the current given string
		selectedChars (set<char>): The predicted characters
	Returns:
		answer (char) : The most suitable character for prediction
***/

char findBestChar(const vector<string>& candidateWords, const set<char>& selectedChars)
{
	char answer=' ';
	//Write your code here
	answer = findMostFrequentChar(countOccurrences(candidateWords), selectedChars);
	return answer;
}

string getWordMask(char nextChar)
{
	string mask;
	cout << "The next char is: " << nextChar << endl;
	cout << "Please give me your answer: ";
	cin >> mask;
	return mask;
}

/***
	Args:
		ch (char): The predicted character by the AI
		mask (string): The response mask by the player
	Returns:
		answer (bool) : return False if the predicted character is the wrong one, True otherwise
***/

bool isCorrectChar(char ch, const string& mask)
{
	bool answer = false;
	//Write your code here
	for (int i = 0; i < int(mask.length()); i++) {
		if (ch == mask[i]) {
			answer = true;
			break;
		}
	}
	return answer;
}

/***
	Args:
		mask (string): The response mask by the player
	Returns:
		answer (bool) : return False if the provided mask is not a whole word, True otherwise
		(Example: -False: g__d
				  -True:  good)
***/
bool isWholeWord(const string& mask)
{
	//Write your code here
	for (char x : mask) {
		if (x == '_' or x== '-') {
			return 0;
		}
	}
	return 1;
}

/***
	This function should be used to support the filterWordsByMask function below
	Args:
		mask (string): The response mask by the player
		word (string): input word
		ch (char): The predicted character by the AI
	Returns:
		answer (bool) : return False if the provided mask and the given word is not in the same form.
		Example: - False: mask(-ood), char 'd' vs word(boot)
				 - True: mask(-ood), char 'd'  vs word(good)

***/
bool wordConformToMask(const string& word, const string& mask, char ch)
{
	bool answer = true;
	//Write your code here
	bool inword = false;
	for (char x : word) {
		if (ch == x) {
			inword = true;
			break;
		}
	}
	if (inword) {
		for (int i = 0; i<int(mask.length()); i++){
			if (mask[i] != '_' and mask[i]!='-') {
				if (mask[i] != word[i]) {
					answer = false;
					break;
				}
			}

		}
	}
	else {
		answer = false;
	}
	return answer;
}

/***
	Args:
		mask (string): The response mask by the player
		words (vector<string>): The candidate words
		ch (char): The predicted character by the AI
	Returns:
		answer (bool) : a list of word which satisfiy the mask and the predicted character
		Examples: input words: (good,boot,hood,...)
				  input mask: -ood
				  predicted char: d
				  Return: good,hood
***/
vector<string> filterWordsByMask(const vector<string>& words, const string& mask, char ch)
{
	vector<string> answer;
	/*Write your code here
	for (string word : words) {
		bool check = true;
		for (int i = 0; i<int(word.length()); i++) {
			if (mask[i] != '_' and mask[i] != '-') {
				if (mask[i] != word[i]) {
					check = false;
				}
			}
		}
		if (check) {
			bool inword = false;
			for (auto x : word) {
				if (ch == x) {
					inword = true;
					break;
				}
			}
			if (inword) {
				answer.push_back(word);
			}
		}
	}*/
	for (string word : words) {
		if (wordConformToMask(word, mask, ch)) answer.push_back(word);
	}
	return answer;
}