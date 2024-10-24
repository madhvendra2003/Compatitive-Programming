#include <bits/stdc++.h>

using namespace std;
int mod = 1e9 +7;
int help( int sum , int num,vector<int>&arr, vector<int>&dp)
{
    if (sum == num)
    {
        return 1;
    }
    if (sum >num)
    {
        return 0;
    }
    if (dp[sum]!=-1)return dp[sum]%mod;
    int ans =0;
    for (int i=0;i<arr.size();i++)
    {
         ans  = (ans %mod + help(sum + arr[i],num,arr,dp)%mod)%mod;
    }
    return dp[sum] = ans%mod;

}

int main()
{  vector<int> arr = {1,2,3,4,5,6};
    int n ;
    cin>>n;
    vector<int>dp(n,-1);
    cout<<help(0,n,arr,dp);

    return 0;
}
