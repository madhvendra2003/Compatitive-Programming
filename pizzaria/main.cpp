#include <bits/stdc++.h>
using namespace std;

class Seg {

    public:

    vector<int>seg;
    int op ;
    int n;

    Seg()
    {

    }

    Seg(int n, int op)
    {
        this->n = n;
        this->op = op;
        seg.resize(4*n+1);
    }


    void build ( int ind , int low, int high , vector<int>& arr)
    {
        if ( low == high)
        {
            seg[ind] = arr[low];
            if (op)
            {
                seg[ind] += low;
            }
            else
            {
                seg[ind] -= low;
            }
            return ;
        }

        int mid = low + (high - low)/2;

        build ( 2*ind + 1 , low, mid , arr);

        build ( 2*ind+2,mid+1,high,arr);

        seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);
    }


    int query(int ind, int l , int r, int low, int high)
    {
        if (low > r || high < l) return INT_MAX;

        if (low >= l && high <= r) return seg[ind];

        int mid = low +(high - low)/2;

        int lft = query(2*ind+1,l,r,low,mid);
        int rgt = query(2*ind+2,l,r,mid+1,high);

        return min(lft,rgt);
    }


    void update(int ind , int i, int val, int low, int high)
    {
        if ( low == high)
        {
            seg[ind] = val;
            if (op)
            {
                seg[ind] += low;
            }
            else
            {
                seg[ind] -= low;
            }
            return ;
        }

        int mid = low + (high - low)/2;

        if ( i<= mid)
        {
            update(2*ind+1,i,val,low,mid);
        }
        else
        {
            update(2*ind+2,i,val,mid+1,high);
        }

         seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);

    }



};

int main() {
	// your code goes here

	int n,q;
	cin >> n>> q;

	vector<int>arr(n);

	for(int i=0;i<n;i++) cin >> arr[i];

	Seg up(n,1),down(n,0);

	up.build(0,0,n-1,arr);
	down.build(0,0,n-1,arr);

	while(q--)
	{
	    int a;
	    cin >> a;
	    if ( a == 1)
	    {
	        int b,c;
	        cin >> b >> c;

	        up.update(0,b-1,c,0,n-1);
	        down.update(0,b-1,c,0,n-1);

	    }

	    else
	    {
	        int b;
	        cin >> b;
	        b--;

	        cout << min ( {up.query(0,b,n-1,0,n-1)-(b),down.query(0,0,b,0,n-1)+b} )<<endl;

	    }
	}




}
