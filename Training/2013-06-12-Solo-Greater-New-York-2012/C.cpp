#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

int T, Num, N;
typedef long long LL;

int main() {

    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &Num, &N);
        LL ans = 0; 
        for (int k = (N - 1) / 2; k * 3 >= N; --k) {
            int rig = k, lef = N - k - k;
            if (lef <= rig) {
                ans += (rig - lef + 1);
                if (k * 3 != N) ans--;
            }
        }
        cout << Num << ' ' << ans << endl;
    }

    return 0;

}
