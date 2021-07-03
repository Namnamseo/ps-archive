#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <functional>
#include <string>
#include <stack>
using namespace std;
#define sz(v) ((v).size())
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define coord_comp(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define v_index(v, x) (lower_bound(all(v),x)-(v).begin())
typedef pair<int,int> pp;
typedef long long ll;
void read(int& x){ scanf("%d",&x); }
void read(ll& x){ scanf("%lld",&x); }
template<typename T1,typename T2>
void read(pair<T1,T2>& p){ read(p.first); read(p.second); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

int n,q;

const ll inf=1LL<<60;

struct segg {
	static const int M=262144;
	ll sumtree[M*2];
	ll mintree[M*2];
	ll lazy[M*2];
	void init(){
		int i;
		for(i=0;i<n;++i) {
			read(sumtree[M+i]);
			mintree[M+i]=sumtree[M+i];
		}
		for(i=n;i<M;++i) mintree[M+i]=inf;
		for(i=M-1;1<=i;--i) mintree[i]=min(mintree[i<<1],mintree[(i<<1)|1]),
			sumtree[i]=sumtree[i<<1]+sumtree[(i<<1)|1];
	}
	void pd(int pos,int sz){
		if(pos>=M)return;
		int c=pos*2;
		ll x=lazy[pos];
		sumtree[c]+=sz/2*x;
		mintree[c]+=x;
		lazy[c]+=x;
		++c;
		sumtree[c]+=sz/2*x;
		mintree[c]+=x;
		lazy[c]+=x;
		lazy[pos]=0;
	}
	void update(int l,int r,int val,int pos=1,int ml=0,int mr=M-1){
		pd(pos,mr-ml+1);
		if(l<=ml && mr<=r){
			sumtree[pos]+=val*ll(mr-ml+1);
			mintree[pos]+=val;
			lazy[pos]+=val;
			return;
		} else if(mr<l || r<ml) return;
		update(l,r,val,pos<<1,ml,(ml+mr)/2);
		update(l,r,val,(pos<<1)|1,(ml+mr)/2+1,mr);
		mintree[pos]=min(mintree[pos<<1],mintree[(pos<<1)|1]);
			sumtree[pos]=sumtree[pos<<1]+sumtree[(pos<<1)|1];
	}
	ll rangeMin(int a,int b,int pos=1,int ml=0,int mr=M-1){
		pd(pos,mr-ml+1);
		if(a<=ml && mr<=b){
			return mintree[pos];
		} else if(mr<a || b<ml) return inf;
		return min(rangeMin(a,b,pos<<1,ml,(ml+mr)/2),
				   rangeMin(a,b,(pos<<1)|1,(ml+mr)/2+1,mr));
	}
	ll rangeSum(int a,int b,int pos=1,int ml=0,int mr=M-1){
		pd(pos,mr-ml+1);
		if(a<=ml && mr<=b){
			return sumtree[pos];
		} else if(mr<a || b<ml) return 0;
		return rangeSum(a,b,pos<<1,ml,(ml+mr)/2)+
			   rangeSum(a,b,(pos<<1)|1,(ml+mr)/2+1,mr);
	}
	
} seg;

int main(){
	int q;
	read(n,q);
	seg.init();
	for(;q--;){
		char com[5];
		scanf("%s",com);
		if(com[0]=='M'){
			int a,b;
			read(a,b);
			--a; --b;
			printf("%lld\n",seg.rangeMin(a,b));
		} else if(com[0]=='P'){
			int a,b,c;
			read(a,b,c);
			--a; --b;
			seg.update(a,b,c);
		} else {
			int a,b;
			read(a,b);
			--a; --b;
			printf("%lld\n",seg.rangeSum(a,b));
		}
	}
	return 0;
}