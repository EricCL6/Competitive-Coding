#include<bits/stdc++.h>
using namespace std;

const int MAXH = 1e5 + 5;

int main()
{
    int n;cin >> n;
    int h[MAXH] = {0};
    for(int i = 0; i < n; i++){
        int c, p;cin >> c >> p;
        h[c]++;
        h[p]--;
    }
    int ans = h[0];
    for(int i = 1; i < MAXH; i++){
        h[i] += h[i - 1];
        ans = max(ans, h[i]);
    }
    cout << ans*20 << "\n";
}