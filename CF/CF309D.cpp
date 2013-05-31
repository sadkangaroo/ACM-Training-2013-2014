#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

typedef long long LL;

int N, M, S;
LL ans;

int main() {

    scanf("%d%d", &N, &M);
    ans = 0;
    S = N + 1;
    int TT = 3 * S;
    for (int i = M + 1; i <= (N + 1) / 2; ++i) {
        int k = M + 1;
        int cur = 0;
        for (int j = M + 1; j <= N - M; ++j) {     
            while ((S + k) * (S - j) + i * (j + k - TT + 2 * i) < 0 && k <= N - M) k++;    
            cur += k - M - 1;
        }
        if (i * 2 <= N) ans += 2 * cur;
        else ans += cur;
    }
    cout << ans * 3 << endl;

    return 0;

}
