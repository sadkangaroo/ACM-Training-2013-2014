#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<algorithm>
#include<map>

using namespace std;

typedef long long LL;

const int MaxN = 50000 + 5;

map<LL, int> Map;

int hash(char* s) {
    int res = 0;
    int l = strlen(s);
    for (int i = 0; i < l; ++i)
        res = res * 999983 + s[i];
    return res;
}

int N;
char com[5], name[30];
int events[MaxN], tot;

int main() {

    Map.clear();
    scanf("%d", &N);
    tot = 1;
    for (int i = 1; i <= N; ++i) {
        scanf("%s", com);
        if (com[0] == 'E') {
            scanf("%s", name);
            LL now = hash(name);
            events[tot++] = now;
            Map[now] = tot - 1;
        }
        else if (com[0] == 'D') {
            int x; 
            scanf("%d", &x);
            for (int k = 0; k < x; ++k) {
                tot--;
                Map[events[tot]] = 0;
            }
        }
        else if (com[0] == 'S') {
            int num;
            scanf("%d", &num);
            bool flag = true;
            int r = 0, tmp = 0;
            for (int k = 0; k < num; ++k) {
                scanf("%s", name);
                if (!flag) continue;
                if (name[0] != '!') {
                    LL code = hash(name);
                    int last = Map[code];
                    if (last == 0) flag = false;
                    else tmp = max(tmp, last);
                }
                else {
                    LL code = hash(name + 1);  
                    int last = Map[code];
                    if (last != 0) r = max(r, tot - last);
                }
            }
            if (!flag || tot - r <= tmp) printf("Plot Error\n");
            else {
                if (r == 0) printf("Yes\n");
                else printf("%d Just A Dream\n", r);
            }
        }
    }

    return 0;

}
