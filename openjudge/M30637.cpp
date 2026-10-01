#include<iostream>
#include<string>
#include<stack>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    string str; cin >> str;
    int len = str.length();
    string s;
    getline(cin, s);
    while(getline(cin, s)){
        if(s.empty()){
            cout << "NO" << endl;
            continue;
        }
        stack<char> st;
        int idx = 0;
        for(int i = 0; i < len; i++){
            st.push(str[i]);
            while(!st.empty() && st.top() == s[idx]){
                st.pop();
                idx++;
            }
        }
        if(idx == s.length() && st.empty()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}