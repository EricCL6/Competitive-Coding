#include<bits/stdc++.h>
using namespace std;

#define INF 1000000000
#define MAXN 305
#define MAXS 2700

int dp[MAXN][MAXN][MAXS + 5];

int main()
{
    int n, k, t;cin >> n >> k >> t;
    t = min(n*n, t);
    int v[n + 1];
    for(int i = 1; i <= n; i++)cin >> v[i];
    vector<int>pos = {0};
    for(int i = 1; i <= n; i++){
        int g;cin >> g;
        if(g == 1)pos.push_back(i);
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= k; j++){
            for(int s = 0; s <= MAXS; s++)dp[i][j][s] = INF;
        }
    }
    dp[0][0][0] = 0;
    int ans = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= min(i, k); j++){
            for(int s = 0; s <= (j*9); s++){
                dp[i][j][s] = dp[i - 1][j][s];
                if(s >= v[i] and j > 0){
                    dp[i][j][s] = min(dp[i][j][s], dp[i - 1][j - 1][s - v[i]] + abs(i - pos[j]));
                }
                if(dp[i][j][s] <= t)ans = max(ans, s);
            }
        }
    }
    printf("%d\n", ans);
}