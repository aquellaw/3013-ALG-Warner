///////////////////////////////////////////////////////////////////////////////
//
// Author:           Aquella Warer
// Email:            aquellawarner@hotmail.com
// Label:            P08
// Title:            Program 08 - 10901
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//       This programs uses a queue to keep track of the times at which each car 
//       is picked up and dropped off by a ferry.
//
/////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{

	int numCases, numCars, time_in_mins, numLines, 
			arrivalT;

	string whichSide;

	queue<int> whichLine[2];
	vector<int> carOrder;

	cin >> numCases;

	while (numCases--)
	{
		cin >> numCars >> time_in_mins >> numLines;

		int fSide = 0, time = 0;

		for(int i=0; i < numLines; i++)
		{

			cin >> arrivalT;
			cin >> whichSide;

			if (whichSide == "right")
			{
				whichLine[1].push(i);
			}
			else
			{
				whichLine[0].push(i);
			}

			carOrder.push_back(arrivalT);
		}

		vector<int> tTime(carOrder.size());

		//While there are cars on either side
		while (!whichLine[0].empty() || !whichLine[1].empty())
		{
			int wait_time = 0;

			if (!whichLine[1].empty() && !whichLine[0].empty())
			{
				if (carOrder[whichLine[0].front()] <= carOrder[whichLine[1].front()])
				{
					wait_time = carOrder[whichLine[0].front()];
				}
				else
				{
					wait_time = carOrder[whichLine[1].front()];
				}
			}
			else
			{
				if (whichLine[0].empty())
				{
					wait_time = carOrder[whichLine[1].front()];
				}
				else if (whichLine[1].empty())
				{
					wait_time = carOrder[whichLine[0].front()];
				}
			}

			//Stores true time
			if (wait_time >= time)
			{
				time = wait_time;
			}

			int carsHeld = 0;

			while ((numCars > carsHeld) && (!whichLine[fSide].empty()) && (carOrder[whichLine[fSide].front()] <= time))
			{
				tTime[whichLine[fSide].front()] = time_in_mins + time;
				whichLine[fSide].pop();
				carsHeld++;
			}

			time += time_in_mins;

			if (fSide == 0)
			{
				fSide = 1;
			}
			else
			{
				fSide = 0;
			}
		}

		//Prints answers
		for (int i = 0; i < numLines; i++)
		{
			cout << tTime[i] << '\n';
		}

		carOrder.clear();
	

		if (numCases > 0)
			cout << '\n';

		//numCases--;
	}
	return 0;
}
