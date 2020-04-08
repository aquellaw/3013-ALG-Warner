///////////////////////////////////////////////////////////////////////////////
//
// Author:           Aquella Warner
// Email:            aquellwarner@hotmail.com
// Label:            P04
// Title:            Program 04 - 459
// Course:           3013
// Semester:         Spring 2020
//
// Description:
//          This program determines the number of maximal connected subgraphs in a
//          a graph.
//
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>

#define endl "\n"

using namespace std;

typedef vector<int> vi;     // vector of integers
typedef pair<int, int> ii; // pair of integers
typedef vector<ii> vii;    // vector of pairs

const int VISITED = 1;
const int UNVISITED = -1;

vi been_visited;            // container to keep track of who get visited
vector <vii> AdjList;        // AdjList stores our edge lists

/**
 * Depth First Search
 *
 * Params:
 *  int u - starting node id
 *
 */
void dfs(int u) {
	// In DFS we use a stack structure to keep track of who to visit next.
	// Recursive acts just like a stack so we dont need to declare any 
	// structure to keep track for us, we let the recursive calls do it for us

	been_visited[u] = VISITED;  // mark u as visited
	//cout << u << " ";         // write u to stdout

	// Loop overadjacency list looking for connections
	for (int j = 0; j < (int)AdjList[u].size(); j++)
	{

		// v is a pair representing a neighbor and the 
		// weight of the edge from u->v
		ii v = AdjList[u][j];

		// check to see if our neighbor was visited
		if (been_visited[v.first] == UNVISITED) {
			dfs(v.first);
		}
	}
}
int main()
{
	int numCases;
	char biggestNode, u, v;

	//Holds the number of cases
	cin >> numCases;
	for (int i = 0; i < numCases; i++)
	{
		//Holds the first character encountered - This is the largest node
		cin >> biggestNode;

		int n = (int(biggestNode) - int('A')) + 1;

		//Clears cin buffer
		cin.ignore();

		AdjList.resize(n);

		been_visited.resize(n, UNVISITED);

		string line;

		while (getline(cin, line) && line !="")
		{
			//Convert to integers
			int first = line[0] - int('A');
			int second = line[1] - int('A');

			//Push onto adjacenct list
			AdjList[first].push_back(make_pair(second, 0));
			AdjList[second].push_back(make_pair(first, 0));
		}
		//Holds the number of maximal connected subgraphs
		int count = 0;

		//Find connected components
		for (int i = 0; i < n; i++)
		{
			if (been_visited[i] == UNVISITED)
			{
				count++;
				dfs(i);
			}
		}
		
		cout << count << endl;

		//Clears both data structures.
		been_visited.clear();
		AdjList.clear();
		if (numCases)
		{
			cout << endl;
		}
	}
	return 0;
}
