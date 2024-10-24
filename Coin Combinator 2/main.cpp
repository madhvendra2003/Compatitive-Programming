#include <bits/stdc++.h>

using namespace std;
int mod = 1e9 +7;
int main()
{
    // initiated
    int n , amt ;
    cin>>n>>amt;
    vector<int>arr(n);
    for(int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    // solution
    sort (arr.begin(),arr.end());
    vector<int>dp(amt+1,0);
    // base cases
    dp[amt ]=1;

     // general case
    for (int i=1;i<=n;i++)
    {
        for (int sum =amt-arr[i-1];sum >=0;sum --)
        { if (sum + arr[i-1] <= amt)
               {
                 dp[sum]= (dp[sum]%mod + dp[sum+arr[i-1]]%mod)%mod;
                }
       }
    }
     //ans
    cout<< dp[0]%mod;

    return 0;
}
