#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxLen = 10000000 + 5;

int T, Num, B;
char s[MaxLen];

int main() {

    scanf("%d", &T);
    while (T--) {
        scanf("%d%d %s ", &Num, &B, s);
        int l = strlen(s);
        int now = 0;
        for (int i = l - 1; i >= 0; --i) {
            now = (now * B + s[i] - '0') % (B - 1);
        }
        printf("%d %d\n", Num, now);
    }

    return 0;

}
