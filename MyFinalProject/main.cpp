#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <random>
#include <ctime>
using namespace std;

class Verse
{
public:
	string book;
	int bookNum;
	int chapter;
	int verse;
	string text;
};

vector<string> splitRecord_withStringStream(const string& record, char delimiter)
{
	vector<string> fields;
	stringstream stringStream(record);
	string field;
	while (getline(stringStream, field, delimiter))
	{
		fields.push_back(field);
	}
	return fields;
}

void searchWord(vector<Verse>& verses, string keyWord) //search from algorithm library
{
	bool wordInVerse = false;
	for (const auto& verse : verses)
	{
		auto result = search(verse.text.begin(), verse.text.end(), keyWord.begin(), keyWord.end());
		if (result != verse.text.end())
		{
			cout << verse.book << " " << verse.chapter << " : " << verse.verse << " - " << verse.text << endl;
			wordInVerse = true;
		}
	}
	if (wordInVerse == false)
	{
		cout << "This word is not in the Bible." << endl;
	}
}

void searchForVerse(vector<Verse>& verses, string searchBook, int chaptNum, int verseNum)
{

	bool verseFound = false;
	for (int i = 0; i < verses.size(); i++)
	{
		if (verses[i].book == searchBook && verses[i].chapter == chaptNum && verses[i].verse == verseNum)
		{
			cout << verses[i].book << " " << verses[i].chapter << " : " << verses[i].verse << " - " << verses[i].text << endl;
			verseFound = true;
		}
	}
	if (verseFound == false)
	{
		cout << "This is not a real verse." << endl;
	}
}

void searchForBook(vector<Verse>& verses, string searchBook)
{
	bool bookFound = false;
	for (int i = 0; i < verses.size(); i++)
	{
		if (verses[i].book == searchBook)
		{
			cout << verses[i].chapter << " : " << verses[i].verse << " - " << verses[i].text << endl;
			bookFound = true;
		}
	}
	if (bookFound == false)
	{
		cout << "This is not a book in the Bible." << endl;
	}
}

void randomVerse(vector<Verse>& verses)
{
	int i = rand() % verses.size();
	cout << verses[i].book << " " << verses[i].chapter << " : " << verses[i].verse << " - " << verses[i].text << endl;
}

map<string, int> countVerses(vector<Verse>&verses) //counts how many verses are in each book
{
	map<string, int> mappyMcMapster;
	for (int i = 0; i < verses.size(); i++)
	{
		mappyMcMapster[verses[i].book]++;
	}
	return mappyMcMapster;
}

void longestVerse(vector<Verse>& verses)
{
	int maxLength = 0;
	for (int i = 1; i < verses.size(); i++)
	{
		if (verses[i].text.length() > verses[maxLength].text.length())
		{
			maxLength = i;
		}
	}
	cout << verses[maxLength].text << endl;
}

void shortestVerse(vector<Verse>& verses)
{
	int minLength = 0;
	for (int i = 1; i < verses.size(); i++)
	{
		if (verses[i].text.length() < verses[minLength].text.length())
		{
			minLength = i;
		}
	}
	cout << verses[minLength].text << endl;
}

int main()
{
	std::ifstream inputFile("C:/Users/jewel/Downloads/kjv_data.txt");
	if (!inputFile)
	{
		cout << "FNFR\n";
		return -1;
	}

	vector<Verse> verses; //list of verse objects
	string currentLine;

	getline(inputFile, currentLine);
	while (getline(inputFile, currentLine))
	{
		if (currentLine.empty()) continue;
		vector<string> splitRecord = splitRecord_withStringStream(currentLine, '\t');
		if (splitRecord.size() < 6) continue;
		Verse currentRecord;
		currentRecord.book = splitRecord[1];
		currentRecord.bookNum = stoi(splitRecord[2]);
		currentRecord.chapter = stoi(splitRecord[3]);
		currentRecord.verse = stoi(splitRecord[4]); // stoi string to integer
		currentRecord.text = splitRecord[5];
		verses.push_back(currentRecord); // puts verse into list of verses
	}

	int option;
	string keyWord;
	int chaptNum;
	int verseNum;
	string searchBook;
	map<string, int> bookCounts = countVerses(verses);
	srand(static_cast<unsigned int>(time(0)));
	cout << "Hello :) This program is intended to allow you to search through Bible Verses from the KJV Version.\n\n";
	do
	{
		cout << "Please choose how you would like to search: \n0. Exit\n1. Search by Keyword\n2. Search for Verse\n3. Search for Book\n4. Random Verse\n5. Search for Number of Verses in a Book\n6. Longest Verse\n7. Shortest Verse" << endl;
		cin >> option;

		switch (option)
		{
		case 1: //Search for Keyword
			cout << "Please enter the word you would like to search for: ";
			cin >> keyWord;
			cout << "Entering Keyword search..." << endl;
			searchWord(verses, keyWord);
			break;
		case 2: //Search for Verse
			cout << "Please enter the book of the verse you would like to search for: ";
			cin >> searchBook;
			cout << "Please enter the chapter number of the verse you would like to search for: ";
			cin >> chaptNum;
			cout << "Please enter the verse number of the verse you would like to search for: ";
			cin >> verseNum;
			cout << "Searching for Verse..." << endl;
			searchForVerse(verses, searchBook, chaptNum, verseNum);
			break;
		case 3: //Search for Book
			cout << "Please enter the book you would like to search for (Please Capitalize): ";
			cin >> searchBook;
			cout << "Searching for Book..." << endl;
			searchForBook(verses, searchBook);
			break;
		case 4: //Random Verse
			cout << "Generating a random verse..." << endl;
			randomVerse(verses);
			break;
		case 5: // Number of Verses in book
			cout << "Please enter the book you would like to search the number of verses for: ";
			cin >> searchBook;
			cout << "Counting number of verses in book..." << endl;
			cout << bookCounts[searchBook] << "\n\n";
			break;
		case 6: // Longest Book
			cout << "Searching for the Longest Verse..." << endl;
			longestVerse(verses);
			break;
		case 7: // Shortest Book
			cout << "Searching for the Shortest Verse..." << endl;
			shortestVerse(verses);
			break;
		case 0: //Exit
			cout << "Exiting program...\n";
			break;
		default:
			cout << "Invalid choice, please try again." << endl;
			break;
		}
	} while (option != 0);
	return 0;
}