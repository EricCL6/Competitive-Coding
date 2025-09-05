#include<bits/stdc++.h>
using namespace std;

struct interval{
    long long int sum = 0;
    int quant = 0;
    vector<long long int> vec = {0};
};

int main()
{
    int n, m;cin >> n >> m;

    int sq = sqrt(n) + 1;
    
    vector<interval> ida;
    vector<interval> volta;
    for(int i = 0; i < n; i += sq){
        interval aux;
        if(i + sq >= n){
            vector<long long int>v(n - i, 0);
            aux.vec.swap(v);
        }
        else{
            vector<long long int>v(sq, 0);
            aux.vec.swap(v);
        }
        ida.push_back(aux);
        volta.push_back(aux);
    }

    for(int i = 0; i < m; i++){
        int o, pos;cin >> o >> pos;
        /*for(auto u : ida){
            printf("%lld %d\n", u.sum, u.quant);
            for(auto j : u.vec)printf("%lld ", j);
            printf("\n");
        }
        for(auto u : volta){
            printf("%lld %d\n", u.sum, u.quant);
            for(auto j : u.vec)printf("%lld ", j);
            printf("\n");
        }*/
        if(o == 1){
            pos--;
            int val;cin >> val;
            int id = pos/sq;
            for(int j = pos - id*sq; j < ida[id].vec.size(); j++){
                if(val == 0)break;
                ida[id].vec[j] += val;
                val--;
            }
            id++;
            while(val >= sq and id < ida.size()){
                ida[id].sum += val;
                ida[id].quant++;

                val -= sq;
                id++;
            }
            if(id == ida.size())continue;
            for(int j = 0; val > 0 and j < ida[id].vec.size(); j++){
                ida[id].vec[j] += val;
                val--;
            }
        }
        if(o == 2){
            pos = n - pos;
            int val;cin >> val;
            int id = pos/sq;
            for(int j = pos - id*sq; j < volta[id].vec.size(); j++){
                if(val == 0)break;
                volta[id].vec[j] += val;
                val--;
            }
            id++;
            while(val >= sq and id < volta.size()){
                volta[id].sum += val;
                volta[id].quant++;

                val -= sq;
                id++;
            }
            if(id == volta.size())continue;
            for(int j = 0; val > 0 and j < volta[id].vec.size(); j++){
                volta[id].vec[j] += val;
                val--;
            }
        }
        if(o == 3){
            long long int ans = 0;

            pos--;
            int id = pos/sq;
            int j = pos - id*sq;
            ans += ida[id].sum;
            ans -= ida[id].quant * j;
            ans += ida[id].vec[j];

            pos = n - pos - 1;
            id = pos/sq;
            j = pos - id*sq;
            ans += volta[id].sum;
            ans -= volta[id].quant * j;
            ans += volta[id].vec[j];

            printf("%lld\n", ans);
        }
    }
}