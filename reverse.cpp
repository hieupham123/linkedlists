#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

struct dnodeptr {
	string word;
	dnodeptr* next = NULL;
	dnodeptr* prev = NULL;
	dnodeptr* list = NULL;
};

void ConvertCase(string& str);

int main(int argc, char* argv[]) {
	/*********Variables***********/
	dnodeptr *current = NULL;
	dnodeptr *head = NULL;
	dnodeptr *tail = NULL;

	dnodeptr *Bigcurrent = NULL;
	dnodeptr *Bighead = NULL;
	dnodeptr *Bigtail = NULL;
	ifstream inputfile;
	ofstream outputfile;
	string input = "test01.txt";
	string input_line;
	int count = 0;
	int countnode = 0;
	int linecount = 0;
	string tempwords = "";
	string tempwords2 = "";
	string cleanwords = "";
	bool cleanFlag;
	/******************************/

	/*******************Argument Manager********************************/
	/*if (argc < 2) {
		std::cerr << "Usage: reverse inputfile=input.txt" << std::endl;
		return -1;
	}
	ArgumentManager am(argc, argv);
	const std::string input_file_name = am.get("inputfile");
	std::cout << "input file name is " << input_file_name << std::endl;
	inputfile.open(input_file_name.c_str());
	const std::string cleanFlaginput = am.get("clean");
	if (cleanFlaginput == "y" || cleanFlaginput == "Y") {
		cleanFlag = true;
		cout << "Clean Flag = True" << endl;
	}
	else {
		cleanFlag = false;
		cout << "Clean Flag = False" << endl;
	}
	/*******************************************************************/
	inputfile.open(input);
	/*****************Checking if file opens************************/
	if (!inputfile.is_open()) {
		cout << "There is an error in opening the file." << endl;
	}
	else {
		cout << "The file is opened successfully!" << endl;
	}
	/***************************************************************/

	/*******************Gets the lines of the textfile****************/
	while (getline(inputfile, input_line)) {
		/*****************************************************************/
		ConvertCase(input_line); //Converts the lines into lowercase form.
		count++;
		tempwords = "";
		//**************************** Adds to tempwords if it is an alpha or digit ********************************************************//
		for (size_t i = 0; i < input_line.length(); i++) {
			if (isalpha(input_line[i]) || isdigit(input_line[i]) || input_line[i] == ' ') { //if it is digit or alpha
				if (input_line[i] != input_line[0]) { //if it's not the first letter
					if (isalpha(input_line[i - 1]) && isdigit(input_line[i]) || isdigit(input_line[i - 1]) && isalpha(input_line[i])) {//Split words if alpha and digit are next to each other.
						tempwords = ' ' + tempwords;
						tempwords = tempwords + ' ';
					}
				}
				tempwords = tempwords + input_line[i];
			}
			else { //replaces symbols or nonalpha and nondigits to ' '
				input_line[i] = ' ';
				tempwords = tempwords + input_line[i];
			}
		}

		tempwords2 = "";
		for (size_t i = 0; i < tempwords.length(); i++) {
			if (isalpha(tempwords[i]) || isdigit(tempwords[i])) {
				if (tempwords[i] != tempwords[0]) {
					if (isalpha(tempwords[i - 1]) && isdigit(tempwords[i]) || isdigit(tempwords[i - 1]) && isalpha(tempwords[i])) {
						tempwords2 = ' ' + tempwords2;
						tempwords2 = tempwords2 + ' ';
					}
				}
				tempwords2 = tempwords2 + tempwords[i];
			}
			else {
				tempwords[i] = ' ';
				tempwords2 = tempwords2 + tempwords[i];
			}
		}

		/************** Place words into a list of nodes and then input the list of nodes into another list of nodes. **********/
		size_t i = 0;
		while (i < tempwords2.length()) {
			/***************************** Places a word from the line of words in cleanwords********************/
			while (tempwords2[i] == ' ' && i < tempwords2.length()) {
				i++;
			}
			while (tempwords2[i] != ' ' && i < tempwords2.length()) {
				cleanwords = cleanwords + tempwords2[i];
				i++;
			}
			/****************************************************************************************************/

			/************** Places each word in a node *************/
			if (head == NULL) { //if it is the first node
				current = new dnodeptr; //creates new node
				current->word = cleanwords; //places word in node
				head = current; //head points to current
				tail = current; //tail points to current
				cleanwords = ""; //refreshes words
				countnode++;
			}
			else {
				current = new dnodeptr;
				current->word = cleanwords;
				current->prev = tail; //prev points to last node
				tail->next = current; //last node points to current
				tail = current; //tail now equals to the new current
				cleanwords = ""; //refreshes words
				countnode++;
			}
		}
		/********************************************************/
		tail->next = NULL; //Ends each node created

						   /************************ Places list of nodes into another into nodes **************/
		if (Bighead == NULL) { //if it is the first node
			Bigcurrent = new dnodeptr;
			Bigcurrent->list = tail; //points to the tail of the list of nodes
			Bighead = Bigcurrent;
			Bigtail = Bigcurrent;
			linecount++; //counts the lines
			countnode++;
		}
		else {
			Bigcurrent = new dnodeptr;
			Bigcurrent->list = tail;
			Bigcurrent->prev = Bigtail;
			Bigtail->next = Bigcurrent;
			Bigtail = Bigcurrent;
			linecount++; //counts the lines
			countnode++;
		}
		current = new dnodeptr;
		current->prev = NULL;
		head = current;
		tail = current;
	}
	/*************************************************************************************/

	outputfile.open("output.txt");

	dnodeptr* Bigtemp = Bigtail;
	dnodeptr* temp = Bigtail->list;
	int countnew = 0;
	while (Bigtemp != NULL) { //if big node still contains items
		while (temp != NULL) { //if little node still contains items
			if (cleanFlag == true) {
				if (isdigit(temp->word[0]) || temp->word == "") {
					temp->word = "NUM/EMPTY";

					//outputfile << temp->word << " ";
				}
				else {
					outputfile << temp->word << " ";
					countnew++;
				}
			}
			else {
				if (temp->word != ""){
					outputfile << temp->word << " ";
					countnew++;
				}
			}
			temp = temp->prev;	//goes dont the little node list
		}
		outputfile << endl;
		//cout << endl;
		Bigtemp = Bigtemp->prev; //goes down the big node list
		if (Bigtemp != NULL) //if big list still contains items
			temp = Bigtemp->list; //redeclares the temp
	}
	cout << "There are " << "[" << linecount << "] " << "lines in the program." << endl; //cout the amount of lines in the program
	cout << "There are " << "[" << countnode*(8 + 8 + sizeof(string)) << "] " << "bytes in the program." << endl;
	cout << "There are " << "[" << countnew*(8 + 8 + sizeof(string)) << "] " << "bytes in the program after execution." << endl;
	outputfile.close();

	inputfile.close();

	return 0;
}
/************************ Lowercase function***************/
void ConvertCase(string& str) {
	for (size_t i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}
}
/**********************************************************/