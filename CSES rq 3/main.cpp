#include <bits/stdc++.h>
#define ll long long
using namespace std;
void build (int ind , int low , int high , vector<int>&arr , vector<ll>&seg)
{

    if ( low == high)
    {
        seg[ind] = (ll)arr[low];
        return ;
    }

    int mid = low + (high - low) / 2;

    build ( 2* ind + 1, low,mid,arr,seg);
    build(2*ind+2,mid+1,high,arr,seg);

    seg[ind] = seg[2*ind+1]+seg[2*ind+2];


}

void update(int low,int high, int ind , int i , int val,vector<ll>&seg)
{

    if ( low == high)
    {
        seg[ind] = (ll)val;
        return ;
    }

    int mid  = low + (high - low) / 2;

    if ( i<=mid)
    {
        update(low,mid,2*ind+1,i,val,seg);
    }
    else{
        update(mid+1,high,2*ind+2,i,val,seg);
    }

    seg[ind] = seg[2*ind+1] + seg[2 * ind + 2];


}

ll query(int ind , int l , int r, int low , int high , vector<ll>&seg)
{
    if ( l > high || r < low)
    {
        return 0;
    }

    if ( low>=l && high<= r)
    {
        return seg[ind];

    }

    int mid = low + (high-low)/2;

    ll lft = query(2*ind+1,l,r,low,mid,seg);
    ll rgt = query(2*ind+2,l,r,mid+1,high,seg);

    return lft + rgt;

}


int main()
{
    int n ,q ;
    cin  >> n >> q;

    vector<int> arr(n);
    vector<ll> seg(4*n+1);

    for(int i=0;i<n;i++) cin >> arr[i];

    build(0,0,n-1,arr,seg);

    while ( q--)
    {
        int a, b, c;

        cin >> a>>b>>c;
        if ( a == 1)
        {

            update(0,n-1,0,b-1,c,seg);

        }else{
            cout<<query(0,b-1,c-1,0,n-1,seg)<<endl;
        }

    }
    return 0;
}
