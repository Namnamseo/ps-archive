#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
typedef pair<ll,ll> pll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define x first
#define y second

const int max_n = 1000010;
const ll mod=1e9+7;

int n;
pp pt[max_n];

void in(){
    read(n);
    for(int i=1; i<=n; ++i) read(pt[i].x, pt[i].y);
}

void mosun(){
    puts("0");
    exit(0);
}

struct UF {
    int par[max_n];
    int ene[max_n];
    void init(){
        for(int i=1; i<=n; ++i){
            par[i]=i;
            ene[i]=-1;
        }
    }
    int R(int x){return (x==par[x])?x:(par[x]=R(par[x])); }
    int Join(int a, int b){
        if(a==-1 || b==-1) return a+b+1;
        return par[R(a)]=R(b);
    }
    void dis(int a, int b){
        a=R(a); b=R(b);
        if(a == b) mosun();
        int c=ene[b], d=ene[a];
        a=Join(a, c); b=Join(b, d);
        ene[a]=b; ene[b]=a;
    }
} uf;

int recpt[max_n];
bool dead[max_n];

typedef tuple<int,int,int,int> t4;
vector<t4> query;

const int M=2097152;
vector<int> trec[M<<1];
int tcnt[M<<1];

void upjoin(int ind, int y){
    y += M;
    while(y){
        if(tcnt[y]){
            int last=-1;
            while(trec[y].size()){
                int cr=trec[y].back(); trec[y].pop_back();
                if(dead[cr]) continue;
                recpt[cr]=uf.Join(ind, recpt[cr]);
                last=cr;
            }
            if(last == -1) tcnt[y]=0;
            else tcnt[y]=1, trec[y].push_back(last);
        }
        y>>=1;
    }
}

void dorect(){
    for(int i=1; i<=n; ++i){
        int l, r, d, u;
        int x, y; tie(x, y) = pt[i];
        l=x; r=y; d=y+1; u=2*n+1;
        query.emplace_back(l,    i, d, u);
        query.emplace_back(r+1, -i, d, u);
        recpt[i]=-1;
        
        query.emplace_back(l, 0, r, i);
    }
    sort(all(query));
    for(auto Q:query){
        int x, ind, d, u;
        tie(x, ind, d, u) = Q;
        if(ind == 0){
            upjoin(u, d);
        } else if(ind > 0){
            d+=M; u+=M;
            auto push= [&](int x){
                ++tcnt[x]; trec[x].push_back(ind);
            };
            while(d<=u){
                if(d&1) push(d++);
                if(u%2==0) push(u--);
                d>>=1; u>>=1;
            }
        } else {
            dead[-ind]=1;
        }
    }
}

bool chk[1000010];

int main()
{
	in();
    uf.init();
    dorect();
	for(int i=1; i<=n; ++i){
        int r=i;
        if(recpt[r] != -1){
            uf.dis(i, recpt[r]);
        }
	}
	ll ans=1;
	for(int i=1; i<=n; ++i){
        if(uf.par[i] == i){
            if(chk[i]) continue;
            chk[i]=1;
            int e=uf.ene[i];
            if(e != -1) chk[uf.R(e)]=1;
            ans = (ans*2)%mod;
        }
	}
	printf("%lld\n", ans);
    return 0;
}
