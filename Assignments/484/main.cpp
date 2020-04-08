///////////////////////////////////////////////////////////////////////////////
//
// Author:           Aquella Warner
// Email:            aquellawarner@hotmail.com
// Label:            P05
// Title:            Program 05 - 484
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//       This programs  remove all duplicates from a sequence of integers 
//       and prinst a list of unique integers along with the number of
//       of occurences of each.
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main()
{
	map<int, int> M;
	vector<int> pairs;
	int num;

	while (cin >> num)
	{
		if (M.find(num) == M.end())
		{	// not found
			pairs.push_back(num);
			M[num] = 1;
		}
		else
		{	// found
			M[num] = M[num] + 1;
		}
	}
	for (int i = 0; i < pairs.size(); i++)
	{
		cout << pairs[i] <<" "<< M[pairs[i]] << endl;
	}
	system("pause");
	return 0;
}
