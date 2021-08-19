typedef long long ll;

ll dl[10000010];
ll dr[10000010];

int l;

ll min(ll a,ll b){ return a>b?b:a; }

int f(int x){
    return min(x, l-x);
}

long long delivery(int n, int k, int l_, int pos[])
{
    l=l_;
    int i;
    for(i=0; i<k; ++i) dl[i]=pos[i] + f(pos[i]);
    for(i=k; i<n; ++i) dl[i]=dl[i-k] + pos[i] + f(pos[i]);
    for(i=0; i<k; ++i) dr[n-1-i]=l-pos[n-1-i] + f(pos[n-1-i]);
    for(i=k; i<n; ++i) dr[n-1-i]=dr[n-1-i+k] + l-pos[n-1-i] + f(pos[n-1-i]);
    ll ans=min(dl[n-1], dr[0]);
    for(i=0; i+1<n; ++i){
        ans=min(ans, dl[i]+dr[i+1]);
    }
    return ans;
}
