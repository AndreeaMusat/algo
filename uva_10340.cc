#include <bits/stdc++.h>
using namespace std;

bool bkt(const string& str1, const string& str2, size_t i, size_t j) {
	if (j == str2.length() and i < str1.length()) return false;
	if (i == str1.length()) return true;
	if (str1[i] == str2[j] and bkt(str1, str2, i + 1, j + 1)) return true;
	return bkt(str1, str2, i, j + 1);
}

bool bkt(const string& str1, const string& str2) {
	return bkt(str1, str2, 0, 0);
}

int main() {
	string str1, str2;

	while (cin >> str1 >> str2) {
		cout << (bkt(str1, str2) ? "Yes\n" : "No\n");
	}
}