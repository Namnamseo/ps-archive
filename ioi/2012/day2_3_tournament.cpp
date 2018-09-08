#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)((v).size()))
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

int n, rnds, R;

#define rank namseo

int *rank;

struct pos_tree {
	static const int M=131072;
	int tree[M*2];
	void upd(int pos,int val){
		pos += M;
		tree[pos]=val; pos>>=1;
		while(pos){
			tree[pos]=tree[pos*2] + tree[pos<<1|1];
			pos >>= 1;
		}
	}

	void init(){
		for(int i=1; i<=n; ++i) upd(i, 1);
	}

	int find_kth(int k){
		int sum = 0;
		int pos = 1;
		while(pos < M){
			pos *= 2;
			if(sum + tree[pos] < k){
				sum += tree[pos];
				++pos;
			}
		}
		return pos - M;
	}
} pos_T;

struct maxtree{
	static const int M=131072;
	int tree[262144];

	void upd(int pos,int val){
		pos += M;
		tree[pos]=val; pos >>= 1;
		while(pos){
			tree[pos] = max(tree[pos<<1], tree[pos<<1|1]);
			pos >>= 1;
		}
	}

	void init(){
		for(int i=1; i<n; ++i) upd(i, rank[i]);
	}

	int rangemax(int a,int b){
		a+= M; b+=M;
		int ret=-1;
		while(a<=b){
			if(a%2==1) ret=max(ret, tree[a++]);
			if(b%2==0) ret=max(ret, tree[b--]);
			a>>=1; b>>=1;
		}
		return ret;
	}
} max_T;

int nodeL[100010];
int nodeR[100010];
int nxtNode[100010];

int maxDepth[100010];
int maxPos  [100010];

int GetBestPosition(int N, int C, int rr, int *K, int *S, int *E){
	n = N;
	rnds = C;
	R = rr;
	rank = K-1;

	max_T.init();
	pos_T.init();

	for(int i=1; i<=n; ++i)
		nodeL[i] = nodeR[i] = i,
		nxtNode[i] = i+1,
		maxPos[i] = i;

	int ans=0, ansPos=1;

	for(int i=1; i<=rnds; ++i){
		int L = S[i-1], R = E[i-1];
		++L; ++R;
		int a=pos_T.find_kth(L), b=pos_T.find_kth(R);
		if(a==0) break;

		int realL=2e9, realR=-1;
		int maxD = -1, maxP = -1;

		for(int j=a; j<=b; j=nxtNode[j]){

			pos_T.upd(j, 0);

			realL=min(realL, nodeL[j]);
			realR=max(realR, nodeR[j]);

			if(maxDepth[j] != -1){
				if(maxD < maxDepth[j])
					maxP = maxPos[j],
					maxD = maxDepth[j];
				else if(maxD == maxDepth[j])
					maxP = min(maxP, maxPos[j]);
			}
		}

		pos_T.upd(a, 1);
		nodeL[a]=realL;
		nodeR[a]=realR;
		nxtNode[a] = nxtNode[b];
		maxDepth[a] = -1;
		maxPos  [a] = -1;

		if(maxP == -1 || max_T.rangemax(realL,realR-1) > ::R){
			continue;
		}

		maxDepth[a] = maxD + 1;
		maxPos  [a] = maxP;

		if(ans < maxDepth[a])
			ans = maxDepth[a],
			ansPos = maxPos[a];
		else if(ans == maxDepth[a]) ansPos = min(ansPos, maxPos[a]);
	}
	return ansPos-1;
}