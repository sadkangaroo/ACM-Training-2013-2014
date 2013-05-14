#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long LL;

const int MaxN = 300 + 5;
const int oo = 0x7f7f7f7f;
const double Pi = acos(-1.0), eps = 1e-8;
const int MaxNode = MaxN * 2, MaxE = MaxN * 2;

struct Point {
    int x, y;
    void load() {
        scanf("%d%d", &x, &y);
    }
    Point() {}
    Point(int _x, int _y): x(_x), y(_y) {}
    bool operator < (const Point &t) const {
        if (x == t.x) return y < t.y;
        return x < t.x;
    }
    bool operator == (const Point &t) const {
        return x == t.x && y == t.y;
    }
    Point operator - (const Point &t) const {
        return Point(x - t.x, y - t.y);
    }
    int det(const Point &t) const {
        return x * t.y - y * t.x;
    }
}Start, Finish; vector<Point> pts, ply[MaxNode];

struct Segment {
    Point a, b; int v;
    void load() {
        a.load(); b.load();
        scanf("%d", &v);
    }
}sgs[MaxN];

struct Boarder {
    int t, side, lab;
    bool vis;
    double deg;
    Boarder(int _t, int _side, int _lab, double _deg): 
        t(_t), side(_side), lab(_lab), deg(_deg), vis(false) {}
    bool operator < (const Boarder &t) const {
        return deg < t.deg;
    }
}; vector<Boarder> stretch[MaxN * 2];

struct etp {
    int t, c, lab;
    etp *nxt, *p;
    etp() {}
    etp(int _t, etp* _nxt, int _c, int _lab): t(_t), nxt(_nxt), c(_c), lab(_lab){}
}*e[MaxNode], buf[MaxE], *cbuf;

int getLab(Point now) {
    return lower_bound(pts.begin(), pts.end(), now) - pts.begin();
}

Boarder* search(int now, double deg) {
    deg += Pi - eps; 
    if (deg >= Pi) deg -= 2 * Pi;
    int sz = stretch[now].size();
    int idx = (lower_bound(stretch[now].begin(), stretch[now].end(), Boarder(0, 0, 0, deg)) - stretch[now].begin() - 1 + sz) % sz;
    return &stretch[now][idx];
}

LL getArea2(vector<Point> &P) {
    LL res = 0;
    for (int i = 0; i + 1 < P.size(); ++i)
        res += P[i].det(P[i + 1]);
    return res;
}

bool inPly(Point S, vector<Point> &P) {
    int cnt = 0; 
    for (int i = 0; i + 1 < P.size(); ++i) {
        int d1 = P[i].y - S.y, d2 = P[i + 1].y - S.y; 
        int d = (P[i] - S).det(P[i + 1] - S);
        if (d > 0 && d1 <= 0 && d2 > 0) cnt++;
        if (d < 0 && d1 > 0 && d2 <= 0) cnt--;
    }
    return cnt != 0;
}

int N, tot, rgnum;
int side[2][MaxN]; 
int S, T, Num, d[MaxN], v[MaxN];
bool vis[MaxNode];
vector<int> ans;

void Me(int a, int b, int cab, int cba, int lab) {
    e[a] = new(cbuf++)etp(b, e[a], cab, lab);
    e[b] = new(cbuf++)etp(a, e[b], cba, lab);
    (cbuf - 1)->p = cbuf - 2; (cbuf - 2)->p = cbuf - 1;
}

int aug(int now, int Max) {
    if (now == T) return Max;
    int Rest = Max, dmin = Num, dt;
    for (etp* u = e[now]; u; u = u->nxt) if (u->c) {
        if (Rest && d[u->t] + 1 == d[now]) {
            dt = aug(u->t, min(Rest, u->c));
            u->c -= dt; u->p->c += dt; Rest -= dt;
            if (d[S] >= Num) return Max - Rest;
        } dmin = min(dmin, d[u->t] + 1);
    }
    if (Max == Rest) 
        if (!--v[d[now]]) d[S] = Num; else v[d[now] = dmin]++;
    return Max - Rest;
}

void dfs(int now) {
    vis[now] = true;
    for (etp* u = e[now]; u; u = u->nxt)
        if (!vis[u->t] && u->c) dfs(u->t);
}

int main() {

    cbuf = buf;
    memset(e, 0, sizeof(e));
    pts.clear();
    scanf("%d", &N);    
    for (int i = 0; i < 2 * N; ++i) {
        stretch[i].clear();
        ply[i].clear();
    }
    for (int i = 0; i < N; ++i) {
        sgs[i].load();
        pts.push_back(sgs[i].a);
        pts.push_back(sgs[i].b);
    }
    Start.load(); Finish.load();
    sort(pts.begin(), pts.end());
    pts.resize(unique(pts.begin(), pts.end()) - pts.begin());
    tot = pts.size();
    for (int i = 0; i < N; ++i) {
        Point vec = sgs[i].b - sgs[i].a;
        int a = getLab(sgs[i].a), b = getLab(sgs[i].b);
        stretch[a].push_back(Boarder(b, 0, i, atan2(vec.y, vec.x)));
        stretch[b].push_back(Boarder(a, 1, i, atan2(-vec.y, -vec.x)));
    }
    rgnum = 0;
    for (int i = 0; i < tot; ++i) sort(stretch[i].begin(), stretch[i].end());
    for (int i = 0; i < tot; ++i) {
        for (int k = 0; k < (int)stretch[i].size(); ++k) if (!stretch[i][k].vis) {
            Boarder* now = &stretch[i][k];
            while (!now->vis) {
                now->vis = true; ply[rgnum].push_back(pts[now->t]);
                side[now->side][now->lab] = rgnum;
                now = search(now->t, now->deg);
            }
            rgnum++; 
        }
    }
    for (int i = 0; i < N; ++i) {
        int a = side[0][i], b = side[1][i];      
        Me(a, b, sgs[i].v, sgs[i].v, i);
    }
    Num = rgnum;
    for (int i = 0; i < rgnum; ++i) {
        ply[i].push_back(ply[i][0]);
        if (inPly(Start, ply[i]) && getArea2(ply[i]) > 0) S = i;
        if (inPly(Finish, ply[i]) && getArea2(ply[i]) > 0) T = i;
    }
    memset(d, 0, sizeof(d));    
    memset(v, 0, sizeof(v)); v[0] = Num;
    int flow = 0;
    while (d[S] < Num) flow += aug(S, oo);
    printf("%d\n", flow);
    memset(vis, false, sizeof(vis));
    dfs(S);
    ans.clear();
    for (int i = 0; i < Num; ++i)
        for (etp* u = e[i]; u; u = u->nxt)
            if (vis[i] && !vis[u->t]) ans.push_back(u->lab + 1);
    int sz = ans.size();
    printf("%d\n", sz);
    for (int i = 0; i + 1 < sz; ++i) printf("%d ", ans[i]);
    printf("%d\n", ans[sz - 1]);

    return 0;

}
