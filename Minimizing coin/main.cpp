#include <bits/stdc++.h>
using namespace std;
int help(int sum , int amt , vector<int>&c,vector<int> &dp)
{
    if (sum == amt)return 0;
    if (dp[sum ]!=-2)return dp[sum];
    int flag =0;
    int take = INT_MAX;

    for (int i=0;i<c.size();i++)
    {
        if (sum + c[i]<=amt)
        {
            int t = help(sum + c[i],amt,c,dp);
            if (t==-1)continue;
            flag =1;
            int temp =  1 + t;
            take = min(take,temp);

        }

    }
    if (flag)
    {

        return dp[sum] = take;
    }
    return dp[sum] = -1;
}
int main()
{
    int n , x;
    cin>>n>>x;
    vector<int>c(n);
    for (int i=0;i<n;i++)
    {
        cin>>c[i];
    }
    vector<int> dp(x,-2);
     int ans = help(0,x,c,dp);
     cout<<ans<<endl;
        return 0;
}
