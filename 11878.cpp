/*
	Author: Andreea Musat
	Date: 21 sept 2017

	Simple string parser
	https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3000	
*/
#include <bits/stdc++.h>
using namespace std;

bool check_correct(string line)
{
	bool is_addition = true;
	size_t op_pos = line.find('+');
	size_t eq_pos = line.find('=');
	if (op_pos == string::npos)
	{
		op_pos = line.find('-');
		is_addition = false;
	}

	int op1 = stoi(line.substr(0, op_pos));
	int op2 = stoi(line.substr(op_pos + 1, eq_pos - op_pos - 1));
	string res_str = line.substr(eq_pos + 1, line.size() - 1 - eq_pos);
	if (res_str.find('?') != string::npos)
		return false;
	
	int res = stoi(res_str);
	if (is_addition) return (op1 + op2 == res);
	return (op1 - op2 == res);
}

int main()
{
	int cnt_correct = 0;
	string line;

	while (cin >> line)
	{
		if (check_correct(line))
			cnt_correct	+= 1;
	}

	cout << cnt_correct << "\n";
	return 0;
}
