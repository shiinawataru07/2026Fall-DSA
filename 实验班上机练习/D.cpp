#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    vector<int> L(n), R(n);
    for (int i = 0; i < n; ++i) cin >> L[i] >> R[i];
    const int SZ = 40002;
    vector<long long> c0(SZ + 1, 0), c1(SZ + 1, 0), c2(SZ + 1, 0), c3(SZ + 1, 0);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) { return L[x] > L[y]; });
    long long ans = 0;
    int p = 0;
    while (p < n) {
        int q = p, cur = L[order[p]];
        while (q < n && L[order[q]] == cur) ++q;
        for (int t = p; t < q; ++t) {
            int i = order[t];
            long long li = L[i], ri = R[i];
            long long s0 = 0, s1 = 0, s2 = 0, s3 = 0;
            for (int x = R[i]; x > 0; x -= x & -x) {
                s0 += c0[x]; s1 += c1[x]; s2 += c2[x]; s3 += c3[x];
            }
            ans += ri * s1 - s3 - li * ri * s0 + li * s2;
        }
        for (int t = p; t < q; ++t) {
            int i = order[t];
            long long li = L[i], ri = R[i], lr = li * ri;
            for (int x = R[i] + 1; x <= SZ; x += x & -x) {
                c0[x] += 1; c1[x] += li; c2[x] += ri; c3[x] += lr;
            }
        }
        p = q;
    }
    cout << ans << '\n';
    return 0;
}