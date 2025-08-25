#include<bits/stdc++.h>
using namespace std;

struct vert{
    pair<int, int>max1, max2, min1, min2;
};

const int MAXN = 1e5 + 5;
const int INF = 1e6  +5;

vert seg[4*MAXN];

vert merge(vert e, vert d)
{
    char g;

    vert r;

    if(e.max1 > d.max1)g = 'e';
    else if(d.max1 > e.max1)g = 'd';
    else {
        if(e.min1 > d.min1)g = 'e';
        else g = 'd';
    }

    if(g == 'e'){
        r.max1 = e.max1;
        r.max2 = max(d.max1, e.max2);
    }
    if(g == 'd'){
        r.max1 = d.max1;
        r.max2 = max(e.max1, d.max2);
    }

    char l;

    if(e.min1 < d.min1)l = 'e';
    else if(d.min1 < e.min1)l = 'd';
    else{
        if(e.max1 < d.max1)l = 'e';
        else l = 'd';
    }

    if(l == 'e'){
        r.min1 = e.min1;
        r.min2 = min(d.min1, e.min2);
    }
    if(l == 'd'){
        r.min1 = d.min1;
        r.min2 = min(e.min1, d.min2);
    }

    return r;
}

void build(int pos, int ini, int fim, int* v)
{
    if(ini == fim){
        seg[pos].max1 = {v[ini], ini};
        seg[pos].min1 = {v[ini], ini};
        seg[pos].max2 = {0, 0};
        seg[pos].min2 = {INF, 0};
        return;
    }

    int m = (ini + fim)/2;
    int e = 2*pos, d = 2*pos + 1;

    build(e, ini, m, v);
    build(d, m + 1, fim, v);

    seg[pos] = merge(seg[e], seg[d]);
}

void update(int pos, int ini, int fim, int dest, int val)
{
    if(dest < ini or fim < dest)return;
    if(ini == fim){
        seg[pos].max1 = max(seg[pos].max1, {val, ini});
        seg[pos].min1 = min(seg[pos].min1, {val, ini});
        return;
    }

    int m = (ini + fim)/2;
    int e = 2*pos, d = 2*pos + 1;

    update(e, ini, m, dest, val);
    update(d, m + 1, fim, dest, val);

    seg[pos] = merge(seg[e], seg[d]);
}

vert query(int pos, int ini, int fim, int l, int r)
{
    if(fim < l or r < ini){
        vert zero;
        zero.max1 = {0, 0};
        zero.min1 = {INF, 0};
        zero.max2 = {0, 0};
        zero.min2 = {INF, 0};
        return zero;
    }
    if(l <= ini and fim <= r)return seg[pos];

    int m = (ini + fim)/2;
    int e = 2*pos, d = 2*pos+1;

    vert qe = query(e, ini, m, l, r);
    vert qd = query(d, m + 1, fim, l, r);

    return merge(qe, qd);
}

int main()
{
    int n, m;scanf("%d %d", &n, &m);
    int v[n + 1];for(int i = 1; i <= n; i++)scanf("%d", &v[i]);
    build(1, 1, n, v);
    for(int i = 0; i < m; i++){
        int t, a, b;scanf("%d %d %d", &t, &a, &b);
        if(t == 1)update(1, 1, n, b, a);
        if(t == 2){
            vert ans = query(1, 1, n, a, b);
            int out;
            if(ans.max1.second == ans.min1.second){
                out = max(ans.max1.first-ans.min2.first, ans.max2.first-ans.min1.first);
            }
            else out = ans.max1.first-ans.min1.first;
            printf("%d\n", out);
        }
    }
}