#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<set>

using namespace std;

const int MaxN = 200000 + 5;

int N;

bool vis[MaxN];
int a[MaxN], ans[MaxN];
int deg[MaxN];

set<int> S;

int main() {

    scanf("%d", &N); 
    S.clear();
    memset(vis, false, sizeof(vis));
    memset(deg, 0, sizeof(deg));
    for (int i = 1; i <= N; ++i) {
        scanf("%d", a + i);
        vis[a[i]] = true;
        deg[a[i]]++;
    }
    for (int i = 1; i <= N + 1; ++i)
        if (!vis[i]) 
            S.insert(i);
    bool flag = true;
    if (a[N] != N + 1) flag = false;
    for (int i = 1; i <= N; ++i) {
        if (!flag) break;
        if (S.empty()) {
            flag = false;
            break;
        }
        ans[i] = *S.begin();
        S.erase(S.begin());
        deg[a[i]]--;
        if (deg[a[i]] == 0)
            S.insert(a[i]);
    }
    if (!flag) printf("Error\n");
    else {
        for (int i = 1; i <= N; ++i) 
            printf("%d\n", ans[i]);
    }

    return 0;

}
