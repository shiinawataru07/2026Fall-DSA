#include<iostream>
#include<vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int left = 0, right = 10000;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        long long count = 0;
        for (int i = 0; i < n; ++i) {
            count += a[i] / mid;
        }
        if (count >= k) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }
    cout << left << endl;
    return 0;
}