#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5+5;

int pai[MAXN], depth[MAXN];

int find(int cur)
{
    int root = pai[cur];
    if(pai[root] != root){
        return pai[cur] = find(root);
    }
    return root;
}

void unionSets(int a, int b)
{
    int paia = find(a);
    int paib = find(b);

    if(paia == paib)return;
    if(depth[paia] < depth[paib]){
        pai[paia] = paib;
        return;
    }
    else if(depth[paib] < depth[paia]){
        pai[paib] = paia;
    }
    else{
        pai[paib] = paia;
        depth[paia]++;
    }
}

int main()
{
    int n, k;cin >> n >> k;
    for(int i = 1; i <= n; i++){
        pai[i] = i;
        depth[i] = 0;
    }
    for(int i = 0; i < k; i++){
        char o;
        int a, b;
        cin >> o >> a >> b;
        if(o == 'F'){
            unionSets(a, b);
        }
        if(o == 'C'){
            int paia = find(a);
            int paib = find(b);
            if(paia == paib)printf("S\n");
            else printf("N\n");
        }
        //printf("%d\n", i);
    }
}