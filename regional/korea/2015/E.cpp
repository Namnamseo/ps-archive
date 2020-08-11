#include <bits/stdc++.h>
using namespace std;

void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args> void read(T& a,Args&... b){ read(a); read(b...); }

int n;
int h[10010];

bool dekiru(int D){
    multiset<int> ms;
    for(int i=2; i<=n; ++i) ms.insert(h[i]);
    for(int i=0; i<2; ++i){
        int x = h[1];
        while(x < h[n]){
            auto it = ms.upper_bound(x + D);
            if(it == ms.begin()) return false;
            --it;
            if(*it == h[n]) break;
            x = *it;
            ms.erase(it);
        }
    }
    return true;
}

int main()
{
    int t; read(t); for(;t--;){
        read(n);
        for(int i=1; i<=n; ++i) read(h[i]);
        sort(h+1, h+n+1);
        int l=-1, r=100010;
        while(l+1 < r){
            int mid=(l+r)/2;
            if(dekiru(mid)){
                r=mid;
            } else l=mid;
        }
        printf("%d\n", r);
    }
    return 0;
}

