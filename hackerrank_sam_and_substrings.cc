#include <bits/stdc++.h>
using namespace std;

const int kModulo = (int) 1e9 + 7;

int main() {
    string str;
    cin >> str;

    int n = (int)str.length(), digit;
    long long ans = 0, tmp = 1;

    for (int i = n - 1; i >= 0; i--) {
    	digit = str[i] - '0';
    	ans = (ans + (((i + 1) % kModulo) * (digit * tmp) % kModulo) % kModulo) % kModulo;
    	tmp = (((tmp * 10) % kModulo) + 1) % kModulo;
    }

    cout << ans << "\n";
}