#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, amt;
    cin >> n >> amt;
    vector<int> coins(n);

    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    vector<int> dp(amt + 1, 0);
    dp[0] = 1;

    for (int i=1;i<=amt;i++)
    {
        for (auto &it : coins)
        {

            if (i>=it)
            {
                dp[i] = (dp[i] + dp[i-it])%MOD;
            }
        }
    }

    cout << dp[amt] << endl;
    return 0;
}
