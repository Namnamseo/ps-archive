#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define x first
#define y second
const int inf=1e9;

int n, A, B;

pp data[300010];
vector<int> ed[300010];
vector<int> re[300010];

void in(){
	int m;
	read(n, m, A, B);
	for(int i=1; i<=n; ++i){
		int x, y; read(x, y);
		data[i] = {x, y};
	}
	for(;m--;){
		int f, t, k;
		read(f, t, k);
		ed[f].pb(t);
		re[t].pb(f);
		if(k != 1) ed[t].pb(f), re[f].pb(t);
	}
}

vector<int> right;
int miny[300010];
int maxy[300010];

bool vis[300010];

void bfs(){
	queue<int> q;
	for(int i=1; i<=n; ++i) if(data[i].x == 0) q.push(i), vis[i]=1;
	while(q.size()){
		int x=q.front(); q.pop();
		for(int y:ed[x]){
			if(!vis[y]) vis[y]=1, q.push(y);
		}
	}
}

void sep(){
	fill(miny+1, miny+n+1, inf);
	fill(maxy+1, maxy+n+1, -inf);
	vector<int> ys;
	for(int i=1; i<=n; ++i) if(data[i].x == A && vis[i]) ys.pb(data[i].y);
	sort(all(ys)); ys.erase(unique(all(ys)), ys.end());
	for(int i=1; i<=n; ++i) if(data[i].x == A && vis[i]){
		miny[i] = maxy[i] = lower_bound(all(ys), data[i].y) - ys.begin();
	}
}

void dijk(){
	priority_queue<pp> pq;
	for(int i=1; i<=n; ++i) if(data[i].x == A){
		pq.push(pp{-miny[i], i});
	}
	while(pq.size()){
		int d, i; tie(d, i) = pq.top(); pq.pop(); d=-d;
		if(d != miny[i]) continue;
		for(int y:re[i]) if(miny[y] > d){
			miny[y]=d;
			pq.push(pp{-miny[y], y});
		}
	}
	
	for(int i=1; i<=n; ++i) if(data[i].x == A){
		pq.push(pp{maxy[i], i});
	}
	while(pq.size()){
		int d, i; tie(d, i) = pq.top(); pq.pop();
		if(d != maxy[i]) continue;
		for(int y:re[i]) if(maxy[y] < d){
			maxy[y]=d;
			pq.push(pp{maxy[y], y});
		}
	}
}

int main()
{
    in(); bfs(); sep(); dijk();
    vector<pp> ans;
    for(int i=1; i<=n; ++i) if(data[i].x == 0){
		if(maxy[i] == -inf) maxy[i]=0, miny[i]=1;
		ans.pb(pp{data[i].y, maxy[i] - miny[i] + 1});
    }
    sort(all(ans)); reverse(all(ans));
    for(auto tmp:ans) printf("%d\n", tmp.second);
    return 0;
}
