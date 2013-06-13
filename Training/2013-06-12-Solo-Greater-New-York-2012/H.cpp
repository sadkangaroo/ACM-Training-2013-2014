#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>

using namespace std;

const int MaxM = 20 + 3;
const double Pi = acos(-1.0);
const double eps = 1e-8;

int T, Num, M, S, Start;
double iniAng;

struct Node {
    double x, y, ang;
    int lab;
    Node() {}
    Node(double _x, double _y, double _ang, int _lab): x(_x), y(_y), ang(_ang), lab(_lab) {}
    bool operator < (const Node &t) const {
        return ang < t.ang;
    }
}pts[MaxM], List[MaxM][MaxM];

double ref(double x) {
    if (x < -Pi) x += 2 * Pi;
    if (x >= Pi) x -= 2 * Pi;
    return x;
}

double calc(double a1, double a2) {
    if (a2 < a1) a2 += 2 * Pi;
    return a2 - a1;
}

int main() {

    scanf("%d", &T);
    while (T--) {
        int tmp;
        double x, y;
        scanf("%d%d%d%d%lf", &Num, &M, &S, &Start, &iniAng);
        printf("%d", Num);
        Start--;
        for (int i = 0; i < M; ++i) {
            scanf("%d%lf%lf", &tmp, &x, &y);
            pts[i] = Node(x, y, 0, 0);     
        }
        for (int i = 0; i < M; ++i) {
            int tot = 0;
            for (int j = 0; j < M; ++j)
                if (j != i) List[i][tot++] = Node(pts[j].x, pts[j].y, atan2(pts[j].y - pts[i].y, pts[j].x - pts[i].x), j);
            sort(List[i], List[i] + tot);
        }
        int now = Start; double ang = iniAng / 180.0 * Pi;
        /*
        cout << endl;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j + 1 < M; ++j) cout << List[i][j].ang << ' ';
            cout << endl;
        }
        */
        for (int step = 1; step <= S; ++step) {
            int id;
            int id1 = lower_bound(List[now], List[now] + M - 1, Node(0, 0, ang + eps, 0)) - List[now];
            if (id1 == M - 1) id1 = 0;
            int id2 = lower_bound(List[now], List[now] + M - 1, Node(0, 0, ref(ang + Pi) + eps, 0)) - List[now];
            if (id2 == M - 1) id2 = 0;
            if (calc(ang, List[now][id1].ang) < calc(ref(ang + Pi), List[now][id2].ang))
                id = id1;
            else id = id2;
            int nxt = List[now][id].lab;
            printf(" %d", nxt + 1);
            ang = List[now][id].ang;
            now = nxt;
        }
        printf("\n");
    }

    return 0;

}
