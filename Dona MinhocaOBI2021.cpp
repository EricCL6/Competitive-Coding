#include<bits/stdc++.h>
using namespace std;

const int MAXN = 5e4 + 5;

vector<int>grafo[MAXN];

int dist[MAXN];
int is_d[MAXN];

void calc_dist(int pos, int pai, int d)
{
    dist[pos] = d;
    for(auto viz : grafo[pos]){
        if(viz == pai)continue;
        calc_dist(viz, pos, d + 1);
    }
}

int find_center(int pos, int pai, int des, int diametro, stack<int>path, int size)
{
    path.emplace(pos);
    if(pos == des){
        if(diametro%2 == 0){
            for(int i = 0; i < diametro/2 - 1; i++){
                path.pop();
            }

            int ant = path.top();
            path.pop();
            int cur = path.top();

            grafo[size].push_back(ant);
            grafo[size].push_back(cur);

            for(int i = 0; i < grafo[ant].size(); i++){
                if(grafo[ant][i] == cur)grafo[ant][i] = size;
            }
            for(int i = 0; i < grafo[cur].size(); i++){
                if(grafo[cur][i] == ant)grafo[cur][i] = size;
            }

            return size;
        }
        if(diametro%2 == 1){
            for(int i = 0; i < diametro/2; i++){
                path.pop();
            }
            return path.top();
        }
    }
    int ans = -1;
    for(auto viz : grafo[pos]){
        if(viz == pai)continue;
        ans = max(ans, find_center(viz, pos, des, diametro, path, size));
    }
    return ans;
}

int count_ex(int pos, int pai)
{
    int ans = is_d[pos];
    for(auto viz : grafo[pos]){
        if(viz == pai)continue;
        ans += count_ex(viz, pos);
    }
    return ans;
}

void reset_dist(int size)
{
    for(int i = 0; i < size; i++)dist[i] = 0;
}

int main()
{
    long long int n;cin >> n;
    for(int i = 0; i < n -1; i++){
        int a, b;cin >> a >> b;
        a--;
        b--;
        grafo[a].push_back(b);
        grafo[b].push_back(a);
    }
    int diametro = 0;
    int f1 = 0;
    int f2 = 0;
    long long int tot = 0;

    calc_dist(0, 0, 1);
    for(int i = 0; i < n; i++){
        if(dist[i] > diametro){
            diametro = dist[i];
            f1 = i;
        }
    }
    reset_dist(n);

    calc_dist(f1, f1, 1);
    for(int i = 0; i < n; i++){
        if(dist[i] > diametro){
            diametro = dist[i];
            f2 = i;
        }
    }

    printf("%d\n", diametro);
    if(diametro <= 2){
        printf("1\n");
        return 0;
    }

    for(int i = 0; i < n; i++){
        if(dist[i] == diametro){
            is_d[i] = 1;
            tot++;
        }
    }
    reset_dist(n);

    calc_dist(f2, f2, 1);
    for(int i = 0; i < n; i++){
        if(dist[i] == diametro and is_d[i] == 0){
            is_d[i] = 1;
            tot++;
        }
    }
    stack<int>aux;
    int c = find_center(f1, f1, f2, diametro, aux, n);

    /*for(int i = 0; i <= n; i++){
        printf("%d:", i);
        for(auto viz : grafo[i])printf("%d ", viz);
        printf("\n");
    }*/

    long long int ans = 0;
    //printf("%d %lld\n", c, tot);
    for(auto viz : grafo[c]){
        long long int count = count_ex(viz, c);
        //printf("%d %lld\n", viz, count);
        tot -= count;
        ans += count*tot;
    }
    printf("%lld\n", ans);
}