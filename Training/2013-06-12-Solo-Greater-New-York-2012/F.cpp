#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

typedef long long LL;

const int MaxN = 20 + 5;

int T, Num, N;
LL dp[MaxN][MaxN][2];

int main() {

    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &Num, &N);
        if (N == 1) {
            printf("%d %d\n", Num, 1);
            continue;
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= N; ++i)
            dp[1][N - i][0] = dp[1][N - i][1] = 1;
        for (int i = 1; i < N; ++i) 
            for (int j = 0; j <= N; ++j) {
                if (dp[i][j][0]) {
                    for (int k = 1; k <= N - i - j; ++k) 
                        dp[i + 1][N - i - k][1] += dp[i][j][0];
                }
                if (dp[i][j][1]) {
                    for (int k = 1; k <= j; ++k)
                        dp[i + 1][j - k][0] += dp[i][j][1];
                }
            }


        cout << Num << ' ' << dp[N][0][0] + dp[N][0][1] << endl;
    }

    return 0;

}
