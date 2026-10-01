#include<iostream>
#include<cstring>
#include<unordered_map>

using namespace std;

int main(){
    string s;
    getline(cin, s);
    unordered_map<char, int> m;
    int leftpos = 0;
    int res = 0;
    for(int i = 0; i < s.size(); i++){
        leftpos = max(leftpos, m[s[i]]);
        res = max(res, i - leftpos + 1);
        m[s[i]] = i + 1;
    }
    cout << res << endl;
    return 0;
}