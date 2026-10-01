#include<iostream>
#include<vector>
using namespace std;

long long cnt = 0;
void mergesort(vector<int>& a, int l, int r) {
    if (l >= r) return;
    int mid = (l + r) / 2;
    mergesort(a, l, mid);
    mergesort(a, mid + 1, r);
    vector<int> temp(r - l + 1);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else{
            temp[k++] = a[j++];
            cnt += mid - i + 1;
        }
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];
    for (int i = 0; i < k; i++) a[l + i] = temp[i];
}

int main() {
    int n;
    while(cin >> n) {
        if (n == 0) break;
        vector<int> a(n);
        cnt = 0;
        for (int i = 0; i < n; i++) cin >> a[i];
        mergesort(a, 0, n - 1);
        cout << cnt << endl;
    }
}