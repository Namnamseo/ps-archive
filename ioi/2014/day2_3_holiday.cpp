#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

ll inf = (1LL << 60);

vector<int> xp;

struct KF {
	const static int M = 131072;
	int tree[M<<1];
	ll  tsum[M<<1];
	void init(){
		for(auto& x:tree) x=0;
		for(auto& x:tsum) x=0;
	}
	
	void app(int x, int d){
		int p=lower_bound(all(xp), x) - xp.begin();
		p += M;
		while(p){
			tree[p] += d;
			tsum[p] += d*x;
			p >>= 1;
		}
	}
	void add(int x){ app(x, 1); }
	void del(int x){ app(x, -1); }
	
	ll topk(int k){
		if(k > tree[1]) k=tree[1];
		if(k == 0) return 0ll;
		ll ret=0;
		int p=1;
		while(p < M){
			if(k > tree[p*2+1]){
				k -= tree[p*2+1];
				ret += tsum[p*2+1];
				p *= 2;
			} else p = p*2+1;
		}
		return ret + k*1LL*xp[p-M];
	}
} kfinder;

int cur_l, cur_r;

ll ask(vector<int>& data, int l, int r, int d){
	while(cur_r < r) kfinder.add(data[++cur_r]);
	while(l < cur_l) kfinder.add(data[--cur_l]);
	while(r < cur_r) kfinder.del(data[cur_r--]);
	while(cur_l < l) kfinder.del(data[cur_l++]);
	return kfinder.topk(d);
}

ll work(vector<int> data, int sp, int days){
	int n = data.size();
	kfinder.init(); cur_l = 1, cur_r = 0;
	typedef tuple<int,int,int,int> state;
	queue<state> q; q.push(state{0, sp, 0, n-1});
	ll ans = -inf;
	while(q.size()){
		int ml, mr, xl, xr;
		tie(ml, mr, xl, xr) = q.front(); q.pop();
		int p=(ml+mr)/2;
		pair<ll,int> tmp(-inf, -1);
		for(int i=xl; i<=xr; ++i){
			if(p <= i && (sp-p) + (i-p) <= days)
				tmp=max(tmp, make_pair(ask(data, p, i, days-(sp-p)-(i-p)), i));
		}
		ans = max(ans, tmp.first);
		int use=tmp.second;
		if(ml <= p-1)
			q.push(state{ml, p-1, xl, use});
		if(p+1 <= mr)
			q.push(state{p+1, mr, use, xr});
	}
	return ans;
}

int main()
{
	// input
	int n, start, d;
	read(n, start, d);
	vector<int> p;
	p.resize(n);
	for(int& x:p) read(x), xp.pb(x);
	sort(all(xp)); xp.erase(unique(all(xp)), xp.end());
	// do left side
	ll ans=work(p, start, d);
	// flip
	reverse(all(p)); start=n-1-start;
	// do right side
	ans=max(ans, work(p, start, d));
	// print ans
	printf("%lld\n", ans);
    return 0;
}
