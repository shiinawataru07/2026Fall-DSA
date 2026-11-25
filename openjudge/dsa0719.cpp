
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main() {
    int v, a;
    cin >> v >> a;

    vector<vector<int>> graph(v + 1);
    vector<int> indegree(v + 1, 0);

    for (int i = 0; i < a; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        indegree[y]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 1; i <= v; i++) {
        if (indegree[i] == 0) pq.push(i);
    }

    bool first = true;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        if (!first) cout << " ";
        cout << "v" << u;
        first = false;

        for (int w : graph[u]) {
            indegree[w]--;
            if (indegree[w] == 0) {
                pq.push(w);
            }
        }
    }

    cout << '\n';
    return 0;
}
