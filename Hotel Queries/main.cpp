#include <bits/stdc++.h>
using namespace std;
void build (int ind , int low, int high , vector<int>&arr , vector<int>&seg)
{
    if ( low  == high)
    {
        seg[ind] = arr[low];
        return ;
    }

    int mid = low + (high - low) / 2;

    build ( 2 * ind  + 1, low , mid , arr,seg);
    build ( 2 * ind  + 2 , mid + 1, high , arr,seg);

    seg[ind] = max ( seg[2*ind + 1], seg[2* ind + 2]);
}

void get (int ind , int low, int high , int val , vector<int> & seg , int& ans)
{
     if ( val > seg[ind]) return ;

    if ( low == high)
    {
        ans = low ;
        seg[ind] -= val;
        return ;
    }



    int mid  = low + (high - low) / 2;

    if ( val <= seg[2*ind + 1])
    {
        get(2*ind+1,low,mid,val,seg,ans);
    }
    else
    {
        get(2*ind+2,mid+1,high,val,seg,ans);
    }

    seg[ind] = max( seg[2*ind+1] , seg[2*ind+2]);
}

int main() {

	int n ,m;

	cin >> n >> m;


	vector<int>arr(n);
	for(int i=0;i<n;i++) cin >> arr[i];

	vector<int> seg(5*n,-1);

	build(0,0,n-1,arr,seg);


	while ( m -- )
	{
	    int ans  = -1;
	    int hm;
	     cin >> hm;

	     get(0,0,n-1,hm,seg ,ans);
	     cout << ++ans<<endl;
	}





}
