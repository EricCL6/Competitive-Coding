#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

struct vert{
    int pai;
    int prof = 0;
    long long int sub = 1;
    int lz = 0;
    int imp = 0;
    vector<int> adj;
};

vert grafo[MAXN];
bool marc[MAXN];

void dfs(int pos)
{
    if(marc[pos])return;
    marc[pos] = true;

    for(int viz : grafo[pos].adj){
        if(marc[viz])continue;

        grafo[viz].pai = pos;
        grafo[viz].prof = grafo[pos].prof + 1;
        dfs(viz);
        grafo[pos].sub += grafo[viz].sub;
    }
}

int main()
{
    int n;scanf("%d", &n);
    for(int i = 0; i < n - 1; i ++){
        int a, b, c;scanf("%d %d %d", &a, &b, &c);
        if(c == 1){
            grafo[a].imp++;
            grafo[b].imp++;
        }
        grafo[a].adj.push_back(b);
        grafo[b].adj.push_back(a);
    }

    dfs(1);

    long long int tot = n;
    long long int ans = 0;

    pair<int, int>order[n];

    for(int i = 1; i <= n; i++){
        order[i - 1] = {-grafo[i].prof, i};
    }

    sort(order, order + n);

    for(int i = 0; i < n; i++){
        int cur = order[i].second;

        grafo[grafo[cur].pai].lz += grafo[cur].lz;

        //printf("%d %d %d\n", cur, grafo[cur].imp, order[i].first);

        if(grafo[cur].imp == 0)continue;

        grafo[cur].sub -= grafo[cur].lz;
        grafo[grafo[cur].pai].lz += grafo[cur].sub;
        grafo[grafo[cur].pai].imp--;
        tot -= grafo[cur].sub;

        ans += grafo[cur].sub*tot;
    }
    printf("%lld\n", ans);
}