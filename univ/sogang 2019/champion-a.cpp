#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 3e5 + 10;
int n;
int a[maxn];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    if (n == 0) {
        cout << "0";
        return 0;
    }
    for(int i=1; i<=n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    int julsa = (n * 15 + 50) / 100;
    int s = 0;
    for(int i=julsa+1; i<=n-julsa; ++i) s += a[i];
    int c = n - 2*julsa;
    int avg = (2*s + c) / (2*c);
    cout << avg << endl;
    return 0;
}
