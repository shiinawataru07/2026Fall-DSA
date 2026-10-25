#include<iostream>
#include<vector>
using namespace std;

int main() {
    int l, n, m; cin >> l >> n >> m;
    vector<int> sto(n + 2);
    sto[0] = 0; sto[n + 1] = l;
    for(int i = 1; i <= n; ++i) cin >> sto[i];
    int left = 0, right = l;
    while(left < right) {
        int mid = (left + right + 1) / 2;
        int cnt = 0;
        int lastpos = 0;
        for(int i = 1; i <= n + 1; ++i){
            if(sto[i] - lastpos < mid){
                ++cnt;
                if(cnt > m) break;
            }else{
                lastpos = sto[i];
            }
        }
        if(cnt <= m){
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    cout << left << endl;
    return 0;
}