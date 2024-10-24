#include <bits/stdc++.h>
#define ll long long
using namespace std;

// Segment tree with lazy propagation for range updates
class SegTree {
    int n;
    vector<ll> seg, lazy;

public:
    SegTree(int size) {
        n = size;
        seg.resize(4 * n + 1);
        lazy.resize(4 * n + 1);
    }

    void build(int ind, int low, int high, vector<int>& arr) {
        if (low == high) {
            seg[ind] = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    void propagate(int ind, int low, int high) {
        if (lazy[ind] != 0) {
            seg[ind] += (high - low + 1) * lazy[ind];

            if (low != high) {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }

            lazy[ind] = 0;
        }
    }

    void rangeUpdate(int ind, int low, int high, int l, int r, ll val) {
        propagate(ind, low, high);

        if (low > r || high < l) return;

        if (low >= l && high <= r) {
            seg[ind] += (high - low + 1) * val;
            if (low != high) {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }

        int mid = (low + high) >> 1;
        rangeUpdate(2 * ind + 1, low, mid, l, r, val);
        rangeUpdate(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    ll pointQuery(int ind, int low, int high, int pos) {
        propagate(ind, low, high);

        if (low == high) return seg[ind];

        int mid = (low + high) >> 1;
        if (pos <= mid)
            return pointQuery(2 * ind + 1, low, mid, pos);
        else
            return pointQuery(2 * ind + 2, mid + 1, high, pos);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    SegTree seg(n);
    seg.build(0, 0, n - 1, arr);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int a, b, u;
            cin >> a >> b >> u;
            a--; b--;  // Convert to 0-based indexing
            seg.rangeUpdate(0, 0, n - 1, a, b, u);
        } else {
            int k;
            cin >> k;
            k--;  // Convert to 0-based indexing
            cout << seg.pointQuery(0, 0, n - 1, k) << '\n';
        }
    }

    return 0;
}
