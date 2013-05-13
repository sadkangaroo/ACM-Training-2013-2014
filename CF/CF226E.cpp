#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 100000 + 5, MaxM = 100000 + 5, MaxE = MaxN, Step = 18;
const int MaxNode = MaxN * 4 + MaxM * 20 * 2;

int N, M, root, tot;
int depth[MaxN], lb[MaxN], rb[MaxN];
int fa[MaxN][Step + 1], attacked[MaxN];

struct etp {
    int t; etp* nxt; 
    etp() {}
    etp(int _t, etp* _nxt): t(_t), nxt(_nxt) {}
}*e[MaxN], bufe[MaxE], *cbufe;

struct Node {
    int sum;
    Node *l, *r; 
    Node() {
        sum = 0;
        l = r = NULL;
    }
    void update() {
        sum = l->sum + r->sum;
    }
}*head[MaxM], bufn[MaxNode], *cbufn, *tmp;

void dfs(int now) {
    lb[now] = ++tot;
    for (int i = 1; i <= Step; ++i) 
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (etp* u = e[now]; u; u = u->nxt) { 
        depth[u->t] = depth[now] + 1;
        fa[u->t][0] = now;
        dfs(u->t);
    }
    rb[now] = tot;
}

int goUp(int x, int k) {
    for (int i = 0; i <= Step; ++i)
        if (k & (1 << i)) x = fa[x][i];
    return x;
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    a = goUp(a, depth[a] - depth[b]);
    if (a == b) return a;
    for (int i = Step; i >= 0; --i)
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i]; b = fa[b][i];
        }
    return fa[a][0];
}

void buildFirst(Node* now, int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    now->l = new(cbufn++)Node(); now->r = new(cbufn++)Node();
    buildFirst(now->l, l, mid);
    buildFirst(now->r, mid + 1, r);
}

void buildNext(Node* last, Node* now, int l, int r, int p, int x) {
    if (l == r) {
        now->sum = last->sum + x;
        return;
    }
    int mid = (l + r) / 2;
    if (p <= mid) {
        now->r = last->r;
        now->l = new(cbufn++)Node();
        buildNext(last->l, now->l, l, mid, p, x);
    }
    else {
        now->l = last->l;
        now->r = new(cbufn++)Node();
        buildNext(last->r, now->r, mid + 1, r, p, x);
    }
    now->update();
}

int query(Node* last, Node* now, int l, int r, int a, int b) {
    if (a > b) return 0;
    if (a <= l && b >= r) return now->sum - last->sum;
    int res = 0;
    int mid = (l + r) / 2;
    if (a <= mid) res += query(last->l, now->l, l, mid, a, b);
    if (b > mid) res += query(last->r, now->r, mid + 1, r, a, b);
    return res;
}

int search(int now, int ki, int yi, int Y) {
    for (int i = Step; i >= 0; --i) {
        int t1 = depth[now] - query(head[yi], head[Y], 1, tot, 1, lb[now]);
        int t2 = depth[fa[now][i]] - query(head[yi], head[Y], 1, tot, 1, lb[fa[now][i]]);
        int d = t1 - t2;
        if (d < ki) {
            ki -= d;
            now = fa[now][i];
        }
    }
    return now;
}

int main() {

    cbufe = bufe;
    cbufn = bufn;
    memset(e, 0, sizeof(e));
    scanf("%d", &N);
    memset(attacked, 0, sizeof(attacked));
    int x;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &x);
        if (x == 0) root = i;
        else e[x] = new(cbufe++)etp(i, e[x]);
    }
    tot = 0;
    depth[root] = 1;
    memset(fa, 0, sizeof(fa));
    dfs(root);
    tot++;
    scanf("%d", &M);
    int typ, ci, ai, bi, ki, yi;
    head[0] = new(cbufn++)Node();
    buildFirst(head[0], 1, tot);
    for (int Y = 1; Y <= M; ++Y) {
        scanf("%d", &typ); 
        if (typ == 1) {
            scanf("%d", &ci);
            attacked[ci] = Y;
            tmp = new(cbufn++)Node();
            buildNext(head[Y - 1], tmp, 1, tot, lb[ci], 1);        
            head[Y] = new(cbufn++)Node();
            buildNext(tmp, head[Y], 1, tot, rb[ci] + 1, -1);
        }
        else {
            scanf("%d%d%d%d", &ai, &bi, &ki, &yi);
            head[Y] = head[Y - 1];
            ci = lca(ai, bi);
            int ta = depth[ai] - query(head[yi], head[Y], 1, tot, 1, lb[ai]);
            int tb = depth[bi] - query(head[yi], head[Y], 1, tot, 1, lb[bi]);
            int tc = depth[ci] - query(head[yi], head[Y], 1, tot, 1, lb[ci]);
            int da = attacked[ai] <= yi;
            int db = attacked[bi] <= yi;
            int dc = attacked[ci] <= yi;
            int aval = ta - tc - ((ai != ci) && da);
            int avar = tb - tc - ((bi != ci) && db);
            int avac = (ai != ci) && (bi != ci) && dc;
            if (aval + avar + avac < ki) printf("-1\n");
            else if (aval == ki - 1 && avac) printf("%d\n", ci);
            else if (aval >= ki) {
                     printf("%d\n", search(fa[ai][0], ki, yi, Y));
                 }
                 else {
                     ki = avar - (ki - aval - avac) + 1;
                     printf("%d\n", search(fa[bi][0], ki, yi, Y));
                 }
        }
    }


    return 0;

}
