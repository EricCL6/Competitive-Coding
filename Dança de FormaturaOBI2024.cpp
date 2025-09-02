#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, p;cin >> n >> m >> p;
    int l[n], c[m];
    for(int i = 0; i < n; i++)l[i] = i;
    for(int i = 0; i < m; i++)c[i] = i + 1;
    for(int i = 0; i < p; i++){
        char o;
        int a, b;
        cin >> o >> a >> b;
        a--;
        b--;
        if(o == 'L'){
            int temp = l[b];
            l[b] = l[a];
            l[a] = temp;
        }
        if(o == 'C'){
            int temp = c[b];
            c[b] = c[a];
            c[a] = temp;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", c[j] + l[i]*m);
        }
        printf("\n");
    }
}