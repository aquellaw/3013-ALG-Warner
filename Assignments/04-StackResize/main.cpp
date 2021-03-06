///////////////////////////////////////////////////////////////////////////////
//
// Author:           Aquella Warner
// Email:            aquellawarner@hotmail.com
// Label:            P01
// Title:            Program 01 - Array Based Stack
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//       Overview of a class implementing an array based stack
//
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>

using namespace std;

/**
 * ArrayStack
 *
 * Description:
 *      Array based stack
 *
 * Public Methods:
 *      - See class below
 *
 * Usage:
 *      - See main program
 *
 */
class ArrayStack {
private:
	int *A;                         // pointer to array of int's
	int size;                       // current max stack size
	int top;                        // top of stack 
	int maxSize;	                  // max size stack grows to
	int resize;		                  // No.times stack was resized.
public:
	/**
	 * ArrayStack
	 *
	 * Description:
	 *      Constructor no params
	 *
	 * Params:
	 *     - None
	 *
	 * Returns:
	 *     - NULL
	 */
	ArrayStack() {
		size = 10;
		A = new int[size];
		top = -1;
		maxSize = 0;
	}

	/**
	 * ArrayStack
	 *
	 * Description:
	 *      Constructor size param
	 *
	 * Params:
	 *     - int size
	 *
	 * Returns:
	 *     - NULL
	 */
	ArrayStack(int s) {
		size = s;
		A = new int[s];
		top = -1;
		maxSize = 0;
	}

	/**
	 * Public bool: Empty
	 *
	 * Description:
	 *      Checks if stack is empty
	 *
	 * Params:
	 *      NULL
	 *
	 * Returns:
	 *      [bool] true = empty
	 */
	bool Empty() {
		return (top <= -1);
	}

	/**
	 * Public bool: Full
	 *
	 * Description:
	 *      Checks if stack is full
	 *
	 * Params:
	 *      NULL
	 *
	 * Returns:
	 *      [bool] true = full
	 */
	bool Full() {
		return (top >= size - 1);
	}

	/**
	 * Public int: Peek
	 *
	 * Description:
	 *      Returns top value without altering the stack
	 *
	 * Params:
	 *      NULL
	 *
	 * Returns:
	 *      [int]: top value if any
	 */
	int Peek() {
		if (!Empty()) {
			return A[top];
		}

		return -99;							            // some sentinel value
											                  // not a good solution
	}

	/**
	 * Public int: Pop
	 *
	 * Description:
	 *      Returns top value and removes it from stack
	 *
	 * Params:
	 *      NULL
	 *
	 * Returns:
	 *      [int]: top value if any
	 */
	int Pop() {
		if (!Empty()) {

			CheckResize();					      // then resize stack (shrink it)

			return A[top--];
		}
		return -99;							        // some sentinel value								
											              // not a good solution
	}

	/**
	 * Public void: Print
	 *
	 * Description:
	 *      Prints stack to standard out
	 *
	 * Params:
	 *      NULL
	 *
	 * Returns:
	 *      NULL
	 */
	void Print() {
		for (int i = 0; i <= top; i++) {
			cout << A[i] << " ";
		}
		cout << endl;
	}

	/**
	 * Public bool: Push
	 *
	 * Description:
	 *      Adds an item to top of stack
	 *
	 * Params:
	 *      [int]: item to be added
	 *
	 * Returns:
	 *      [bool]: success = true
	 */
	bool Push(int x) {
		if (Full()) 
		{
			CheckResize();					          // increase stack size if stack is full
		}

		if (!Full())
		{
			A[++top] = x;
			return true;
		}

		return false;
	}

