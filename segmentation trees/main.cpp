#include <bits/stdc++.h>
using namespace std;

void build(int ind, int low, int high, int arr[], vector<int>&seg) {
    if (low == high) {
        seg[ind] = arr[low];
        return;
    }

    int mid = low + (high - low) / 2;  // Changed calculation to avoid potential overflow

    build(2 * ind + 1, low, mid, arr, seg);
    build(2 * ind + 2, mid + 1, high, arr, seg);

    seg[ind] = (seg[2 * ind + 1]+seg[2 * ind + 2]);
}

int query(int ind, int low, int high, int l, int r, vector<int>&seg) {
    // No overlap
    if (r < low || high < l) {
        return INT_MAX;
    }

    // Complete overlap
    if (low >= l && high <= r) {
        return seg[ind];
    }

    // Partial overlap
    int mid = low + (high - low) / 2;

    int left = query(2 * ind + 1, low, mid, l, r, seg);
    int right = query(2 * ind + 2, mid + 1, high, l, r, seg);

    return left + right;
}

void update ( int ind, int i , int val  , int high , int low,vector<int>&seg)
{

    if ( low == high)
    {
        seg[ind] = val;
        return;
    }

    int mid = (low + high)/2;

    if (i <=mid)
    {
        update(2*ind + 1 , i , val,mid,low,seg);

    }
    else{
        update(2*ind+2 , i, val, high , mid+1,seg);

    }

    seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);


}

int main() {
    int n;
    cin >> n;

    int q;
    cin >> q;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<int> seg(4 * n);
    build(0, 0, n - 1, arr, seg);

    while (q--)
    {
        int c ;
        cin >> c;
        if(c == 1)
        {
            int i , val;
            cin >> i>> val;
            update(0,i-1,val,n-1,0,seg);

        }
        else{
            int l,r;
            cin >> l>> r;
            cout<< query(0,0,n-1,l,r,seg);
        }



    }



    return 0;
}
