#include<bits/stdc++.h>
using namespace std;

const int INF = 2 * 1e6 + 5;
const int MAXN = 1e3 + 5;

struct ret{
    int x1, y1, x2, y2;
};

struct node{
    int pos, dis;
};

int dist(ret a, ret b)
{
    bool bx = false;
    if((b.x1 <= a.x1 and a.x1 <= b.x2) or (b.x1 <= a.x2 and a.x2 <= b.x2)){
        bx = true;
    }
    if((a.x1 <= b.x1 and b.x1 <= a.x2) or (a.x1 <= b.x2 and b.x2 <= a.x2)){
        bx = true;
    }

    bool by  = false;
    if((b.y1 <= a.y1 and a.y1 <= b.y2) or (b.y1 <= a.y2 and a.y2 <= b.y2)){
        by = true;
        //printf("y\n");
    }if((a.y1 <= b.y1 and b.y1 <= a.y2) or (a.y1 <= b.y2 and b.y2 <= a.y2)){
        by = true;
    }

    if(by and bx)return 0;
    if(by)return min(abs(a.x2 - b.x1), abs(a.x1 - b.x2));
    if(bx)return min(abs(a.y2 - b.y1), abs(a.y1 - b.y2));

    int ans = abs(a.x1 - b.x2) + abs(a.y1 - b.y2);
    ans = min(ans, abs(a.x1 - b.x2) + abs(a.y2 - b.y1));
    ans = min(ans, abs(a.x2 - b.x1) + abs(a.y1 - b.y2));
    ans = min(ans, abs(a.x2 - b.x1) + abs(a.y2 - b.y1));
    return ans;
}

vector<node>grafo[MAXN];

int main()
{
    int xi, yi, xf, yf;scanf("%d %d %d %d", &xi, &yi, &xf, &yf);
    int n;scanf("%d", &n);
    ret v[n + 2];
    v[0] = {xi, yi, xi, yi};
    v[n + 1] = {xf, yf, xf, yf};
    for(int i = 1; i <= n; i++){
        scanf("%d %d %d %d", &v[i].x1, &v[i].y1, &v[i].x2, &v[i].y2);
    }
    for(int i = 0; i < n + 2; i++){
        for(int j = i + 1; j < n + 2; j++){
            int dis = dist(v[i], v[j]);
            grafo[i].push_back({j, dis});
            grafo[j].push_back({i, dis});
            //printf("%d %d %d\n", i, j, dis);
        }
    }
    int ans[n + 2];
    int marc[n + 2] = {0};
    priority_queue<pair<int, int>>pq;
    pq.push({0, 0});
    while(!pq.empty()){
        pair<int, int>top = pq.top();
        pq.pop();

        int pos = top.second;
        int d = -top.first;

        if(marc[pos] == 1)continue;
        marc[pos] = 1;

        ans[pos] = d;

        for(auto viz : grafo[pos]){
            if(marc[viz.pos] == 1)continue;
            pq.push({-(viz.dis + d), viz.pos});
        }
    }
    printf("%d\n", ans[n + 1]);
}