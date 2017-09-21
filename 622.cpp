/*
	Author: Andreea Musat
	Date: 21 sept 2017

	Algebraic expressions grammar parser

	< expression > := < component > | < component > + < expression >
	< component > := < factor > | < factor > * < component >
	< factor > := < positiveinteger > | (< expression >)

	https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=563
*/

#include <bits/stdc++.h>
using namespace std;
const int ERROR = INT_MIN;

int expression(string);
int factor(string);
int component(string);

int expression(string str)
{
	if (str.empty())
		return ERROR;
	
	int ans, ans_comp, ans_expr;

	ans = component(str);
	if (ans != ERROR)
		return ans;

	size_t plus_pos = str.find('+');
	while (plus_pos != string::npos)
	{
		string comp = str.substr(0, plus_pos);
		string expr = str.substr(plus_pos + 1, str.size() - 1 - plus_pos);

		ans_comp = component(comp);
		ans_expr = expression(expr);	

		if (ans_comp != ERROR && ans_expr != ERROR)
			return ans_comp + ans_expr;

		plus_pos = str.find('+', plus_pos + 1);
	}
	
	return ERROR;
}

int component(string str)
{
	if (str.empty())
		return ERROR;

	int ans, ans_fact, ans_comp;

	ans = factor(str);
	if (ans != ERROR)
		return ans;

	size_t star_pos = str.find('*');
	while (star_pos != string::npos)
	{
		string fact = str.substr(0, star_pos);
		string comp = str.substr(star_pos + 1, str.size() - star_pos - 1);

		ans_fact = factor(fact);
		ans_comp = component(comp);	

		if (ans_fact != ERROR && ans_comp != ERROR)
			return ans_fact * ans_comp;

		star_pos = str.find('*', star_pos + 1);
	}
	
	return ERROR;
}

int positive_integer(string str)
{
	if (str.empty())
		return ERROR;

	for (auto chr : str)
		if (!isdigit(int(chr)))
			return ERROR;

	return stoi(str);
}

int factor(string str)
{
	if (str.empty())
		return ERROR;

	int ans, ans_expr = ERROR;

	ans = positive_integer(str);
	if (ans != ERROR)
		return ans;

	if (str[0] != '(' || str.back() != ')')
		return ERROR;

	if (str.size() >= 2)
		ans_expr = expression(str.substr(1, str.size() - 2));

	return ans_expr;
}

void eval(string line)
{
	int res = expression(line);
	if (res != ERROR)
		cout << res << "\n";
	else 
		cout << "ERROR\n";
}

int main()
{
	int T;
	string line;

	cin >> T;
	while (T--)
	{
		cin >> line;
		eval(line);
	}
	return 0;
}
