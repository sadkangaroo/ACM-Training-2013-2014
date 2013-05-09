#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 100000 + 5;
const int MaxNode = 4 * MaxN + MaxN * 20;

struct Node {
    int sz;
    Node *l, *r;
    Node() {
       sz = 0;
       l = r = NULL; 
    }
    void update() {
        sz = l->sz + r->sz;
    }
}buf[MaxNode], *cbuf, *head[MaxN];

int N, M, tot;
int a[MaxN], val[MaxN]; 

void buildFirst(Node* now, int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2; 
    now->l = new(cbuf++)Node(); 
    now->r = new(cbuf++)Node();
    buildFirst(now->l, l, mid);
    buildFirst(now->r, mid + 1, r);
    now->update();

}

void buildNext(Node* last, Node* now, int l, int r, int x) {
    if (l == r) {
        now->sz = last->sz + 1;
        return;
    }
    int mid = (l + r) / 2;
    if (x <= val[mid]) {
        now->r = last->r;
        now->l = new(cbuf++)Node();
        buildNext(last->l, now->l, l, mid, x);
    }
    else {
        now->l = last->l;
        now->r = new(cbuf++)Node();
        buildNext(last->r, now->r, mid + 1, r, x);
    }
    now->update();
}

int query(Node* last, Node* now, int l, int r, int kk) {
    if (l == r) return val[l];
    int mid = (l + r) / 2;
    if (kk <= now->l->sz - last->l->sz) 
        return query(last->l, now->l, l, mid, kk);
    else return query(last->r, now->r, mid + 1, r, kk - (now->l->sz - last->l->sz));
}

int main() {

    cbuf = buf;
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; ++i) {
        scanf("%d", a + i);
        val[i] = a[i];
    }
    sort(val, val + N);
    tot = unique(val, val + N) - val;
    head[0] = new(cbuf++)Node();
    buildFirst(head[0], 0, tot - 1);
    for (int i = 0; i < N; ++i) {
        head[i + 1] = new(cbuf++)Node();
        buildNext(head[i], head[i + 1], 0, tot - 1, a[i]);
    }
    int ll, rr, kk;
    for (int Que = 0; Que < M; ++ Que) {
        scanf("%d%d%d", &ll, &rr, &kk); 
        printf("%d\n", query(head[ll - 1], head[rr], 0, tot - 1, kk));
    }

    return 0;

}
