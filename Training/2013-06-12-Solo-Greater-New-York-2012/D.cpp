#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 100 + 5;
const double eps = 0;

int T, Num, N;
double L, R;

double Prob[MaxN][MaxN * 2][MaxN];

int main() {

    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%lf%lf", &Num, &N, &L, &R);
        for (int i = 0; i <= N; ++i)
            for (int j = 0; j <= 2 * N; ++j)
                for (int k = 0; k <= N; ++k)
                    Prob[i][j][k] = 0;
        Prob[0][N][0] = 1;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j <= 2 * N; ++j)
                for (int k = 0; k <= N; ++k)
                    if (fabs(Prob[i][j][k]) > eps) {
                        Prob[i + 1][j][k] += (1 - L - R) * Prob[i][j][k];
                        Prob[i + 1][j - 1][k] += L * Prob[i][j][k];
                        Prob[i + 1][j + 1][max(k, j + 1 - N)] += R * Prob[i][j][k];
                    }
        double ans = 0;
        for (int j = 0; j <= 2 * N; ++j)
            for (int k = 0; k <= N; ++k) {
                if (fabs(Prob[N][j][k]) > eps)
                    ans += Prob[N][j][k] * k;
            }
        printf("%d %.4f\n", Num, ans);
    }

    return 0;

}
