#include<iostream>
#include<cctype>
#include<stack>
#include<string>
#include<vector>
using namespace std;

int s2i(string s){
    int res = 0;
    for(int i = 0; i < s.length(); ++i){
        res = res * 10 + (s[i] - '0');
    }
    return res;
}

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
        stack<int> stk;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == "+"){
                int a = stk.top(); stk.pop();
                int b = stk.top(); stk.pop();
                stk.push(b + a);
            }
            else if(s[i] == "-"){
                int a = stk.top(); stk.pop();
                int b = stk.top(); stk.pop();
                stk.push(b - a);
            }
            else if(s[i] == "*"){
                int a = stk.top(); stk.pop();
                int b = stk.top(); stk.pop();
                stk.push(b * a);
            }
            else if(s[i] == "/"){
                int a = stk.top(); stk.pop();
                int b = stk.top(); stk.pop();
                stk.push(b / a);
            }
            else{
                stk.push(s2i(s[i]));
            }
        }
        cout << stk.top() << '\n';
    }
    return 0;
}