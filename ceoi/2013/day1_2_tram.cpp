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
#define eb emplace_back
#define x first
#define y second
#define rep(i, n) for(int i=0; i<(n); ++i)
#define rrep(i, n) for(int i=1; i<=(n); ++i)

int n, m;
pp history[30001];
char chk[150010][2];

typedef pair<ll,pp> candtype;
auto cmp = [](const candtype& a, const candtype& b){
	return make_tuple(-a.x, a.y) < make_tuple(-b.x, b.y);
};
set<candtype,decltype(cmp)> cand(cmp);

multiset<int> row;

const ll inf = 1ll<<60;

ll dist(ll a, ll b){ return a*a + b*b; }

void get_cand(int l, int r, vector<candtype>& v){
	v.clear();

	if(l+1 == r) return;
	int lb, rb;
	if(l == 0){
		if(r == n+1){
			v.eb(0, pp{1, 0});
			return;
		} else lb = rb = 1;
	} else if(r == n+1) lb = rb = n;
	else lb = (l+r)/2, rb = (l+r+1)/2;

	for(int ri=lb; ri<=rb; ++ri) for(int ci=0; ci<2; ++ci){
		ll md = inf;
		for(int br=l; br<=r; br+=(r-l)) for(int bc=0; bc<2; ++bc){
			if(chk[br][bc]) md = min(md, dist(br-ri, bc-ci));
		}
		if(v.size()){
			ll cv = v.back().first;
			if(cv > md) continue;
			else if(cv < md) v.clear();
		}
		if(v.empty() || v.back().first == md){
			v.eb(md, pp{ri, ci});
		}
	}
}

int get_bef(int r){ return *--row.lower_bound(r); }
int get_nxt(int r){ return *row.upper_bound(r); }

vector<candtype> v;
void Add(int l, int r){ get_cand(l, r, v); for(auto& c:v) cand.insert(c); }
void Del(int l, int r){ get_cand(l, r, v); for(auto& c:v) cand.erase(c); }

int main(){
	read(n, m);
	row.insert(0); row.insert(n+1);
	Add(0, n+1);
	rrep(qi, m){
		static char cmdbuf[5];
		scanf("%s", cmdbuf);
		if(cmdbuf[0] == 'E'){
			auto itm = *cand.begin();
			int cr, cc;
			tie(cr, cc) = history[qi] = cand.begin() -> second;
			printf("%d %d\n", cr, cc+1);
			int bef = get_bef(cr), nxt = get_nxt(cr);
			Del(bef, nxt);
			row.insert(cr); chk[cr][cc]=1;
			Add(bef, cr); Add(cr, nxt);

			if(!chk[cr][cc^1]){
				cand.emplace(1, pp{cr, cc^1});
			}
			cand.erase(itm);
		} else {
			int bq; read(bq);
			int r, c; tie(r, c) = history[bq];
			int bef = get_bef(r), nxt = get_nxt(r);
			Del(bef, r); Del(r, nxt);
			chk[r][c] = 0; row.erase(row.find(r));
			if(chk[r][c^1]){
				Add(bef, r); Add(r, nxt);
				cand.emplace(1, pp{r, c});
			} else {
				cand.erase(candtype(1, pp{r, c^1}));
				Add(bef, nxt);
			}
		}
	}
	return 0;
}
