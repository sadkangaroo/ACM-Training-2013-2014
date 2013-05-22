#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxN = 1000000 + 5;
const int MaxNode = MaxN;
const int Border = 1000000;
const int oo = 0x7f7f7f7f;

typedef long long LL;

#define nonRoot(x) ((x)->fa->c[0] == (x) || (x)->fa->c[1] == (x))

struct Node {
    int key, sz;   
    Node *fa, *c[2];
    Node(): sz(0) {
        fa = c[0] = c[1] = this; 
    }
    Node(int _key, Node *_fa, Node *_c0, Node *_c1): key(_key) {
        fa = _fa; c[0] = _c0; c[1] = _c1;
    }
    void rz() {
        sz = c[0]->sz + c[1]->sz + 1; 
        c[0]->fa = c[1]->fa = this;
    }
    void zig(bool d) {
        Node *x = fa, *y = x->fa; 
        x->c[d] = c[!d]; x->rz();
        c[!d] = x; x->fa = this;
        if (y->c[0] == x) y->c[0] = this;
        else if (y->c[1] == x) y->c[1] = this;
        fa = y;
    }
    void splay() {
        while (nonRoot(this)) {
            bool d = fa->c[1] == this;
            if (!nonRoot(fa)) {zig(d); break;}
            bool dd = fa->fa->c[1] == fa;
            d != dd? (zig(d), zig(dd)): (fa->zig(dd), zig(d));
        } rz();
    }
}Tnull, *null = &Tnull, buf[MaxNode], *cbuf;

struct Splay {
    Node* root;
    Splay(int x) {
        root = new(cbuf++)Node(x, null, null, null);
        root->rz();
    }
    int select(int k) {
        Node* now = root;
        while (now->c[0]->sz != k) {
            if (now->c[0]->sz > k) now = now->c[0];
            else {k -= now->c[0]->sz + 1; now = now->c[1];}
        }; now->splay(); root = now;
        return root->key;
    }
    void search(int x) {
        Node* now = root;
        while (now->c[x > now->key] != null) {
            now = now->c[x > now->key];
        }now->splay(); root = now;
        if (x > root->key) select(root->c[0]->sz + 1);
    }
    void insert(int x) {
        search(x);
        root = new(cbuf++)Node(x, null, root->c[0], root);
        root->c[1]->c[0] = null; root->c[1]->rz(); root->rz();
    }
    void remove(int x) {
        search(x);
        Node *oldroot = root;
        root = root->c[1]; root->fa = null; select(0);
        root->c[0] = oldroot->c[0]; root->rz();
    }
    int getSize() {
        return root->sz - 1;
    }
};

int N;
int cubes[MaxN], fa[MaxN], length[MaxN];
LL number[MaxN];

int grand(int x) {
    if (fa[x] == x) return x;
    return fa[x] = grand(fa[x]);
}

void merge(Splay &Sp, int f1, int f2) {
    fa[f2] = f1;
    Sp.remove(f2);
    length[f1] += length[f2];
    number[f1] += number[f2];
}

void putCubes(Splay &Sp, int x, int c) {
    cubes[x] += c;
    if (cubes[x] > c) 
        number[grand(x)] += c;
    else {
        fa[x] = x;
        length[x] = 1;
        number[x] = c;
        Sp.insert(x);
        if (x > 1 && cubes[x - 1]) 
            merge(Sp, grand(x - 1), grand(x));
        if (x < Border && cubes[x + 1]) 
            merge(Sp, grand(x), grand(x + 1));
    }
}

int main() {

    cbuf = buf;
    Splay Sp(oo);
    int t, x, c;
    char s[20];
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        fa[i] = length[i] = number[i] = -1;
    }
    memset(cubes, 0, sizeof(cubes));
    for (int com = 0; com < N; ++com) {
        scanf("%s", s);
        if (strcmp(s, "put") == 0) {
            scanf("%d%d", &x, &c);
            putCubes(Sp, x, c);
        }
        if (strcmp(s, "tput") == 0) {
            scanf("%d%d%d", &t, &x, &c);
            int start = Sp.select(t - 1); 
            putCubes(Sp, start + x - 1, c);
        }
        if (strcmp(s, "towers") == 0) 
            printf("%d towers\n", Sp.getSize());
        if (strcmp(s, "cubes") == 0) {
            scanf("%d", &t);
            int start = Sp.select(t - 1);
            printf("%lld cubes in %dth tower\n", number[start], t); 
        } 
        if (strcmp(s, "length") == 0) {
            scanf("%d", &t);
            int start = Sp.select(t - 1);
            printf("length of %dth tower is %d\n", t, length[start]);
        }
        if (strcmp(s, "tcubes") == 0) {
            scanf("%d%d", &t, &x);
            int start = Sp.select(t - 1);
            printf("%d cubes in %dth column of %dth tower\n", cubes[start + x - 1], x, t);
        }
    }

    return 0;

}
