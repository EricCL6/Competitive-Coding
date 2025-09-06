#include<bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const int INF = 1e9;

int v[2 * MAXN];
int sum[2 * MAXN];
int dp[2 * MAXN][2 * MAXN];

int main()
{
    int n;
    double f;
    cin >> n >> f;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        v[i + n] = v[i];
    }
    for(int i = 0; i < 2*n; i++){
        sum[i] = v[i];
        if(i == 0)continue;
        sum[i] += sum[i - 1];
    }
    for(int size = 1; size < n; size++){
        for(int ini = 0; ini + size < 2*n; ini++){
            int fim = ini + size;
            dp[ini][fim] = INF;
            for(int pos = ini; pos < fim; pos++){
                dp[ini][fim] = min(dp[ini][fim], max(sum[pos]-sum[ini]+v[ini], sum[fim]-sum[pos]) + dp[ini][pos] + dp[pos + 1][fim]);
            }
            //printf("%d %d %d\n", ini, fim, dp[ini][fim]);
        }
    }
    int ans = INF;
    for(int i = 0; i < n; i++){
        ans = min(ans, dp[i][i + n - 1]);
    }
    printf("%.2f\n", ans*f);
}