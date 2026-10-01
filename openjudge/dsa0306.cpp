#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    bool ok = true;
    stack<int> s;
    vector<int> arr(n);
    vector<string> ans;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        if(arr[i] < 0 || arr[i] > n) ok = false;
    }
    int idx = 0;
    for(int i = 1; i <= n; i++){
        s.push(i);
        ans.push_back("PUSH " + to_string(i));
        while(!s.empty() && idx < n && s.top() == arr[idx]){
            s.pop();
            ans.push_back("POP " + to_string(arr[idx]));
            idx++;
        }
        if (!s.empty() && s.top() > arr[idx]) {
            ok = false;
            break;
        }
    }
    if(ok && s.empty()){
        for(auto &str : ans){
            cout << str << "\n";
        }
    } else {
        cout << "NO\n";
    }
    return 0;
}