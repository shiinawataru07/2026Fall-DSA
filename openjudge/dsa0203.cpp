#include<iostream>
#include<string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string line;
    while(getline(cin, line)) {
        int splitIndex = line.find(' ');
        string str = line.substr(0, splitIndex);
        string substr = line.substr(splitIndex + 1);
        int maxIndex = -1;
        int maxAscii = -1;
        for(int i = 0; i < str.length(); ++i) {
            if(str[i] > maxAscii) {
                maxAscii = str[i];
                maxIndex = i;
            }
        }
        cout << str.substr(0, maxIndex + 1) + substr + str.substr(maxIndex + 1) << endl;
    }
    return 0;
}