#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

int N, T, M, Tot;
int cheers[95];

struct Node {
    int a, b; 
    Node(): a(-1) {}
    Node(int _a, int _b): a(_a), b(_b) {}
    bool operator > (const Node &t) const {
        if (a == -1) return false;
        return (t.a == -1) || (a - b > t.a - t.b) || (a - b == t.a - t.b && a > t.a);
    }
    void update(const Node &t) {
        if (t > *this) 
            *this = t;
    }
}dp[90 + 5][1800 + 5][9];

Node& get(int i, int j, int k) {
    return dp[i][j][k + 4]; 
}

int main() {

    scanf("%d%d%d", &N, &T, &M);
    Tot = N * T;
    memset(cheers, 0, sizeof(cheers));
    for (int i = 0; i < M; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        for (int k = a + 1; k <= b; ++k) cheers[k]++; 
    }
    get(0, 0, 0) = Node(0, 0);
    for (int i = 0; i < 90; ++i)
        for (int j = 0; j <= Tot; ++j)
            for (int k = -4; k <= 4; ++k) 
                if (get(i, j, k).a != -1) 
                    for (int s = 0; s <= N && s <= Tot - j; ++s) {
                        int ii = i + 1, jj = j + s, kk;
                        if (s == cheers[i + 1]) kk = 0;
                        if (s > cheers[i + 1]) {
                            if (i + 1 == 46) kk = 1;
                            else kk = max(k, 0) + 1;
                        }
                        if (s < cheers[i + 1]) {
                            if (i + 1 == 46) kk = -1;
                            else kk = min(k, 0) - 1;
                        }
                        int ta = get(i, j, k).a, tb = get(i, j, k).b;
                        if (kk == 5) {
                            ta++; kk = 0;
                        }
                        if (kk == -5) {
                            tb++; kk = 0;
                        }
                        get(ii, jj, kk).update(Node(ta, tb));
                    }
    Node ans(-10000, 10000);
    for (int j = 0; j <= Tot; ++j)
        for (int k = -4; k <= 4; ++k)
                ans.update(get(90, j, k));
    printf("%d %d\n", ans.a, ans.b);

    return 0;

}
