#include <iostream>
#include <fstream>
#include <vector>
#define V std::vector

V<int> edge[10001];

int n,m;

inline int enc(int a,int b){ return a*n+b; }

int q[10001];
int h,t;

bool lit[10001];
bool vis[10001];

int dx[5]={0,1,0,-1,0};

int main()
{
	std::ifstream I; I.open("lightson.in");
	std::ofstream O; O.open("lightson.out");
	I>>n>>m;
	int x,y,a,b;
	for(;m--;) I>>x>>y>>a>>b, edge[enc(x-1,y-1)].push_back(enc(a-1,b-1));
	q[h++]=0;
	lit[0]=1;
	vis[0]=1;
	int me;
	int ans=1;
	int i;
	int nx,ny;
	while(t<h){
		me=q[t++];
		for(auto that : edge[me]){
			if(!lit[that]){
				x=that/n; y=that%n;
				bool flag = 0;
				for(i=0;i<4;++i){
					nx=x+dx[i]; ny=y+dx[i+1];
					if(0<=nx && 0<=ny && nx<n && ny<n){
						if(vis[enc(nx,ny)]){
							flag = 1;
							break;
						}
					}
				}
				if(flag){
					q[h++]=that;
					vis[that]=1;
				}
				++ans;
				lit[that]=1;
			}
		}
		x=me/n; y=me%n;
		for(i=0;i<4;++i){
			nx=x+dx[i]; ny=y+dx[i+1];
			if(0<=nx && 0<=ny && nx<n && ny<n){
				if(lit[enc(nx,ny)] && !vis[enc(nx,ny)]){
					q[h++]=enc(nx,ny);
					vis[q[h-1]]=1;
				}
			}
		}
	}
	O<<ans;
	return 0;
}
