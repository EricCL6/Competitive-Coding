#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;cin >> n >> m;
    long long int v[n];for(int i = 0; i < n; i++)cin >> v[i];
    sort(v, v + n);

    multiset<pair<long long int, long long int>>ms;
    for(int i = 0; i < m; i++){
        long long int f;cin >> f;
        ms.insert({f, 1});
    }

    long long int ans = 0;
    for(int i = n - m - 1; i >= 0; i--){
        auto it = ms.begin();
        auto p = *it;
        ans += v[i]*p.first;
        p.first /= p.second;
        p.second++;
        p.first *= p.second;

        ms.erase(it);
        ms.insert(p);
    }
    printf("%lld\n", ans);
}