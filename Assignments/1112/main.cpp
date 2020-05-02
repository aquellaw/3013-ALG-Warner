///////////////////////////////////////////////////////////////////////////////
//
// Author:           Aquella Warner
// Email:            aquellwarner@hotmail.com
// Label:            P07 - Mice and Maze
// Title:            Program 07 - 1112
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//           This program is used to determine the total number of mice that
//			 that can escape a maze and the length of time it take for them
//			 to do so.
//
/////////////////////////////////////////////////////////////////////////////////
 

#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

#define ii pair<int, int>
vector<ii> matrix[101];

int numC, exitCell, m_connects, timer, distanceG[110];

void dijkstras(int x)
{
	priority_queue<ii> pQueue;

	for (int i = 0; i <= numC; i++)
	{
		distanceG[i] = INT_MAX;
	}

	distanceG[x] = 0;

	pQueue.push(ii(distanceG[x], x));
	
	while (!pQueue.empty())
	{
		ii P1 = pQueue.top();
		int c = P1.second;

		pQueue.pop();

		for (int i = 0; i < matrix[c].size(); ++i)
		{
			ii r = matrix[x][i];

			if (distanceG[x] + r.second < distanceG[r.first])
			{
				distanceG[r.first] = distanceG[c] + r.second;
				pQueue.push(make_pair(distanceG[r.first], r.first));
			}
		}
	}
}

int main()
{
	int total, line1, line2, line3;

	cin >> total;
	while (total--)
	{
		cin >> numC >> exitCell >> timer >> m_connects;

		while (m_connects)
		{
			cin >> line1 >> line2 >> line3;
			matrix[line2].push_back(ii(line1, line3));

			m_connects--;
		}

			dijkstras(exitCell);

			int counter = 0;

			for (int i = 1; i <= numC; i++)
			{
				if (distanceG[i] <= timer)
					counter++;
			}

			cout << counter << '\n';

			if (total > 0)
			{
				cout << '\n';
			}

	}
	return 0;
}
