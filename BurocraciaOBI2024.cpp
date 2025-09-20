#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int LOG = 32;

vector<int>grafo[MAXN];
int tin[MAXN], tout[MAXN], pai[MAXN];
int bl[MAXN][LOG];
int tempo = 0;

void dfs(int pos, int prev)
{
    pai[pos] = prev;
    
    tempo++;
    tin[pos] = tempo;

    for(auto viz : grafo[pos]){
        if(viz == prev)continue;
        dfs(viz, pos);
    }
    tout[pos] = tempo;
}

int seg[4*MAXN];

void update(int pos, int ini, int fim, int l, int r, int val)
{
    if(fim < l or r < ini)return;
    if(l <= ini and fim <= r){
        if(seg[pos] == 0)seg[pos] = val;
        else seg[pos] = min(seg[pos], val); 
        return;
    }

    int m = (ini + fim)/2;
    int e = 2*pos, d = 2*pos + 1;

    update(e ,ini, m, l, r, val);
    update(d, m + 1, fim, l, r, val);
}

int query(int pos, int ini, int fim, int dest)
{
    if(dest < ini or fim < dest)return -1;
    if(ini == fim or seg[pos] != 0)return seg[pos];

    int m = (ini + fim)/2;
    int e = 2*pos, d = 2*pos + 1;

    int q1 = query(e, ini, m, dest);
    int q2 = query(d, m + 1, fim, dest);

    return max(q1, q2);
}

int main()
{
    int n;cin >> n;
    for(int i = 2; i <= n; i++){
        int p;cin >> p;
        grafo[i].push_back(p);
        grafo[p].push_back(i);
    }
    dfs(1, 1);

    for(int i = 1; i <= n; i++){
        update(1, 1, n, tin[i], tin[i], pai[i]);
    }

    for(int i = 0; i < LOG; i++){
        for(int j = 1; j <= n; j++){
            if(i == 0)bl[j][i] = pai[j];
            else bl[j][i] = bl[bl[j][i - 1]][i - 1];
        }
    }

    int q;cin >> q;
    for(int i = 0; i < q; i++){
        int o, v; cin >> o >> v;
        if(o == 1){
            int k; cin >> k;
            k--;
            int cur = query(1, 1, n, tin[v]);

            for(int i = 0; i < LOG; i++){
                if(k & (1 << i)){
                    cur = bl[cur][i];
                }
            }
            printf("%d\n", cur);
        }
        if(o == 2){
            update(1, 1, n, tin[v] + 1, tout[v], v);
        }
    }
}