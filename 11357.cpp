/*
	Author: Andreea Musat
	Date: 21 sept 2017

	Check if Boolean formulas written according to the next grammar:
	<formula> ::= <clause> | <formula> "|" <clause>
	<clause> ::= "(" <conjunction-of-literals> ")"
	<conjunction-of-literals> ::= <literal> | <conjunction-of-literals> "&" <literal>
	<literal> ::= <variable> | "~" <variable>
	<variable> ::= "a" | "b" | "c" | ... | "z"
	are satisfiable
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2342
*/

#include <bits/stdc++.h>
using namespace std;

vector<string> split(string line, char delimiter)
{
	vector<string> result;
	size_t start_idx = 0, len;
	size_t end_idx = line.find(delimiter);

	while (end_idx != string::npos)
	{
		len = end_idx - start_idx;
		result.push_back(line.substr(start_idx, len));
		start_idx = end_idx + 1;
		end_idx = line.find(delimiter, start_idx);
	}

	return result;
}

bool check_satisfiability(string clause)
{
	int seen[26]; // set 1 if seen positive, -1 is seen with tilde (neg)
	memset(seen, 0, sizeof seen);

	vector<string> literals = split(clause + '&', '&');
	for (auto& literal : literals)
	{
		if (literal[0] == '~')
		{
			if (seen[literal[1] - 'a'] == 1)
				return false;
			else
				seen[literal[1] - 'a'] = -1;
		}
		else
		{
			if (seen[literal[0] - 'a'] == -1)
				return false;
			else
				seen[literal[0] - 'a'] = 1;
		}
	}

	return true;
}

int main()
{
	int T; 
	string line;
	cin >> T;
	while (T--)
	{
		cin >> line;

		/* Split the input string into clauses; If a single clause can be true, 
		then the expression is satisfiable. The clause can be true iff a literal
		is only present when its inverse is not present in the same clause */
		vector<string> clauses = split(line + '|', '|');
		bool is_satisfiable = false;
		for (auto& clause : clauses)
		{
			if (check_satisfiability(clause.substr(1, clause.size() - 2)))
			{
				is_satisfiable = true;
				break;
			}
		}

		if (is_satisfiable)
			cout << "YES\n";
		else 
			cout << "NO\n";
	}
	return 0;
}
