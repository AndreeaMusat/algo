#include <bits/stdc++.h>
using namespace std;

map<string, bool> seen;

bool solve(string str)
{
	if (seen.find(str) != seen.end())
		return seen[str];

	int i = 0, j;

	// for every element of the string
	while (i < (int)str.size())
	{
		j = i;
		// let j be the first index where str[j] != str[i]
		while (j < (int)str.size() and str[j] == str[i])
			j += 1;

		// if str[i..j] is a block of at least 2 chars, it can be popped
		// so we can recursively call the procedure for the remaining previous
		// and next string
		if (j - i >= 2)
		{
			string prev = str.substr(0, i);
			string next = str.substr(j, string::npos);
			bool res = solve(prev + next);

			// is a solution is found for the remainder, then a solution for the 
			// entire initial string was found
			if (res) 
			{
				seen[str] = res;
				return res;	
			}
			
		}

		// we only get here is solution was not found by popping the current block
		// or if the block didn't have at least 2 chars;
		// we go to the next possible block
		i = j;
	}

	// if we get here, then no solution was found
	seen[str] = false;
	return false;
}

int main()
{
	int T;
	string str;

	cin >> T;
	while (T--)
	{
		seen.clear();
		seen[""] = true;

		cin >> str;
		cout << solve(str) << "\n";
	}
	return 0;
}