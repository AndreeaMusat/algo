/* 
    Author: Andreea Musat
    Date: 11 Sept 2017
    Find bitmask that uniquely identifies every binary representation
    from the input. Compile with -std=c++11

    https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2146
*/

#include <bits/stdc++.h>
using namespace std;

int solve(const vector<int>& nums, int p)
{
	unordered_set<int> unique_nums;

	int min_num_bits = p;
	int crt_set_bits = INT_MAX;
	int crt_num = 0;

	for (int bitmask = 0; bitmask < (1 << p) - 1; bitmask++)
	{
		/* store unique numbers in unordered set */
		if (unique_nums.size() > 0)
			unique_nums.clear();

		/* for every number read, if it is already in the set, 
		   then the current bitmask cannot uniquely represent all the 
		   numbers, so we should try the next bitmask; 
		   otherwise, we can insert current number (bitmask & nums[i])
		   in the set 
		*/
		bool is_sol = true;
		for (size_t i = 0; is_sol && (i < nums.size()); i++)
		{
			crt_num = nums[i] & bitmask;
			if (unique_nums.find(crt_num) != unique_nums.end())
				is_sol = false;
			else
				unique_nums.insert(crt_num);
		}

		/*
			If number of set bits in current bitmask is less than current
			minimum number of bits set, then update minimum number of bits set
		*/
		crt_set_bits =  __builtin_popcount(unsigned(bitmask));
		if (is_sol && crt_set_bits < min_num_bits)
			min_num_bits = crt_set_bits;

	}

	return min_num_bits;
}

int main()
{
	int T;	// no of tests
	int n;	// no of binary represenations
	int p;	// no of bits
	int bit = -1;
	int num_bits_repr = 0;
	cin >> T;

	while (T--)
	{
		cin >> p >> n;
		
		vector<int> nums(n, 0);

		// read set bits in every representation and construct decimal number
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < p; j++)
			{
				cin >> bit;
				if (bit)
					nums[i] += 1 << (p - j - 1);
			}
		}

		// get min no of set bits necessary to uniquely represent all the read numbers
		num_bits_repr = solve(nums, p);
		cout << num_bits_repr << "\n";
	}

	return 0;
}
