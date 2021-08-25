#include <cstdio>
#include <set>
using namespace std;
const int z=100010;
int n,k;

int parent[z];
int color[z];
int vis[z];
int aup[z];
int bup[z];
int nowtime;

int findLCA(int a,int b){
    ++nowtime;
    int ac=0, bc=0;
    aup[a]=0, bup[b]=0;
    while(true){
        aup[a]=ac;      bup[b]=bc;
        if(vis[a]==nowtime && a) return a;
        if(vis[b]==nowtime && b) return b;
        vis[a]=nowtime; vis[b]=nowtime;
        if(a==b)            return a;
        if(a) {
            a=parent[a];
            ++ac;
        }
        if(b) {
            b=parent[b];
            ++bc;
        }
    }
}

int main()
{
    scanf("%d%d",&n,&k);
    int a,b,c;
    parent[0]=-1;
    set<int> asdf;
    for(;k--;){
        int r;
        scanf("%d",&r);
        if(r==1){
            scanf("%d%d%d",&a,&b,&c);
            int lca=findLCA(a,b);
            //printf("LCA of %d and %d is %d; dist %d, %d\n",a,b,lca,aup[lca],bup[lca]);
            for(;aup[lca]--;){
                color[a]=c;
                a=parent[a];
            }
            for(;bup[lca]--;){
                color[b]=c;
                b=parent[b];
            }
        } else if(r==2){
            scanf("%d%d",&a,&b);
            parent[a]=b;
        } else if(r==3){
            scanf("%d%d",&a,&b);
            int lca=findLCA(a,b);
            for(;aup[lca]--;){
                asdf.insert(color[a]);
                a=parent[a];
            }
            for(;bup[lca]--;){
                asdf.insert(color[b]);
                b=parent[b];
            }
            printf("%d\n",int(asdf.size()));
            asdf.clear();
        }
    }
    return 0;
}
