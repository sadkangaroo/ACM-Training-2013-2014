#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

int T, num, N;

int main() {

    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &num, &N); 
        int mx = N;
        while (N != 1) {
            if (N & 1) N = N * 3 + 1;
            else N /= 2;
            mx = max(mx, N);
        }
        printf("%d %d\n", num, mx);
    }

    return 0;

}
