#include <iostream>

#define endl "\n"

using namespace std;

int main()
{
	int c, x, y, i = 0;
	cin >> c;
	while (i < c)
	{
		cin >> x >> y;
		if (x < y)
		{
			cout << '<' << endl;
		}
		else if (x > y)
		{
			cout << '>' << endl;
		}
		else
		{
			cout << '=' << endl;
		}
		i++;
	}
	return 0;
}
