/*
    Author: Andreea Musat 
    Date: 13 sept 2017

    Given a list of N numbers you will be allowed to choose any M of them
    You will have to determine how many of these chosen groups have a sum, which is divisible by D

    https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1557
*/

#include <bits/stdc++.h>
using namespace std;

#define MAXN 210
#define MAXM 210
#define MAXD 30

vector<int> arr;
int N, Q, D, M;
long long dp[210][210][30];

long long countDivisibleGroups(int i, int crt_nums, int crt_sum)
{
    if (crt_nums == M && crt_sum == 0)
        return 1;

    if (crt_nums >= M || i >= N)
        return 0;

    long long& ans = dp[i][crt_sum][crt_nums];
    if (ans != INT_MIN)
        return ans;

    ans = 0;
    ans += countDivisibleGroups(i + 1, crt_nums, crt_sum);
    ans += countDivisibleGroups(i + 1, crt_nums + 1, (crt_sum + arr[i]) % D);

    return ans;
}

int main()
{
    int set_no = 1;

    while (true)
    {
        cin >> N >> Q;
        if (N == 0 && Q == 0)
            break;

        if (arr.size() > 0)
            arr.clear();
        arr.resize(N);

        for (int i = 0; i < N; i++)
            cin >> arr[i];

        cout << "SET " << set_no++ << ":\n";
        for (int ii = 0; ii < Q; ii++)
        {
            cin >> D >> M;

            for (int i = 0; i < MAXN; i++)
                for (int j = 0; j < MAXM; j++)
                    for (int k = 0; k < MAXD; k++)
                        dp[i][j][k] = INT_MIN;

            long result = countDivisibleGroups(0, 0, 0);
            cout << "QUERY " << ii + 1 << ": " << result << "\n";
        }
    }

    return 0;
}
