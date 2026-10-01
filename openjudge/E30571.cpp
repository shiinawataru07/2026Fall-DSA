#include<iostream>
#include<cmath>
using namespace std;

int bits[64];
int getbits(int n){
    int maxbit = 0;
    for(int i=0; i<64; i++){
        if(n & 1 == 1){
            bits[i] = 1;
            maxbit = i;
        }
        else{
            bits[i] = 0;
        }
        n >>= 1;
    }
    return maxbit;
}

int main(){
    int n;
    cin >> n;
    int maxbit = getbits(n);
    for(int i=0; i<64; i++){
        bits[i] = 1 - bits[i];
    }
    unsigned long long res = 0;
    for(int i=0; i<=maxbit; i++){
        res += bits[i] * pow(2, i);
    }
    cout << res << endl;
}