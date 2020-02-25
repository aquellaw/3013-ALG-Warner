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
//       describe program here thoroughly
//
// Usage:
//       how to use the program if necessary
//
// Files:            (list of all source files used in this program)
////////////////////////////////////////////////////////////////////////////////
#include <time.h>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include "JsonFacade.hpp"
#include "Timer.hpp"
#include "mygetch.hpp"
#include "LinkedList.hpp"

// using namespace std;

class List {
  struct WordNode {
    std::string word;
    std::string definition;
    WordNode *next;
    WordNode(){
        word = "";
        definition = "";
    }
    WordNode(string key,string def){
        word = key;
        definition = def;
    }
  };

 public:
  // requires : List is not created
  // ensures : List is created and empty
  List() {
    WordNode *dummyN = new WordNode;
    dummyN->next = nullptr;
    head = dummyN;
    cursor = dummyN;
    count = 0;
  }
  List(List &other) {
    std::string Word;
    WordNode *temp;
    WordNode *dummyN = new WordNode;
    dummyN->next = nullptr;
    head = dummyN;
    cursor = dummyN;
    count = 0;
    // construct empty list - same code as in default constructor goes here

    // copy items in other to this list
    other.cursor = other.head;
    while (other.cursor->next != nullptr) {
      Word = other.cursor->next->word;

      temp = new WordNode;
      temp->word = Word;
      temp->next = cursor->next;
      cursor->next = temp;
      count++;

      other.cursor = other.cursor->next;
      cursor = cursor->next;
    }
  }

  // requires : List is created
  // ensures : List is not created
  ~List() {
    WordNode *temp;
    ResetCursor();
    temp = cursor;

    while (temp != nullptr) {
      cursor = cursor->next;
      delete temp;
      temp = cursor;
    }
    // starting at head of list, delete all nodes

    head = cursor = temp = nullptr;
    // dispose of dummy node
  }

  // requires: List is created
  // ensures:  List is empty
  void ClearList() {
    ResetCursor();
    while (!CursorAtEnd()) DeleteItem();
  }

  // requires: this list and other are created
  // ensures:   this = #other and other = #list, except that cursors are at
  // heads
  void SwapLists(List &other) {
    WordNode *temp;
    int tempCount;

    // swap cursors
    temp = cursor;
    cursor = other.cursor;
    other.cursor = temp;

    // swap heads
    temp = head;
    head = other.head;
    other.head = temp;

    // swap counts
    tempCount = count;
    count = other.count;
    other.count = count;
  }

  // requires : List is created
  // ensures : List's cursor is placed before the first item in the sequence,
  //           and the sequence is unchanged
  void ResetCursor() { cursor = head; }

  // requires : L is created
  // ensures : returns true iff L's cursor is located after
  //           the last item in the sequence.  L is not changed
  bool CursorAtEnd() {
    if (cursor->next == nullptr)
      return true;
    else
      return false;
    // cursor at end
  }

  // requires : List is created and the cursor is not at the end of the sequence
  // ensures : Return in Item the item referenced by L's cursor.  The sequence
  //           is unchanged and the cursor is not moved
  // checks :  if Cursor is at the end of the list, write error message
  std::string GetCurrentItem() {
    if (cursor->next != nullptr) {
      std::string Word = cursor->next->word;
      return Word;
    } else {
      std::cout << "ERROR : cursor at end cannot get current item" << std::endl;
    }
    return "";
  }

  // requires : L is created and the cursor is not at the end of the sequence
  // ensures : the item referenced by L's cursor is set to the value of I;
  //            The sequence is unchanged otherwise and the cursor is not moved
  // checks : if Cursor is at the end of the list, write error message
  void UpdateCurrentItem(const std::string &Word) {
    if (cursor->next == nullptr)
      std::cout << "ERROR : cursor at end cannot get current item" << std::endl;
    else
      cursor->next->word = Word;
  }

  // requires : List is created and the cursor is not at the end of the sequence
  // ensures : List's cursor is advanced one position in the sequence and the
  //           sequence is unchanged
  // checks : if Cursor is at the end of the list, write error message
  void AdvanceCursor() {
    if (cursor->next == nullptr)
      std::cout << "ERROR : cursor at end cannot advance cursor" << std::endl;
    else
      cursor = cursor->next;
  }  // advance cursor

