#include<iostream>
using namespace std;
long long c[20];

int main(){
    int n; cin >> n;
    c[0] = 1;
    for(int i = 1; i <= n; i++) c[i] = c[i - 1] * 2 * (2LL * i - 1) / (i + 1);
    cout << c[n] << endl;
    return 0;
}