#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;cin >> n;
    int v[n];for(int i = 0; i < n; i++)cin >> v[i];
    int ans = 0;
    int minA = v[0];
    int maxA = v[0];
    for(int i = 0; i < n; i++){
        minA = min(minA, v[i]);
        maxA = max(maxA, v[i]);
    }
    while(minA < maxA){
        bool continuo = false;
        for(int i = 0; i < n; i++){
            if(v[i] == minA){
                if(!continuo)ans++;
                continuo = true;
                v[i]++;
            }
            else continuo = false;
        }
        minA++;
    }
    printf("%d\n", ans);
}