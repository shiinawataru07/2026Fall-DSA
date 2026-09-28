#include<iostream>
#include<map>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    while(n--){
        int x, y;
        map<int, int, greater<int>> mp;
        for(int i = 0; i < 2; i++){
            while(cin >> x >> y){
                if(y < 0) break;
                mp[y] += x;
            }
        }
        for(auto it = mp.begin(); it != mp.end(); it++){
            if(it->second == 0) continue;
            cout << "[ " << it->second << " " << it->first << " ]";
            if(next(it) != mp.end()) cout << " ";
        }
        cout << endl;
    }
    return 0;
}