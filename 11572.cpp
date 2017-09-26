/*
	Author: Andreea Musat
	Date: 25 sept 2017

	Longest subarray of unique elements
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2619
*/

#include <bits/stdc++.h>
using namespace std;

size_t findLargestUniqueSubarray(const vector<int>& arr)
{
	int start_index = 0;
	int end_index = 0;
	size_t largest_unique_len = (arr.size() > 0) ? 1 : 0;

	/* map integers to their frequency in current subarray */
	unordered_map<int, int> mp;

	while (end_index < arr.size())
	{
		/* if current element is not in crt subarray yet, extend window */
		if (!mp[arr[end_index]])
		{
			mp[arr[end_index]] = 1;
			end_index += 1;
			largest_unique_len = max(largest_unique_len, mp.size());
		}

		/* remove elements from the beginning of the window so that we
		   can extend it with current element */
		else 
		{
			end_index += 1;
			while (start_index < end_index)
			{
				if (arr[start_index] == arr[end_index - 1])
				{
					mp[arr[start_index]] = 1;
					start_index += 1;
					break;
				}

				mp.erase(mp.find(arr[start_index]));
				start_index += 1;
			}
			largest_unique_len = max(largest_unique_len, mp.size());
		}
	}

	return largest_unique_len;
}

int main()
{
	int T, n;
	vector<int> arr;

	cin >> T;
	while (T--)
	{
		cin >> n;

		arr.clear();
		arr.resize(n);

		for (int i = 0; i < n; i++)
			cin >> arr[i];
	
		size_t ans = findLargestUniqueSubarray(arr);
		cout << ans << "\n";
	}

	return 0;
}
