#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long int l, r;
    cin >> n >> l >> r;

    long long int v[n];for(int i = 0; i < n; i++)cin >> v[i];
    sort(v, v + n);

    long long int ans = 0;
    bool gl = false;
    bool gr = false;
    for(int i = 0; i < n; i++){
        //printf("%lld\n", ans);
        if(v[i] >= l and !gl){
            gl = true;
            ans = abs(v[i] - l);
            if(i >= 1){
                ans = min(ans, abs(v[i - 1] - l));         
            }
            continue;
        }

        if(v[i] >= r and !gr){
            gr = true;
            if(i >= 1){
                ans = max(ans, min(abs(v[i] - r), abs(v[i - 1] - r)));
            }
            else{
                ans = max(ans, abs(v[i] - r));
            }
            break;
        }

        if(v[i] < l)continue;
        
        ans = max(ans, (v[i] - v[i - 1])/2);
    }
    if(!gr){
        if(!gl)ans = r - v[n - 1];
        else ans = max(ans, r - v[n - 1]);
    }
    printf("%lld\n", ans);
}