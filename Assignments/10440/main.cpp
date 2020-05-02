///////////////////////////////////////////////////////////////////////////////
//                   
// Author:           Aquella Warner
// Email:            aquellawarner@hotmail.com
// Label:            P08 - 10440
// Title:            10440
// Course:           CMPS-3013-201
// Semester:         Spring 2020
//
// Description:
//       This program uses uses a vector to keep track of in a set of car times to 
//		 determine the minimum number of trips a ferry can make to get all cars 
//		 to the other side.
/////////////////////////////////////////////////////////////////////////////////
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() 
{
	int numCases, numCars, numLines, mins, posOfcar, numTrips, arrTime;
	int ans;
	vector <int> arrivals;

	cin >> numCases;

	int i = 0;

	while(i < numCases)
	{
		cin>> numCars>> mins>> numLines;

		vector <int> arrivals(numLines);

		for (int i = 0; i < numLines; i++)
		{
			cin >> arrTime;
			arrivals[i] = arrTime;
		}

		ans = 0;
		posOfcar = 0;

		if (numLines%numCars != 0)
		{
			posOfcar = numLines % numCars;
			ans = arrivals[posOfcar - 1] + (mins * 2);
		}
		else
		{
			ans = arrivals[numCars - 1] + mins;
			posOfcar = numCars;
		}

		int doubleMins = (mins * 2);

		 while( posOfcar < numLines )
		 {
			 if (ans <= arrivals[posOfcar + numCars - 1])
			 {
				 ans = arrivals[posOfcar + numCars - 1] + doubleMins;
			 }
			 else
			 {
				 ans = ans + doubleMins;
			 }
			posOfcar += numCars;
		}
		ans -= mins;

		i++;
		
		numTrips = ((numLines + numCars - 1) / numCars);

		cout << ans<< " "<< numTrips;
		cout << "\n";
	}

	return 0;
}
