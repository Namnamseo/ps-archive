#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int,int> pp;
priority_queue<pp> pq;

int n,m,q;

struct ES{
	int f,t;
	bool dead;
} ee[300010];

vector<int> edge	[300010];
vector<int> parent  [300010];
vector<int> child   [300010];
vector<int> child_ei[300010];

int  dijk[300010];
bool dead[300010];
int boolman;
int alive_pars[300010];

void dodijk(){
	int i;
	for(i=2;i<=n;++i) dijk[i]=1e9;
	pq.push(pp(0,1));
	int me;
	while(pq.size()){
		pp cur=pq.top(); pq.pop();
		if(dijk[me=cur.second]!=-cur.first) continue;
		int sz=edge[me].size(), nxt;
		for(i=0;i<sz;++i){
			ES& tmp=ee[edge[me][i]];
			nxt=tmp.f+tmp.t-me;
			
			if(dijk[nxt] > dijk[me]+1){
				dijk[nxt]=dijk[me]+1;
				pq.push(pp(-dijk[nxt],nxt));
				{
					vector<int>().swap(parent[nxt]);
					parent[nxt].clear();
				}
				parent[nxt].push_back(me);
				++alive_pars[nxt];
				
				child [me].push_back(nxt);
				child_ei[me].push_back(edge[me][i]);
			} else if(dijk[nxt]==dijk[me]+1){
				parent[nxt].push_back(me);
				++alive_pars[nxt];
				
				child [me].push_back(nxt);
				child_ei[me].push_back(edge[me][i]);
			}
		}
	}
}

void work(int x){
	if(alive_pars[x]==0 && !dead[x]){
		++boolman;
		dead[x]=true;
		int i,sz=child[x].size(),nxt;
		for(i=0;i<sz;++i){
			nxt=child[x][i];
			if(!ee[child_ei[x][i]].dead){
				--alive_pars[nxt];
				work(nxt);
			}
		}
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	int i;
	for(i=1;i<=m;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		ee[i].f=a; ee[i].t=b;
		ee[i].dead=false;
		edge[a].push_back(i);
		edge[b].push_back(i);
	}
	dodijk();
	
	for(;q--;){
		scanf("%d",&i);
		ee[i].dead=true;
		int a=ee[i].f, b=ee[i].t;
		if(dijk[a]>dijk[b]) swap(a,b);
		if(dijk[a]+1 == dijk[b]){
			if(!dead[a]){
				--alive_pars[b];
			}
			work(b);
		}
		printf("%d\n",boolman);
	}
	return 0;
}
