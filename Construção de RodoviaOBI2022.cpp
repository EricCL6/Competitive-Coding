#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

struct qel{
    int id, depth;
};

int marc[MAXN];
pair<int, int> MaxDepth[MAXN];
vector<int>grafo[MAXN];
queue<qel>q;
stack<int>run_back;

int bfs(int pos)
{
    q.push({pos, 0});
    while(!q.empty()){
        qel cur = q.front();
        marc[cur.id] = 1;
        if(cur.depth >= 2)return cur.id;
        for(auto viz : grafo[cur.id]){
            if(marc[viz] == 1)continue;
            marc[viz] = 1;
            q.push({viz, cur.depth + 1});
        }
        run_back.push(cur.id);
        q.pop();
    }
    while(!run_back.empty()){
        int cur = run_back.top();
        marc[cur] = 0;
        run_back.pop();
    }
    return -1;
}

int main()
{
    int n, m;cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b;cin >> a >> b;
        a--;
        b--;
        grafo[a].push_back(b);
    }
    int ans = -1;
    for(int i = 0; i < n; i++){
        if(marc[i] == 1)continue;
        ans = bfs(i);
        if(ans != -1){
            printf("%d ", i + 1);
            ans++;
            break;
        }
    }
    printf("%d\n", ans);
}