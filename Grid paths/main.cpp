#include <bits/stdc++.h>
int mod  = 1e9 + 7;
using namespace std;
int help(int i,int j,vector<vector<char>>&grid, vector<vector<int>>&dp )
{
    int n = grid.size();
    if (i == n-1 && j== n-1)return 1;
    if (i>n-1||j>n-1||grid[i][j]=='*')return 0;
    if (dp[i][j]!=-1)return dp[i][j];
    int lg = help(i+1,j,grid,dp)%mod;
    int rg = help(i,j+1,grid,dp)%mod;
    return dp[i][j] = (lg%mod+rg%mod)%mod;

}

int main()
{
    int n;
    cin >> n;
    vector<vector<char>> grid(n,vector<char>(n)) ;
    vector<vector<int>> dp(n,vector<int>(n,-1));
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
            cin >> grid[i][j];
    }
    if (grid[n-1][n-1]=='*')cout<<0;
    else
    cout<< help(0 , 0 , grid ,dp);
    return 0;
}
