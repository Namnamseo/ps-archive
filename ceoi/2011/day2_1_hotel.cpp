#include <bits/stdc++.h>
using namespace std;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
typedef pair<int,int> pp;
#define all(x) (x).begin(),(x).end()
#define pb push_back

const int max_n = 500010, inf=2e9;

int matches;

pp hot[max_n];
pp off[max_n];
int hn, on;

const int M=524288;
pp tree[M<<1];

pp rmin(int l, int r){
	l+=M; r+=M;
	pp ret(inf, -1);
	while(l<=r){
		if(l%2==1) ret=min(ret, tree[l++]);
		if(r%2==0) ret=min(ret, tree[r--]);
		l>>=1; r>>=1;
	}
	return ret;
}

void upd(int pos,pp val){
	pos+=M; tree[pos]=val; pos>>=1;
	while(pos) tree[pos]=min(tree[pos<<1], tree[pos<<1|1]), pos>>=1;
}

pp poll(int x){
	int from = lower_bound(hot+1, hot+hn+1, pp{x, 0})-hot;
	return rmin(from, hn);
}

bool chkH[max_n];
bool chkO[max_n];

typedef tuple<int,int,int> t3;

int main()
{
	for(auto& x:tree) x=pp{inf, -1};
	read(hn, on, matches);
	vector<int> xp;
    for(int i=1; i<=hn; ++i) read(hot[i].second, hot[i].first);
    for(int i=1; i<=on; ++i) read(off[i].second, off[i].first);
    sort(hot+1, hot+hn+1);
    for(int i=1; i<=hn; ++i) upd(i, pp{hot[i].second, i});
    
    priority_queue<t3> pq;
    for(int i=1; i<=on; ++i){
		auto tmp=poll(off[i].first);
		if(tmp.first < off[i].second){
			pq.push(t3{off[i].second-tmp.first, i, tmp.second});
		}
    }
    
    typedef long long ll;
    ll ans=0;
    while(pq.size() && matches){
		int av, i, j;
		tie(av, i, j) = pq.top(); pq.pop();
		if(chkO[i]){
			continue;
		}
		pp tmp=poll(off[i].first);
		if(tmp.second != j){
			if(tmp.first < off[i].second){
				pq.push(t3{off[i].second-tmp.first, i, tmp.second});
			}
			continue;
		}
		ans += av;
		chkO[i]=1;
		chkH[j]=1;
		--matches;
		int p=tmp.second;
		upd(p, pp{inf, p});
    }
    
    printf("%lld\n", ans);
    return 0;
}
