#include<iostream>
#include<string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string a, b;
    while(cin >> a >> b) {
        int i = 0, j = 0;
        int la = a.length(), lb = b.length();
        while(i < la && j < lb) {
            if(a[i] == b[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        if(i == la) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}