#include<iostream>
using namespace std;

int main(){
    int n = 0;
    cin >> n;
    unsigned long long t[31];
    t[0] = 0;
    t[1] = 1;
    t[2] = 1;
    for(int i=3; i<=n; i++){
        t[i] = t[i-1] + t[i-2] + t[i-3];
    }
    cout << t[n] << endl;
}