#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(),(x).end()

const int M = int(1e9) + 7;
typedef long long ll;

int n;
char arr[4][2010];

int comb[6001][6001];

typedef pair<int,int> pp;
vector<pp> dummy;

ll dp[2010][6010][2];
ll pdp[2010][6010][2];
int fact[6];

void workGugan(int l,int r){
    int cnt=0;

    // first column
    for(int i=1; i<=3; ++i) cnt+=!arr[i][l];
    if(cnt == 1){
        dp[l][1][0]=1;
    } else if(cnt == 2){
        dp[l][1][1]=1;
        dp[l][2][0]=1;
    } else {
        dp[l][1][1]=2;
        dp[l][2][1]=2;
        dp[l][3][0]=2;
    }

    for(int i=l, j=1; j<=cnt; ++j){
        pdp[i][j][0] = (pdp[i][j-1][0] + dp[i][j][0]) % M;
        pdp[i][j][1] = (pdp[i][j-1][1] + dp[i][j][1]) % M;
    }

    for(int i=l+1; i<=r; ++i){
        int cc=0;
        for(int j=1; j<=3; ++j) cc+=!arr[j][i];
        cnt += cc;

        for(int j=1; j<=cnt; ++j){
            if(j >= cc){
                dp[i][j][0] += comb[j-1][cc-1]*pdp[i-1][cnt-cc][0]%M*fact[cc-1]%M;
                dp[i][j][0] %= M;

                dp[i][j][0] += comb[j-1][cc-1]*(pdp[i-1][cnt-cc][1]-pdp[i-1][j-cc][1]+M)%M*fact[cc-1]%M;
                dp[i][j][0] %= M;
            }

            for(int f=0; f<cc-1; ++f){
                dp[i][j][1] +=
                    comb[j-1][f]
                    * comb[cnt-j][cc-f-1] % M
                    * pdp[i-1][j-1-f][0]  % M
                    * fact[cc-1] % M;
                dp[i][j][1] %= M;
            }

            pdp[i][j][0] = (pdp[i][j-1][0] + dp[i][j][0]) % M;
            pdp[i][j][1] = (pdp[i][j-1][1] + dp[i][j][1]) % M;
        }
    }

    ll ans = pdp[r][cnt][0];
    if(arr[2][r+1])
        ans += pdp[r][cnt][1], ans %= M;

    dummy.pb({ans, cnt});
}

int main()
{
    // input
    cin >> n;
    for(int i=1; i<=3; ++i){
        cin >> (arr[i]+1);
        for(int j=1; j<=n; ++j){
            arr[i][j] = (arr[i][j] == 'o');
        }
    }

    // build comb & fact
    fact[0]=1;
    for(int i=1; i<=5; ++i) fact[i]=i*fact[i-1];
    for(int i=0; i<=6000; ++i){
        comb[i][0] = comb[i][i]=1;
        for(int j=1; j<i; ++j) comb[i][j] = (comb[i-1][j-1]+comb[i-1][j])%M;
    }

    // check unable
    if(!arr[1][1] || !arr[1][n] || !arr[3][1] || !arr[3][n]){
        cout << 0;
        return 0;
    }
    for(int i=1; i<=3; i+=2) for(int j=1; j<n; ++j)
    if(!arr[i][j] && !arr[i][j+1]){
        cout << 0;
        return 0;
    }

    // fill in non-2 columns
    for(int i=1; i<=n; ++i) if(arr[2][i]){
        if(!arr[1][i]) dummy.pb({1, 1});
        if(!arr[3][i]) dummy.pb({1, 1});
    }

    // for each group:
    int last_off = -1;
    for(int i=1; i<=n; ++i){
        if(!arr[2][i]){
            if(last_off == -1) last_off = i;
        } else {
            if(last_off != -1) workGugan(last_off, i-1);
            last_off = -1;
        }
    }
    if(last_off != -1){
        workGugan(last_off, n);
    }

    ll ans=1;
    int sz=0;
    for(pp a:dummy){
        ans=(ans*a.first)%M;
        sz+=a.second;
    }

    for(pp a:dummy){
        ans=(ans*comb[sz][a.second])%M;
        sz-=a.second;
    }

    cout << ans;
    return 0;
}
