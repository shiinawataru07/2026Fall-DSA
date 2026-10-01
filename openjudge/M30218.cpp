#include<iostream>
#include<queue>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N; cin >> N;
    deque<int> s;
    for(int i = 0; i < N; ++i) {
        int x; cin >> x;
        if(x > 0) s.push_back(x);
        if(x < 0){
            while(!s.empty() && s.back() > 0 && s.back() + x < 0){
                x += s.back();
                s.pop_back();
            }
            if(!s.empty() && s.back() > 0 && s.back() + x >= 0){
                s.back() += x;
                if(s.back() <= 0) s.pop_back();
            }else{
                s.push_back(x);
            }
        }
    }
    cout << s.size() << "\n";
    for(int i = 0; i < s.size(); ++i){
        cout << s[i];
        if(i != s.size() - 1) cout << " ";
    }
    return 0;
}