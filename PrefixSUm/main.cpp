#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Node {
public:
    ll Sum;
    ll maxSum;

    Node(ll Sum, ll maxSum) {
        this->Sum = Sum;
        this->maxSum = maxSum;
    }

    Node() {
        Sum = maxSum = 0LL;
    }
};

void build(int ind, int low, int high, vector<int>& arr, vector<Node>& seg) {
    if (low == high) {
        Node temp((ll)arr[low], (ll)arr[low]);
        seg[ind] = temp;
        return;
    }

    int mid = low + (high - low) / 2;
    build(2 * ind + 1, low, mid, arr, seg);
    build(2 * ind + 2, mid + 1, high, arr, seg);

    ll tsum = seg[2 * ind + 1].Sum + seg[2 * ind + 2].Sum;
    seg[ind].maxSum = max({
        seg[2 * ind + 1].maxSum,
        seg[2 * ind + 1].Sum + seg[2 * ind + 2].maxSum
    });
    seg[ind].Sum = tsum;
}

Node get(int ind, int l, int r, int low, int high, vector<Node>& seg) {
    if (low > r || high < l) {
        Node temp(0LL, 0LL);
        return temp;
    }

    if (low >= l && high <= r) return seg[ind];

    int mid = low + (high - low) / 2;
    Node lft = get(2 * ind + 1, l, r, low, mid, seg);
    Node rgt = get(2 * ind + 2, l, r, mid + 1, high, seg);

    Node temp(0LL, 0LL);
    temp.Sum = lft.Sum + rgt.Sum;
    temp.maxSum = max(lft.maxSum, lft.Sum + rgt.maxSum);
    return temp;
}

void update(int ind, int i, ll val, int low, int high, vector<Node>& seg) {
    if (low == high) {
        Node temp(val, val);
        seg[ind] = temp;
        return;
    }

    int mid = low + (high - low) / 2;
    if (i <= mid) {
        update(2 * ind + 1, i, val, low, mid, seg);
    } else {
        update(2 * ind + 2, i, val, mid + 1, high, seg);
    }

    ll tsum = seg[2 * ind + 1].Sum + seg[2 * ind + 2].Sum;
    seg[ind].maxSum = max({
        seg[2 * ind + 1].maxSum,
        seg[2 * ind + 1].Sum + seg[2 * ind + 2].maxSum
    });
    seg[ind].Sum = tsum;
}

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    vector<Node> seg(4 * n + 1);
    build(0, 0, n - 1, arr, seg);

    while(q--) {
        int a, b;
        ll c;
        cin >> a >> b >> c;

        if(a == 1) {
            update(0, b - 1, c, 0, n - 1, seg);
        } else {
            cout <<max( get(0, b - 1, c - 1, 0, n - 1, seg).maxSum ,0LL)<< endl;
        }
    }
    return 0;
}
