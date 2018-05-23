#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

const int max_n = int(1e6) + 10, inf = 1e9;

typedef pair<int,int> pp;
pp data[max_n];
int n;

int dpTN[max_n];
int dpMX[max_n];

struct indi {
	int team_num;
	int max_size;
	int from;
	indi(int a=-1, int b=inf, int c=-1){
		team_num = a; max_size = b; from = c;
	}
	bool operator<(const indi& r) const {
		return make_pair(team_num, -max_size) <
			   make_pair(r.team_num, -r.max_size);
	}
};

const int M =1048576;
indi tree[M<<1];
indi tree_add[M<<1];
indi dp[max_n];
int bef[max_n];

indi getMax(indi* tree, int p){
	indi ret;
	p+=M;
	while(p) ret=max(ret, tree[p]), p>>=1;
	return ret;
}

void upd(indi* tree, int l, int r, indi val){
	l+=M; r+=M;
	while(l<=r){
		if(l%2==1) tree[l]=max(tree[l], val), ++l;
		if(r%2==0) tree[r]=max(tree[r], val), --r;
		l>>=1; r>>=1;
	}
}

vector<vector<int>> ans;

struct cmp {
	bool operator()(const int& a, const int& b){
		return ans[a].size() > ans[b].size();
	}
};
priority_queue<int,vector<int>,cmp> PQ;

int main()
{
    read(n);
    for(int i=1; i<=n; ++i){
		read(data[i].first); data[i].second=i;
    }
    sort(data+1, data+n+1, greater<pp>());
    for(int i=0; i<=n; ++i){
		indi v1 = getMax(tree, i);
		indi v2 = getMax(tree_add, i);
		v2.max_size += i;
		indi my = max(v1, v2);
		if(i == 0) my = indi(0, 0, -1);
		dp[i] = my;
		bef[i] = my.from;
		if(i == n) break;
		if(my.team_num == -1) continue;
		int tn = my.team_num;
		int mt = my.max_size;
		ll pt = tn * 1LL * mt;
		int mv=data[i+1].first;
		upd(tree, i+1, min(pt, ll(n)), indi(tn, mt, -i));
		upd(tree, i+mv, min(i+mt-1, n), indi(tn+1, mt, i));
		upd(tree_add, i+max(mv, mt), n, indi(tn+1, -i, i));
    }
    
    printf("%d\n", dp[n].team_num);
	
	vector<pp> pend;
    int p=n;
    while(p){
		int x=bef[p];
		if(x < 0){
			x=-x;
			for(int i=x+1; i<=p; ++i){
				pend.pb(pp{int(ans.size()), data[i].second});
			}
		} else {
			vector<int> v;
			for(int i=x+1; i<=p; ++i){
				v.pb(data[i].second);
			}
			ans.pb(v);
		}
		p=x;
    }
    int an=ans.size();
    for(int i=an-1; i>=0; --i){
		PQ.push(i);
		while(pend.size()){
			int x, y;
			tie(x, y) = pend.back();
			if(x != i) break;
			pend.pop_back();
			int p=PQ.top(); PQ.pop();
			ans[p].pb(y);
			PQ.push(p);
		}
    }
    for(auto& tmp:ans){
		printf("%d ", int(tmp.size()));
		for(int x:tmp) printf("%d ", x);
		putchar(10);
	}
    return 0;
}
