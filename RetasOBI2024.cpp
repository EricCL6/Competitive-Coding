#include<bits/stdc++.h>
using namespace std;
#define lli long long int

const int MAXN = 1e5 + 5;

int seg[4*MAXN];

void build(int pos, int ini, int fim, vector<pair<lli, int>>&v)
{
    if(ini == fim){
        seg[pos] = v[ini].second;
        return;
    }
    int m = (ini + fim)/2;
    int e = 2*pos, d = 2*pos + 1;
    build(e, ini, m, v);
    build(d, m + 1, fim, v);
    seg[pos] = seg[e] + seg[d];
}

int query(int pos, int ini, int fim, int l, int r)
{
    if(fim < l or r < ini)return 0;
    if(l <= ini and fim <= r)return seg[pos];
    int m = (ini + fim)/2;
    int e = 2*pos, d = 2*pos + 1;
    int qe = query(e, ini, m, l, r);
    int qd = query(d, m + 1, fim, l, r);
    return qe + qd;
}

void update(int pos, int ini, int fim, int dest)
{
    if(fim < dest or dest < ini)return;
    if(ini == fim){
        seg[pos]--;
        return;
    }
    int m = (ini + fim)/2;
    int e = 2*pos, d = 2*pos + 1;
    update(e, ini, m, dest);
    update(d, m + 1, fim, dest);
    seg[pos] = seg[e] + seg[d];
}

int bs(lli val, vector<pair<lli, int>>&v)
{
    int ini = 0;
    int fim = v.size() - 1;
    while(ini < fim){
        int m = (ini + fim)/2;
        if(val < v[m].first)fim = m - 1;
        else if(val > v[m].first)ini = m + 1;
        else return m;
    }
    return ini;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    lli x1, x2;
    cin >> n >> x1 >> x2;
    vector<pair<lli, lli>>r;
    vector<lli>ev;
    vector<pair<lli, int>>exit;
    for(int i = 0; i < n; i++){
        int a, b;cin >> a >> b;
        lli ent = (lli)a*x1 + b;
        lli sai = (lli)a*x2 + b;
        //printf("%lld %lld\n", ent, sai);
        r.push_back({ent, -sai});
        ev.push_back(sai);
    }
    sort(r.begin(), r.end());
    sort(ev.begin(), ev.end());
    for(auto cur : ev){
        if(exit.empty() or exit.back().first != cur)exit.push_back({cur, 1});
        else exit.back().second++;
    }
    //for(auto u : exit)printf("%lld %d\n", u.first, u.second);

    lli ans = 0;
    build(1, 0, exit.size() - 1, exit);

    for(auto u : r){
        int id = bs(-u.second, exit);

        if(id >= 0 && id < exit.size() && exit[id].first == -u.second){
            update(1, 0, exit.size() - 1, id);
            ans += query(1, 0, exit.size() - 1, 0, id);
        }
    }
    printf("%lld\n", ans);
}