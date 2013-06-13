#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxLen = 10000000 + 5;

int T, Num, N, K, len;
char s[MaxLen];

int main() {

    scanf("%d", &T); 
    while (T--) {
        scanf("%d", &Num); 
        getchar();
        char c; int len = 0;
        while ((c = getchar()) && c != '\n') {
            s[len++] = c;
        }
        scanf(" %d", &N);
        printf("%d ", Num);
        int now = 0, x;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &x); 
            now = (now + x + len) % len;
            putchar(s[now]);
        }
        printf("\n");
    }

    return 0;

}
