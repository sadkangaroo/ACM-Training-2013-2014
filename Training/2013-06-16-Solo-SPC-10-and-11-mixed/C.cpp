#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

typedef long long LL;

const int MaxN = 1000 + 5;
const int Mod = 1000003;

int N, M;
char s1[MaxN], s2[MaxN];
LL hash1[MaxN], hash2[MaxN];

int count(char* s) {
    int res = 0;
    for (int i = 0; i < N; ++i)
        if (s[i] == '1') res++;
    return res;
}

int main() {

    scanf("%d%d ", &N, &M); 
    bool flag = true;
    memset(hash1, 0, sizeof(hash1));
    memset(hash2, 0, sizeof(hash2));
    for (int i = 0; i < M; ++i) {
        scanf("%s", s1);
        scanf("%s", s2);
        if (count(s1) != count(s2)) flag = false;
        for (int k = 0; k < N; ++k) {
            if (s1[k] == '0')
                hash1[k] = hash1[k] * 999983 + 1;
            if (s2[k] == '0')
                hash2[k] = hash2[k] * 999983 + 1;
            if (s1[k] == '1')
                hash1[k] = hash1[k] * 999983;
            if (s2[k] == '1')
                hash2[k] = hash2[k] * 999983;
        }
    }
    sort(hash1, hash1 + N);
    sort(hash2, hash2 + N);
    for (int i = 0; i < N; ++i)
        if (hash1[i] != hash2[i]) flag = false;
    if (!flag) {
        printf("%d\n", 0);
    }
    else {
        int ans = 1, cur = 1, tmp = 1;
        for (int i = 1; i <= N; ++i)
            if (i == N || hash1[i] != hash1[i - 1]) {
                ans = (LL)ans * cur % Mod;
                cur = 1; tmp = 1;
            }
            else {
                tmp++;
                cur = (LL)cur * tmp % Mod;                
            }
        printf("%d\n", ans);
    }

    return 0;

}
