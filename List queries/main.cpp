#include <bits/stdc++.h>
using namespace std;
void build (int ind , int low, int high , vector<int>&arr , vector<int>&seg)
{
    if ( low  == high)
    {
        seg[ind] = 1;
        return ;
    }

    int mid = low + (high - low) / 2;

    build ( 2 * ind  + 1, low , mid , arr,seg);
    build ( 2 * ind  + 2 , mid + 1, high , arr,seg);

    seg[ind] =   seg[2*ind + 1] + seg[2* ind + 2] ;
}

void get(int pos , int low, int high,int ind, vector<int>&seg , vector<int> & arr, int & ans)
{
    if ( pos > seg[ind])
    {
        return ;
    }

    if ( low == high)
    {
        ans = arr[low];
        seg[ind] = 0;
        return ;
    }


    int mid = low + (high - low)/2;

    if ( seg[2*ind+1] >= pos)
    {
        get(pos,low,mid,2*ind+1,seg,arr,ans);
    }
    else
    {
        get(pos-seg[2*ind+1],mid+1,high,2*ind+2,seg,arr,ans);
    }

    seg[ind] = seg[2*ind+1] + seg[2 * ind + 2];



}



int main() {

	int n ;

	cin >> n;


	vector<int>arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	vector<int> seg(5*n,-1);

	build(0,0,n-1,arr,seg);

	int m = n;
	while ( m-- )
	{
	    int ans  = -1;
	    int hm;
	     cin >> hm;

	     get(hm,0,n-1,0,seg,arr ,ans);
	     cout << ans<<endl;
	}





}
