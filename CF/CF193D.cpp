#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

typedef long long LL;

const int MaxN = 3 * 100000 + 5;

int N;
int p[MaxN], a[MaxN];

struct Node {
    int add, min, a, b;
    void getAdded(int x) {
        min += x;
        add += x;
    }
    void update(Node* lc, Node* rc) {
        min = std::min(lc->min, rc->min); 
        a = (lc->min == min) * lc->a + (rc->min == min) * rc->a;
        b = (lc->min == min) * lc->b + (rc->min == min) * rc->b 
            + (lc->min == min + 1) * lc->a + (rc->min == min + 1) * rc->a;
    }
    void push(Node* lc, Node* rc) {
        lc->getAdded(add); rc->getAdded(add);
        add = 0;
    }
}st[MaxN * 4];

void build(Node* st, int now, int l, int r) {
    st[now].a = r - l + 1;
    if (l == r) return;
    int mid = (l + r) / 2;
    build(st, now * 2, l, mid); 
    build(st, now * 2 + 1, mid + 1, r);
}

void add(Node* st, int now, int l, int r, int a, int b, int x) {
    if (a <= l && b >= r) {
        st[now].getAdded(x);
        return;
    }
    int mid = (l + r) / 2;
    st[now].push(&st[now * 2], &st[now * 2 + 1]);
    if (a <= mid) add(st, now * 2, l, mid, a, b, x);
    if (b > mid) add(st, now * 2 + 1, mid + 1, r, a, b, x);
    st[now].update(&st[now * 2], &st[now * 2 + 1]);
}

int query(Node* st, int now, int l, int r, int a, int b) {
    if (a <= l && b >= r) {
        return (st[now].min == 1) * (st[now].a + st[now].b)
            + (st[now].min == 2) * st[now].a;
    }
    st[now].push(&st[now * 2], &st[now * 2 + 1]);
    int ret = 0;
    int mid = (l + r) / 2;
    if (a <= mid) ret += query(st, now * 2, l, mid, a, b);
    if (b > mid) ret += query(st, now * 2 + 1, mid + 1, r, a, b);
    st[now].update(&st[now * 2], &st[now * 2 + 1]);
    return ret;
}

int main() {

    scanf("%d", &N);
    int x;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", p + i);
        a[p[i]] = i;
    }
    LL ans = 0;
    build(st, 1, 1, N);
    for (int i = 1; i <= N; ++i) {
        int x = a[i];
        add(st, 1, 1, N, 1, i, 1);
        if (x - 1 >= 1 && p[x - 1] < i)
            add(st, 1, 1, N, 1, p[x - 1], -1);
        if (x + 1 <= N && p[x + 1] < i)
            add(st, 1, 1, N, 1, p[x + 1], -1);
        ans += query(st, 1, 1, N, 1, i);
    }
    cout << ans  - N << endl;

    return 0;

}
