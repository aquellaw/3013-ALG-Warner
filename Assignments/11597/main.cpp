///////////////////////////////////////////////////////////////////////////////
//
// Author:           Aquella Warner
// Email:            aquellwarner@hotmail.com
// Label:            P06 - Spanning Trees
// Title:            Program 06 - 11597
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//           This program counts the number of spanning subtrees in a complete
//			 graph.
//
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;
//#define endl "\n"

int main()
{
	int caseNum = 0, num_S_trees;
	int numV;

	cin >> numV;

	while (numV >= 2 && numV <= 400)
	{
		caseNum++;
		num_S_trees = numV*(numV - 1) / 2/(numV-1);
		cout << "Case " << caseNum << ": " << num_S_trees<<"\n";
		cin >> numV;
	}
	return 0;
}
