#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
void read(int& x){ scanf("%d",&x); }
template<typename T,typename... Args>
void read(T& a,Args&... b){ read(a); read(b...); }
#define all(x) (x).begin(),(x).end()
#define pb push_back

int n;

int v1[100010];
int v2[100010];
int vp[100010];

void in(){
	read(n);
	for(int i=0; i<n; ++i) read(v1[i]), vp[v1[i]]=i;
	for(int i=0; i<n; ++i) read(v2[i]);
}

const int M=131072;
int tree[M<<1];

void upd(int p, int v){
	p+=M;
	while(p) tree[p]=max(tree[p], v), p>>=1;
}

int rM(int l, int r){
	l+=M; r+=M;
	int ret=0;
	while(l<=r){
		if(l&1) ret=max(ret, tree[l++]);
		if((r&1)==0) ret=max(ret, tree[r--]);
		l>>=1; r>>=1;
	}
	return ret;
}

int main()
{
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
    in();
    int ans=0;
    for(int i=0; i<n; ++i){
		vector<int> cvs;
		for(int d=-4; d<=4; ++d){
			int cv=v2[i]+d;
			if(1<=cv && cv<=n) cvs.pb(vp[cv]);
		}
		sort(all(cvs)); reverse(all(cvs));
		for(int cv:cvs){
			int l=cv;
			int m=rM(0, l-1)+1;
			ans = max(ans, m);
			upd(l, m);
		}
    }
    printf("%d\n", ans);
    return 0;
}
