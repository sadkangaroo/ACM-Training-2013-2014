#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<string>

using namespace std;

const int MaxN = 1000000 + 5;

int N, R, C;
string s[MaxN];
int f[MaxN][20];
int len[MaxN];
int start, mx;

int main() {

    cin >> N >> R >> C;
    len[0] = 0;
    for (int i = 1; i <=  N; ++i) {
        cin >> s[i];
        len[i] = len[i - 1] + s[i].length() + 1;
    }
    for (int k = 0; k < 20; ++k) f[N + 1][k] = N + 1;
    for (int i = 1; i <= N; ++i) 
        f[i][0] = upper_bound(len + 1, len + N + 1, len[i - 1] + C + 1) - len;
    for (int k = 1; k < 20; ++k) 
        for (int i = 1; i <= N; ++i) 
            f[i][k] = f[f[i][k - 1]][k - 1];
    start = mx = 0;
    for (int i = 1; i <= N; ++i) {
        int now = i, curlen = 0;
        for (int k = 0; k < 20; ++k)
            if (R & (1 << k)) {
                curlen += f[now][k] - now;
                now = f[now][k];
            }
        if (curlen > mx) {
            mx = curlen;
            start = i;
        }
    }
    int nlen = 0; 
    for (int i = start; i < start + mx; ++i) {
        if ((nlen != 0) + nlen + s[i].length() <= C) {
            if (nlen != 0) cout << ' ' << s[i];
            else cout << s[i];
            nlen += (nlen != 0) + s[i].length();
        }
        else {
            cout << '\n' << s[i];
            nlen = s[i].length();
        }
    }
    cout << '\n';

    return 0;

}
