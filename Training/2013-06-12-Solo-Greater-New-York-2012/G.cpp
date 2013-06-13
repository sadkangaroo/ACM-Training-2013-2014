#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxQueueSize = 1000000 + 5;
const int Limit = 100;

int T, Num, N;
bool vis[100][100][100];
int conv[6][2][3];

struct Node {
    int a[3], pre;
    char c;
    void load() {
        scanf("%d%d%d", a, a + 1, a + 2);
    }
    bool operator == (const Node &t) const {
        return a[0] == t.a[0] && a[1] == t.a[1] && a[2] == t.a[2];
    }
    void cover() {
        vis[a[0]][a[1]][a[2]] = true;
    }
    bool legal(int id, Node &nxt) {
        Node now = *this;
        for (int i = 0; i < 3; ++i) 
            now.a[i] -= conv[id][0][i];
        for (int i = 0; i < 3; ++i)
            if (now.a[i] < 0 || now.a[i] >= Limit) return false;
        for (int i = 0; i < 3; ++i)
            now.a[i] += conv[id][1][i];
        for (int i = 0; i < 3; ++i)
            if (now.a[i] < 0 || now.a[i] >= Limit) return false;
        if (vis[now.a[0]][now.a[1]][now.a[2]]) return false;
        vis[now.a[0]][now.a[1]][now.a[2]] = true;
        nxt = now;
        return true;
    }
}Start, End, Q[MaxQueueSize];

char ans[MaxQueueSize];

int bfs() {
    memset(vis, false, sizeof(vis));
    int f = 0, r = 0;
    Q[r++] = Start;
    Q[0].pre = -1;
    if (Start == End)
        return 0;
    Start.cover();
    while (f != r) {
        Node now = Q[f++], nxt; 
        for (int i = 0; i < 6; ++i)
            if (now.legal(i, nxt)) {
                Q[r++] = nxt;
                Q[r - 1].pre = f - 1;
                if (i < 3) Q[r - 1].c = 'A' + i;
                else Q[r - 1].c = 'a' + i - 3;
                if (nxt == End) return r - 1;
            }
    }
    return -1;
}

int main() {

    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &Num, &N);
        printf("%d %d\n", Num, N);
        memset(conv, 0, sizeof(conv));
        for (int i = 0; i < 3; ++i) {
            conv[i][0][i] = 1;
            for (int j = 0; j < 3; ++j)
                scanf("%d", &conv[i][1][j]);
        }
        for (int i = 3; i < 6; ++i)
            for (int d = 0; d < 2; ++d)
                for (int j = 0; j < 3; ++j)
                    conv[i][d][j] = conv[i - 3][d ^ 1][j];
        for (int k = 0; k < N; ++k) {
            int id;
            scanf("%d", &id);
            printf("%d ", id);
            Start.load(); End.load();
            int p = bfs();
            if (p < 0) printf("NO SOLUTION\n");
            else {
                int cnt = 0;
                int l = 0;
                while (p != 0) {
                    cnt++;
                    ans[l++] = Q[p].c;
                    p = Q[p].pre;
                }
                printf("%d ", cnt);
                for (int i = l - 1; i >= 0; --i) putchar(ans[i]);
                printf("\n");
            }
        }
    }

    return 0;

}
