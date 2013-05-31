#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

int N, M;
int a[32], b[32];

int main() {

    scanf("%d%d", &N, &M);
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    int x;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &x);
        for (int k = 0; k < 32; ++k)
            if (x & (1 << k)) a[k]++;
    }
    for (int i = 0; i < M; ++i) {
        scanf("%d", &x);
        b[x]++;
    }
    int ans = 0;
    bool fl = true;
    for (int i = 0; i < 32; ++i) {
        for (int v = 0; v < b[i]; ++v) {
            int k;
            for (k = i; k < 32; ++k) {
                if (a[k]) break;
                else a[k]++;
            }
            if (k == 32) {
                fl = false; 
                break;
            }
            a[k]--;
            ans++;
        }
        if (!fl) break;
    }
    cout << ans << endl;

    return 0;

}
