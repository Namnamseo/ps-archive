#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <deque>
#define pb push_back
#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())

using namespace std;
typedef pair<int,int> pp;
typedef long long ll;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T&a,Args&...b){ read(a); read(b...); }

int y[200010];
pp dt[200010];
int n;

const int M=262144;

int tree[M*2];

void upd(int pos,int val){
	pos+=M;
	while(pos){
		tree[pos] += val;
		pos >>= 1;
	}
}

int rangeSum(int a,int b){
	int ret=0;
	a+=M; b+=M;
	while(a<=b){
		if(a%2==1) ret+=tree[a++];
		if(b%2==0) ret+=tree[b--];
		a/=2; b/=2;
	}
	return ret;
}

ll work(vector<int>& v){
	if(sz(v) <= 1) return 0;
	int n=sz(v);
	int minv = *min_element(all(v));
	int maxv = *max_element(all(v));
	int mid=(minv+maxv)/2;

	ll ans=0;
	vector<int> v1, v2;
	stack<int> s, ss;

	for(int i=0; i<n; ++i){
		if(v[i] <= mid){
			v1.pb(v[i]);
			while(sz(s) && v[s.top()] < v[i]){
				upd(s.top(), -1);
				s.pop();
			}
			s.push(i);
			upd(i, 1);
		} else {
			v2.pb(v[i]);
			while(sz(ss) && v[ss.top()] > v[i]){
				ss.pop();
			}
			ans += rangeSum((sz(ss))?(ss.top()+1):0, i-1);
			ss.push(i);
		}
	}
	while(s.size()){
		upd(s.top(), -1); s.pop();
	}
	ans += work(v1) + work(v2);
	return ans;
}

int main(){
	read(n);
	vector<int> ys;
	for(int i=1; i<=n; ++i){
		read(dt[i].first, dt[i].second);
		ys.push_back(dt[i].second);
	}
	sort(dt+1, dt+n+1);
	sort(all(ys));
	vector<int> v;
	for(int i=1; i<=n; ++i){
		v.pb(lower_bound(all(ys), dt[i].second)-ys.begin());
	}
	printf("%lld\n", work(v));
	return 0;
}
