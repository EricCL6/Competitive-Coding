#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;cin >> n;
    int a0 = 0, a1 = 0, a2 = 0, a3 = 8;
    if(n > 2){
        a0 = (n-2)*(n-2)*(n-2);
        a1 = (n-2)*(n-2)*6;
        a2 = (n-2)*12;
    }
    printf("%d\n%d\n%d\n%d\n", a0, a1, a2, a3);
}