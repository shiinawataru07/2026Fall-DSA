#include <iostream>
#include <algorithm>
using namespace std;

int arr[200001];
int ord[200001];
int ans[200001];
int steps[200001];
int heapArr[200001];

int n;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ord[i] = i;
    }
    bool flg = false;
    for (int i = 0; i < n; i++) {
        cin >> steps[i];
        int idx = i;
        for (int j = 0; j < steps[i]; j++) {
            if (idx == 0) {
                flg = true;
                break;
            }
            int parent = (idx - 1) / 2;
            swap(ord[idx], ord[parent]);
            idx = parent;
        }
    }
    if (flg) {
        cout << "NO\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        ans[ord[i]] = arr[i];
    }
    int heapSize = 0;
    for (int i = 0; i < n; i++) {
        heapArr[heapSize] = ans[i];
        int idx = heapSize;
        int cnt = 0;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (heapArr[parent] < heapArr[idx]) {
                break;
            }
            swap(heapArr[parent], heapArr[idx]);
            idx = parent;
            cnt++;
        }
        if (cnt != steps[i]) {
            cout << "NO\n";
            return 0;
        }
        heapSize++;
    }
    for (int i = 0; i < n; i++) {
        if (heapArr[i] != arr[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << ans[i];
        if (i != n - 1) cout << " ";
    }
    cout << "\n";
    return 0;
}