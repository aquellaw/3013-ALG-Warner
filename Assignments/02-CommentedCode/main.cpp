///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Aquella Warner
// Email:            aquellawarner@hotmail.com
// Label:            A02
// Title:            Linked List Class
// Course:           CMPS 3013
// Semester:         Spring 2020
//
// Description:
//       This program implements a class that allows a linked list to be used just like 
//       an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
//       array elements, but really it traverses the list to find the specified node using
//       an index value. It also overloads the "+" and "-" signs allowing a user to "add"
//       or "push" items onto the end of the list, as well as "pop" items off the end of our 
//       array. This class is not meant to replace the STL vector library, its simply a project
//       to introduce the beginnings of creating complex / abstract data types. 
//       
// Usage: 
//      - $ ./main filename
//      - This will read in a file containing whatever values to be read into our list/array. 
//      
// Files:            
//      main.cpp    : driver program 
//      list.h      : header file with list defintion
//      list.cpp    : list implementation
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

int A[100];

struct Node {
    int x;
    Node *next;
    Node() {
        x = -1;
        next = NULL;
    }
    Node(int n) {
        x = n;
        next = NULL;
    }
};
/**
 * List
 * 
 * Description:
 *      Description of your class and what it does
 * 
 * Public Methods:
 *                          List()
 *      void                Push(int value)
 *      void                Insert()
 *      void                Printtail()
 *      string              print()
 *      int                 pop()
 * 
 * Private Methods:
 *      - A list of 
 *      - each private method
 *      - with return types
 * 
 * Usage: 
 * 
 *      - examples of how
 *      - to use your class 
 *      
 */
class List {
private:
    Node *Head;
    Node *Tail;
    int Size;

public:
     /**
     * Public : List
     * 
     * Description:
     *      Initializes private member variables
     * 
     * Params:
     *     None
     * 
     * Returns:
     *     None
     */
    List() {
        Head = Tail = NULL;
        Size = 0;
    }

     /**
     * Public : Push
     * 
     * Description:
     *      Pushes a value at the end of a linked list.
     * 
     * Params:
     *      int     :  value being pushed onto list.
     * 
     * Returns:
     *      Void   : does not return anything
     */
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

     /**
     * Public : Insert
     * 
     * Description:
     *      Inserts at the head of a linked list.
     * 
     * Params:
     *      int    : value being pushed onto list.
     * 
     * Returns:
     *      Void   : does not return anything
     */
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

     /**
     * Public : PrintTail
     * 
     * Description:
     *      Prints the value stored in memory location tail points to.
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      Void    : does not return anything.
     */
    void PrintTail() {
        cout << Tail->x << endl;
    }

     /**
     * Public : Print
     * 
     * Description:
     *      Loads an array of integerts into a linked list.
     * 
     * Params:
     *      int*    :  array of integers
     *      int     :  array size
     * 
     * Returns:
     *      string   : a word.
     */
    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

     /**
     * Public : Pop
     * 
     * Description:
     *      Loads an array of integerts into a linked list.
     * 
     * Params:
     *      int*    :  array of integers
     *      int     :  array size
     * 
     * Returns:
     *      List*   : a pointer to a linked list of integers.
     */
    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }

    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}
