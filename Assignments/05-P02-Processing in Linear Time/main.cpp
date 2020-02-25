///////////////////////////////////////////////////////////////////////////////
//
// Author:           Aquella Warner
// Email:            aquellawarner@hotmail.com
// Label:            P02
// Title:            Assignment #5 - Processing in Linear Time
// Course:           CMPS 3013
// Semester:         Spring 2020
//
// Description:
//       A linked list data structure is implemented and used to to store words  
//		 and their meanings from a Json file. The words can be found by simply 
//		 typing a few characters using the keyboard, and a number of 
//		 suggested words with the same characters type will be displayed
//		 on the screen.
//
// Usage:
//       Enter the first few letters of the word that is being searched for
//		 after being prompted to do so.
//
// Files:            dict_w_defs.json
//					 json.hpp
//					 JsonFacade.hpp
//					 mygetch.hpp
//					 Timer.hpp
////////////////////////////////////////////////////////////////////////////////
#include <time.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "JsonFacade.hpp"
#include "Timer.hpp"
#include "mygetch.hpp"


//using namespace std;
/*
 * Node
 *
 * Description:
 *    		A Struct which is used to create a linked list and
 * 			stores its data.
 *
 * Public Methods:
 *            wordNode()
 *			  wordNode(string w, string d)
 *
 * Private Methods:
 * 			  N/A
 * Usage:
 *
 *     		  Node* Head;		  Pointer to Head of the linked list
 *
 */
struct node
{
	std::string word;
	std::string definition;
	node *next;
	node()
	{
		word = "light";
		definition = "the natural agent that stimulates sight and makes things visible.";
	}
	node(std::string w, std::string d)
	{
		word = w;
		definition = d;
	}
};
/*
 * List
 *
 * Description:
 *      This class implements a Linked list. The list consists
 *		of nodes which contain a word and its definition, and 
 *		a pointer which connects each node to the next in the list.
 *
 * Public Methods:
 *						MyList()
 *      vector          Find(string pattern)
 *     	void			InsertItem(string w, string def)
 *      int             getCount()
 *      void            ResetCursor() 
 *		string			Print()
 * Usage:
 *
 *      MyList wordList;			 					  //Constructs a new list
 *		wordList.InsertItem(keys[i], J.getValue(keys[i])) //Pushes a key and its 
 *														  //value on the list
 */
class MyList
{
	node *head;
	node *current;
	node *end;
	int count;

public:
	/*
    * Constructor : MyList
    *
    * Description:
    * 	  	Default constructor for list 
    *
    * Params:
    *      none
    *
    * Returns:
	*      nothing
    */
	MyList()
	{
		head = current = end = NULL;
		count = 0;
	}

	/*
    * Public : Find
    *
    * Description:
    * 	  	Searches the linked list for any words which contain
	* 		a substring and stores each word found in a vector. 
    *
    * Params:
    *      string:		pattern
    *
    * Returns:
	*      vector:		a vector of words.
    */
	std::vector<std::string> Find(std::string pattern)
	{
		size_t found;
		ResetCursor();

		std::vector<std::string> results;

		while (current != NULL)
		{

			found = current->word.find(pattern);
			//cout<<current->word<<endl;
			if (found != std::string::npos)
			{
				results.push_back(current->word);
				//return current->word;
			}

			current = current->next;
		}
		return results;
	}

	/*
    * Public : InsertItem
    *
    * Description:
    * 	  	Inserts words and their definition into the linkedl list 
    *
    * Params:
    *      string :		w
	*	   string :		d
    *
    * Returns:
	*      nothing
    */
	void InsertItem(std::string w, std::string d)
	{
		ResetCursor();
		if (head == NULL)
		{
			head = new node(w, d);
			head->word = w;
			head->definition = d;
			end = head;
			end->next = head->next;
		}
		else
		{
			node *temp = new node(w, d);
			end->next = temp;
			temp->next = NULL;
			end = temp;
			end->word = w;
			end->definition = d;
		}
		++count;
	}

	/*
    * Public : getCount
    *
    * Description:
    * 	  	returns the number of words pushed onto the list
    *
    * Params:
    *      none
    *
    * Returns:
	*      int :	number of words pushed onto list.
    */
	int getCount() { return count; }

	/*
    * Public : getCount
    *
    * Description:
    * 	  		Resets cursor so it's equal to head. 
    *
    * Params:
    *      none
    *
    * Returns:
	*      nothing
    */
	void ResetCursor()
	{
		current = head;
	}

	/*
    * Public : Print
    *
    * Description:
    * 	  		Prints the items on the list 
    *
    * Params:
    *      none
    *
    * Returns:
	*      nothing
    */
	void Print()
	{
		ResetCursor();
		while (current != NULL)
		{
			std::cout << current->word;
			if (current->next == NULL)
			{
				return;
			}
			std::cout << "->";
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
					std::cout << current->word;
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

int main()
{
	MyList wordList;									//An instance of MyList class
	Timer T;											//An instance of Timer class
	JsonFacade J("dict_small.json"); 					// create instance of json class
	std::string key;				 					// key variable to access json object
	char k;							 					// holder for character being typed
	std::string word = "";			 					// var to concatenate letters to


	std::vector<std::string> keys = J.getKeys();		//Vector which holds the words from dictionary file
	std::vector<std::string> results;	

	int size = keys.size();

	//Loop to populate a list
	for (int i = 0; i < size; i++)						
	{
		wordList.InsertItem(keys[i], J.getValue(keys[i]));
	}
	
	std::cout << "Type keys and watch what happens. Type capital Q to quit.\n";

	// While capital Q is not typed keep looping
	while ((k = getch()) != 'Q')						
	{
		// append char to word
		word += k; 										

		if ((int)k != 10)
		{ 
			// if k is not a space print it
			std::cout << word<<"\n";					
		}
		// hitting enter sets word back to empty
		else											
		{
			std::cout << "Enter pressed ... Word is empty\nWord: " << std::endl;
			word = "";
		}

		//Start timer.
		T.Start();										
	
		int Lsize = wordList.getCount();

		// Searching for substd::strings of value stored in word.
		//Words which contain the substring are returned to a vector.
		results = wordList.Find(word);				

		//End timer
		T.End();

		double AmtTime = T.Seconds();
		int Totalwords =results.size();

		std::cout << std::endl<<Totalwords << " were found in " << AmtTime << " seconds.\n\n";

		for (int i = 0; i < Totalwords; i++)
		{
			if(i >= 10){
				break;
			}
			std::cout << results[i] << " ";
			
		}
		std::cout<<std::endl;
		results.clear();
		std::cout<<std::endl;
	}
	return 0;
}