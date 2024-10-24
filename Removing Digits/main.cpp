#include <bits/stdc++.h>

using namespace std;


int main()
{
    int n;
    cin >> n;
    int cnt =0;
    while (n!=0)
    {
        int temp = n;
        int c =0;
        while (temp!=0)
        {
            c = max(c,temp%10);
            temp = temp/10;
        }
        n = n - c;
        cnt++;

    }
    cout<<cnt<<endl;
    return 0;
}
