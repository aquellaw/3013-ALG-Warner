#pragma once
#include <iostream>
#include <string>
using namespace std;


struct node {
		std::string word;
		std::string definition;
		node* next;
		node(string w,string d){
			word = w;
			definition = d;
		}
	};

class MyList {
	node* head;
	node* current;
	node* end;
	int count;
public:
	MyList() {
		head = current = end = NULL;
		count  = 0;
	}

	string Find(string pattern){
		size_t found;
		ResetCursor();
		while (current != NULL) {
		
			found = current->word.find(pattern);
			//cout<<current->word<<endl;
			if(found != string::npos){
				return current->word;
			}
			if (current->next == NULL) {
				return "";
			}
			current = current->next;
		}
		return "";
	}

	void InsertItem(std::string w, std::string d) {
		ResetCursor();
		if (head == NULL) {
			head = new node(w,d);
			head->word = w;
			head->definition = d;
			end = head;
			end->next = head->next;
		}
		else {
			node* temp = new node(w,d);
			end->next = temp;
			temp->next = NULL;
			end = temp;
			end->word = w;
			end->definition = d;
		}
		++count;
	}
	int getCount() { return count; }

	void ResetCursor() {
		current = head;
	}

	void Print() {
		ResetCursor();
		while (current != NULL) {
			cout << current->word;
			if (current->next == NULL) {
				return;
			}
			cout << "->";
			current = current->next;
		}
	}

	/*
	bool search(std::string term) {
		resetcursor();
		bool found = false;
		while (current != NULL) {
			if (current->word[0] != term[0]) {
				current = current->next;
			}
			else {
				current = NULL;
			}
			while (found == true) {
				if (current->word.find(term)) {
					cout << current->word;
					current = current->next;
					found = true;
				}
				else {
					found = false;
				}
			}
			return found;
		}
	*/
};