  // requires : List is created
  // ensures : Item is inserted at the position of L's cursor. Otherwise the
  //           sequence is unchanged and the cursor is located before the
  //           inserted item
  void InsertItem(const std::string &Word, const std::string &Def) {
    WordNode *temp = new WordNode;

    if (!head) {
      temp->word = Word;
      temp->definition = Def;
      temp->next = cursor->next;
      cursor->next = temp;
    } else {
      temp->word = Word;
      temp->definition = Def;
      temp->next = nullptr;
      cursor->next = temp;
    }

    count++;
  }

  void Print(){
      char ch;
      WordNode* temp = head;
      
      while(temp){
          cout<<temp->word<<" ";
          head = temp->next;
          cin.get(ch);
      }
  }

  // requires : List is created and the cursor is not at the end of the sequence
  // ensures : the item at the position referenced by L's cursor is deleted.
  //           Otherwise the sequence is unchanged and the cursor is located
  //           before the next item in the sequence
  // checks : if cursor is at the end of the list, write error message
  void DeleteItem() {
    WordNode *temp;

    if (cursor->next == nullptr)
      std::cout << "ERROR : cursor at end cannot delete item" << std::endl;
    else {
      temp = cursor->next;
      cursor->next = temp->next;
      delete temp;
      count--;
    }
  }  // delete item

  // requires: List is created
  // ensures: the number of items in the list is returned
  int getCount() { return count; }

 private:
  WordNode *head;
  WordNode *cursor;
  int count;
};

int main() {
  //List wordList, *wL;
  MyList wordList;
  Timer T;
  JsonFacade J("dict_small.json");  // create instance of json class
  std::string key;                   // key variable to access json object
  char k;                            // holder for character being typed
  std::string word = "";             // var to concatenate letters to

  std::vector<std::string> numWords;          // Stores the matching words found
  std::vector<std::string> priortyWords(10);  // Stores top ten words
  std::vector<std::string> keys = J.getKeys();

  int size = keys.size();

  for (int i = 0; i < size; i++) {
    wordList.InsertItem(keys[i], J.getValue(keys[i]));
  }

  string tkey = keys[rand()%size];
  string rdef = J.getValue(tkey);

  //wordList.Print();

  cout<<"Found"<<wordList.Find("ste")<<endl;

  exit(0);

  std::cout << "Type keys and watch what happens. Type capital Q to quit."
            << std::endl
            << std::flush;

  // While capital Z is not typed keep looping
//   while (true) {
//     k = getch();
//     if (k == 'Q') {
//       break;
//     }
//     wordList.ResetCursor();

//     if ((int)k != 10) {  // if k is not a space print it
//       // std::cout << "Key: " << k << " = " << (int)k << std::endl;
//       // std::cout << "Word: " << word << std::endl;
//       word += k;  // append char to word
//       std::cout << k;
//     }

//     // hitting enter sets word back to empty
//     // else
//     //{
//     //	std::cout << "Enter pressed ... Word is empty\nWord: " << std::endl;
//     //	word = "";
//     //}

//     T.Start();
//     // Searching for substd::strings of value stored in word,
//     // in current item in list
//     int Lsize = wordList.getCount();
//     // for (int i = 0; i < Lsize; i++) {
//     //   size_t found = wordList.GetCurrentItem().find(word);

//     //   if (found != std::string::npos) {
//     //     numWords.push_back(wordList.GetCurrentItem());

//     //     priortyWords.push_back(wordList.GetCurrentItem());
//     //   }
//     //   // std::cout << word;
//     //   // std::cout <<numWords.size();
//     //   wordList.AdvanceCursor();
//     }
//   }
//   T.End();

  // double AmtTime = T.Seconds();
  // int Totalwords = priortyWords.size();

  // std::cout << Totalwords << " were found in " << AmtTime << " seconds.\n\n";

  // for (int i = 0; i < Totalwords; i++)
  // {
  // 	std::cout << priortyWords[i] << " ";
  // }
  return 0;
}