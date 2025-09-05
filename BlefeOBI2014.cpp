#include<bits/stdc++.h>
using namespace std;

struct seq{
    vector<int>v;
    unordered_set<int>s;
};

int main()
{
    int n, m;cin >> n >> m;
    seq a, b;
    for(int i = 0; i < n; i++){
        int cur;cin >> cur;
        a.s.insert(cur);
    }
    bool ans;
    for(int i = 0; i < m; i++){
        ans = false;
        int cur;cin >> cur;

        if(a.s.find(cur) != a.s.end())ans = true;

        for(auto u : b.v){
            if(b.s.find(cur - u) != b.s.end()){
                ans = true;
                break;
            }
        }
        if(!ans){
            printf("%d\n", cur);
            break;
        }
        b.v.push_back(cur);
        b.s.insert(cur);
    }
    if(ans)printf("sim\n");
}