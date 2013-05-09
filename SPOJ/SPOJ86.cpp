#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<vector>
#include<set>

using namespace std;

const int MaxN = 40000 + 5;

typedef long long LL;

struct Roof {
    int x1, y1, x2, y2;
    void load() {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    }
}roof[MaxN];

int X, Last;

struct RoofCmp {
    bool operator() (const int _a, const int _b) {
        Roof a = roof[_a], b = roof[_b];
        return (LL)(b.x2 - b.x1) * ((LL)(a.x2 - a.x1) * a.y1 + (LL)(a.y2 - a.y1) * (X - a.x1))
            > (LL)(a.x2 - a.x1) * ((LL)(b.x2 - b.x1) * b.y1 + (LL)(b.y2 - b.y1) * (X - b.x1));
    }
};

struct Event {
    int lab, x, y, typ;
    Event() {}
    Event(int _lab, int _x, int _y, int _typ) {
        lab = _lab; x = _x; y = _y; typ = _typ;
    }
    bool operator < (const Event &t) const {
        if (x != t.x) return x < t.x;
        if (typ != t.typ) return typ > t.typ;
        if (typ == 1) return y < t.y;
        else return y > t.y;
    }
}event[MaxN * 2];


int N, tot;
int downto[MaxN], ans[MaxN], deg[MaxN];
vector<int> src;
set<int, RoofCmp> S;
set<int>::iterator it;

int T;

int main() {

    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N); 
        for (int i = 0; i < N; ++i)
            roof[i].load();
        tot = 0;
        for (int i = 0; i < N; ++i) {
            event[tot++] = Event(i, roof[i].x1, roof[i].y1, 1);
            event[tot++] = Event(i, roof[i].x2, roof[i].y2, -1);
        }
        sort(event, event + tot);
        memset(downto, -1, sizeof(downto));
        memset(ans, 0, sizeof(ans));
        src.clear();
        memset(deg, 0, sizeof(deg));
        S.clear();
        S.insert(event[0].lab);
        Last = event[0].x;
        for (int i = 1; i < tot; ++i) {
            Event now = event[i]; 
            X = now.x;
            if (!S.empty()) 
                ans[*(S.begin())] += X - Last;
            if (now.typ == 1 && roof[now.lab].y1 < roof[now.lab].y2
                    || now.typ == -1 && roof[now.lab].y2 < roof[now.lab].y1) {
                it = S.upper_bound(now.lab);      
                if (it != S.end()) {
                    downto[now.lab] = *it;
                    deg[*it]++;
                }
            }
            if (now.typ == 1) S.insert(now.lab);
            else S.erase(now.lab);
            Last = X;
        }
        for (int i = 0; i < N; ++i) 
            if (deg[i] == 0) src.push_back(i);
        while (!src.empty()) {
            int now = src[(int)src.size() - 1];
            src.pop_back();
            int to = downto[now];
            if (to != -1) {
                ans[to] += ans[now];
                deg[to]--;
                if (deg[to] == 0) src.push_back(to);
            }
        }
        for (int i = 0; i < N; ++i) 
            printf("%d\n", ans[i]);
    }

    return 0;

}
