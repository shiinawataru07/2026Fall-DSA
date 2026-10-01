#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    vector<int> minans;
    vector<int> maxans;
    deque<int> mindq;
    deque<int> maxdq;
    for(int i = 0; i < n; i++) cin >> arr[i];
    for(int i = 0; i < n; i++){
        while(!mindq.empty() && arr[mindq.back()] >= arr[i]) mindq.pop_back();
        mindq.push_back(i);
        while(!maxdq.empty() && arr[maxdq.back()] <= arr[i]) maxdq.pop_back();
        maxdq.push_back(i);
        if(!mindq.empty() && mindq.front() <= i - k) mindq.pop_front();
        if(!maxdq.empty() && maxdq.front() <= i - k) maxdq.pop_front();
        if(i >= k - 1){
            minans.push_back(arr[mindq.front()]);
            maxans.push_back(arr[maxdq.front()]);
        }
    }
    for(int i = 0; i < minans.size(); i++){
        cout << minans[i];
        if(i != minans.size() - 1) cout << " ";
    }
    cout << "\n";
    for(int i = 0; i < maxans.size(); i++){
        cout << maxans[i];
        if(i != maxans.size() - 1) cout << " ";
    }
    cout << "\n";
    return 0;
}