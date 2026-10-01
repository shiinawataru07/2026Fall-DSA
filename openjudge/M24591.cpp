#include<iostream>
#include<cctype>
#include<stack>
#include<string>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    while(n--){
        string expr;
        cin >> expr;
        int len = expr.length();
        vector<string> s;
        stack<char> op;
        for(int i = 0; i < len; ++i){
            char ch = expr[i];
            if(isdigit(ch)){
                int nextop = expr.find_first_of("+-*/()", i);
                if(nextop == string::npos) nextop = len;
                s.push_back(expr.substr(i, nextop - i));
                i = nextop - 1;
            }
            if(ch == '('){
                op.push(ch);
            }
            if(ch == ')'){
                while(!op.empty() && op.top() != '('){
                    s.push_back(string(1, op.top()));
                    op.pop();
                }
                op.pop();
            }
            if(ch == '+' || ch == '-'){
                while(!op.empty() && op.top() != '('){
                    s.push_back(string(1, op.top()));
                    op.pop();
                }
                op.push(ch);
            }
            if(ch == '*' || ch == '/'){
                while(!op.empty() && op.top() != '(' && op.top() != '+' && op.top() != '-'){
                    s.push_back(string(1, op.top()));
                    op.pop();
                }
                op.push(ch);
            }
        }
        while(!op.empty()){
            s.push_back(string(1, op.top()));
            op.pop();
        }
        for(int i = 0; i < s.size(); ++i){
            cout << s[i] << (i == s.size() - 1 ? '\n' : ' ');
        }
    }
    return 0;
}