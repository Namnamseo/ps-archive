#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }

#define pb push_back
#define all(x) (x).begin(),(x).end()

typedef pair<ll,ll> pp;
pp operator-(pp a, pp b){ return make_pair(a.first-b.first, a.second-b.second); }
ll cross(pp a, pp b){ return a.first*b.second - a.second*b.first; }

typedef vector<pp> vec;
pair<vec,vec> convex_hull(vec p){
    auto ccw = [](pp a, pp b, pp c) -> bool {
        return cross(b-a, c-a) <= 0;
    };
    vector<pp> uh, dh;
    sort(all(p));
{
    vector<int> hull;
    int n = p.size(), top=0;
    for(int i=0; i<n; ++i){
        while(top >= 2 && ccw(p[hull[top-2]], p[hull[top-1]], p[i])) hull.pop_back(), --top;
        hull.pb(i); ++top;
    }
    for(int x:hull) uh.pb(p[x]);
}
{
    vector<int> hull;
    int n = p.size(), top=0;
    for(int i=n-1; i>=0; --i){
        while(top >= 2 && ccw(p[hull[top-2]], p[hull[top-1]], p[i])) hull.pop_back(), --top;
        hull.pb(i); ++top;
    }
    for(int x:hull) dh.pb(p[x]);
}
    return make_pair(uh, dh);
}

ll ans;
ll sqr(ll x){ return x*x; }
void yield(pp a, pp b){ ans = max(ans, sqr(a.first-b.first)+sqr(a.second-b.second)); }

ll furthest_point(vec v){
    vec uh, dh;
    tie(uh, dh) = convex_hull(v);
    int n=uh.size();
    int m=dh.size();
    int i=0, j=0;
    ans=0;  
    while(i!=n-1 || j!=m-1){
        yield(uh[i], dh[j]);
        if(i == n-1) ++j;
        else if(j == m-1) ++i;
        else {
            if(cross(uh[i+1]-uh[i], dh[j+1]-dh[j]) <= 0) ++i;
            else ++j;
        }
    }
    return ans;
}

int n;
vec x, v;

ll test(int t){
    vec a(n);
    for(int i=0; i<n; ++i){
        a[i] = make_pair(x[i].first + t*v[i].first,
                         x[i].second+ t*v[i].second);
    }
    return furthest_point(a);
}

int main()
{
    int t;
    read(n, t);
    x.resize(n); v.resize(n);
    for(int i=0; i<n; ++i){
        read(x[i].first, x[i].second);
        read(v[i].first, v[i].second);
    }
    int l=0, r=t;
    while(l+3<r){
        int p1=(l*2+r)/3;
        int p2=(l+r*2)/3;
        ll v1=test(p1);
        ll v2=test(p2);
        if(v1>v2) l=p1;
        else r=p2;
    }
    ll ans=1LL<<60;
    int ant=-1;
    for(int i=l; i<=r; ++i){
        ll t=test(i);
        if(ans > t) ans=t, ant=i;
    }
    printf("%d\n%lld\n", ant, ans);
    return 0;
}