	/**
	 * Public void: ContainerResize
	 *
	 * Description:
	 *      Resizes the container for the stack by 1.75
	 *      its capacity if ratio is 1 (which means stack is full),
	 *		  or decreases its capacity by .5 if ratio is less
	 *		  than .50 (which means stack is less than half full).
	 *
	 * Params:
	 *     [bool]:	true/false
	 *
	 * Returns:
	 *      NULL
	 */
	void ContainerResize(bool x) {
		int newSize = 0;

		if (x)
		{
			int newSize = size * 1.75;			     //increase size of original by 1.75

			int *B = new int[newSize];			     // allocate new memory

			for (int i = 0; i < size; i++) {     // copy values to new array
				B[i] = A[i];
			}

			delete[] A;							            // delete old array

			size = newSize;						          //save new size

			A = B;								              // reset array pointer 

			if (maxSize < size)					
			{
				maxSize = size;					          // set maxSize = size if mazsize
			}									                  // is less than size(original size)

			resize++;						              	// keeps track of the number of times
											                  	// stack was resized.
		}
		else
		{
			int newSize = size * .5;			       //decrease size of original by .5

			int *B = new int[newSize];			     // allocate new memory

			size = newSize;						           //save new size

			for (int i = 0; i < size; i++) {     // copy values to new array
				B[i] = A[i];
			}

			delete[] A;							            // delete old array

			A = B;								              // reset array pointer 

			if (maxSize < size)
			{
				maxSize = size;				          	// set maxSize = size if mazsize
			}

			resize++;							             // keeps track of the number of times
												                 // stack was resized.
		}

	}

	/**
	 * Public void: CheckResize
	 *
	 * Description:
	 *      Calculates the ratio between the number of items currently
	 *		  in the stack and the stack size. If ratio is 1, increase
	 *		  stack, otherwise is ratio is less that .50, decrease it.
	 *
	 * Params:
	 *      NULL
	 *
	 * Returns:
	 *      NULL
	 */
	void CheckResize() {
		double ratio;

		int numItems = top + 1;						        // accurate number of items on stack

		ratio = (double)numItems / (double)size;	// casting integers as doubles to get an accurate number 

		if (ratio == 1)
		{
			ContainerResize(true);
		}
		else if (ratio < .50 && resize >= 1 && size > 10)
		{
			ContainerResize(false);
		}
	}

	/**
	* Public int: NumResize
	*
	* Description:
	*      returns resize
	*
	* Params:
	*     NULL
	*
	* Returns:
	*      [int]: end stack size
	*/
	int NumResize()
	{
		return resize;
	}

	/**
	 * Public int: MaxStackSize
	 *
	 * Description:
	 *      returns the maximum size of the 
	 *		stack
	 *
	 * Params:
	 *      NULL
	 *
	 * Returns:
	 *      [int]: max size the stack grew to.
	 */
	int MaxStackSize()
	{
		return maxSize;
	}

	/**
	* Public int: EndStackSize
	*
	* Description:
	*      returns the stack size at the end of
	*	     the program.
	*
	* Params:
	*      NULL
	*
	* Returns:
	*      [int]: updated stack size.
	*/
	int EndStackSize()
	{
		return size;
	}
};

// MAIN DRIVER
// Simple Array Based Stack Usage:
int main() {
	ifstream infile;							// fstream variable to read from a file
	ofstream outfile;							// fstream variable to write to a file

	infile.open("nums_test.dat");					// opens .dat file
	outfile.open("output");						// opens txt file

	ArrayStack stack;							// ArrayStack variable

	outfile << "Assignment 4 - Resizing the Stack\n";
	outfile << "CMPS 3013\n";
	outfile << "Aquella Warner\n\n";

	int num;						
	infile >> num;								// int variable which holds value from file

	while (!infile.eof())						// read while it is not the end of the file
	{
		if (num % 2 == 0)						//if numbers are even, push onto stack
		{
			stack.Push(num);
		}
		else
		{
			stack.Pop();						// if numbers are odd, pop the last even number off the stack
		}
		infile >> num;							// read in another number.
	}

	outfile << "Max Stack Size: " << stack.MaxStackSize() << "\n"; 
	outfile << "End Stack Size: " << stack.EndStackSize() << "\n";
	outfile << "Stack Resized: " << stack.NumResize() << " times.\n";
	stack.Print();

	infile.close();
	outfile.close();
	system("pause");
}
