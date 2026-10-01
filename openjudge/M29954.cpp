#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;

struct Node{
    int x, y, step, used;
};
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int main(){
    int r, c, k;
    cin >> r >> c >> k;
    vector<vector<char>> matrix(r, vector<char>(c));
    vector<vector<vector<bool>>> visited(r, vector<vector<bool>>(c, vector<bool>(k + 1, false)));
    queue<Node> q;
    for(int i = 0; i < r; i++){
        string str;
        cin >> str;
        for(int j = 0; j < c; j++){
            matrix[i][j] = str[j];
            if(matrix[i][j] == 'S'){
                q.push({i, j, 0, 0});
            }
        }
    }
    while(!q.empty()){
        Node node = q.front();
        q.pop();
        if(visited[node.x][node.y][node.used]) continue;
        visited[node.x][node.y][node.used] = true;
        if(matrix[node.x][node.y] == 'E'){
            cout << node.step << endl;
            return 0;
        }
        for(int i = 0; i < 4; i++){
            int nx = node.x + dx[i];
            int ny = node.y + dy[i];
            if(nx >= 0 && nx < r && ny >= 0 && ny < c){
                if(matrix[nx][ny] == '.' || matrix[nx][ny] == 'E'){
                    q.push({nx, ny, node.step + 1, node.used});
                }else if(matrix[nx][ny] == '#' && node.used < k){
                    q.push({nx, ny, node.step + 1, node.used + 1});
                }
            }
        }
    }
    cout << -1 << endl;
    return 0;
}