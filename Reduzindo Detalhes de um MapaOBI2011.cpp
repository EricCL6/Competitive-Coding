#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e2 + 5;

int pai[MAXN], depth[MAXN];

int find(int cur)
{
    int root = pai[cur];
    if(pai[root] != root){
        return pai[cur] = find(root);
    }
    return root;
}

bool unionSets(int a, int b)
{
    int paia = find(a);
    int paib = find(b);
    if(paia == paib)return false;
    if(depth[paia] < depth[paib]){
        pai[paia] = paib;
    }
    else if(depth[paib] < depth[paia]){
        pai[paib] = paia;
    }
    else{
        pai[paib] = paia;
        depth[paia]++;
    }
    return true;
}

int main()
{
    int n, m;cin >> n >> m;
    vector<pair<int, pair<int, int>>>edges;
    for(int i = 0; i < m; i++){
        int a, b, w;cin >> a >> b >> w;
        edges.push_back({w, {a, b}});
    }
    sort(edges.begin(), edges.end());

    for(int i = 1; i <= n; i++){
        pai[i] = i;
        depth[i] = 0;
    }

    int ans = 0;
    for(auto u : edges){
        int a = u.second.first;
        int b = u.second.second;
        if(unionSets(a, b))ans += u.first;
    }
    printf("%d\n", ans);
}