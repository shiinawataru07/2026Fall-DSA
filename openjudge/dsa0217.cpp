#include<iostream>
#include<vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int len = 2 * n - 1;
    vector<vector<int>> mat(len, vector<int>(len, 0));
    int x = 0, y = n - 1;
    for(int num = 1; num <= len * len; num++){
        mat[x][y] = num;
        x = (x - 1 + len) % len;
        y = (y + 1) % len;
        if(mat[x][y] != 0){
            x = (x + 2) % len;
            y = (y - 1 + len) % len;
        }
    }
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            cout << mat[i][j];
            if(j != len - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}