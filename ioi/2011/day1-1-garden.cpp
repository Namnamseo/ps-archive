#include "garden.h"
#include "gardenlib.h"

int befnext[150010][2];

int next[300010];
int nc  [300010];

int p;

void addEdge(int a,int b)
{
    if(nc[a]<2)
    {
        befnext[a][nc[a]]=b;
        nc[a]++;
    }
    if(nc[b]<2)
    {
        befnext[b][nc[b]]=a;
        nc[b]++;
    }
}

int visit  [300010];
int dists  [300010];

int pdist  [300010][2];
int loops  [300010][2];

int vn;

int stack [300010];

void run(int pos)
{
    int bef=-1;

    int metpdist[2]= {-1,-1};

    int top = 0;
    int loopsize;
    int temp;
    while(true)
    {
        if(visit[pos]==vn)
        {
            loopsize = dists[bef] - dists[pos] + 1;

            int top_orig = top;
            int i;
            for(i=0; i<2; i++)
            {
                if(metpdist[i]!=-1)
                {
                    if(metpdist[i]>=dists[pos])
                    {
                        // p[i] is in the graph
                        temp = (metpdist[i]-dists[pos]+1)%loopsize;
                        top = top_orig;
                        while(top!=0)
                        {
                            if(stack[top-1] == p + 150000*i) temp%=loopsize;
                            loops[stack[top-1]][i]=loopsize;
                            pdist[stack[top-1]][i]=temp;
                            temp++;
                            top--;
                        }
                    }
                    else
                    {
                        while(top!=0)
                        {
                            if(metpdist[i] == dists[stack[top-1]]) break;
                            top--;
                        }
                        temp = 0;
                        while(top!=0)
                        {
                            pdist[stack[top-1]][i] = temp;
                            loops[stack[top-1]][i] = 987654321;
                            temp++;
                            top--;
                        }
                    }
                }
            }
            break;
        }
        if(visit[pos]!=-1 && visit[pos]<vn)
        {
            int i,l;
            int origtop = top;
            for(i=0; i<2; i++)
            {
                if(pdist[pos][i]==-1) {
                    if(metpdist[i] != -1){
                        top = origtop;
                        while(top != 0){
                            if(stack[top-1] == p + 150000*i){
                                break;
                            }
                            top--;
                        }
                        temp=0;
                        while(top!=0){
                            loops[stack[top-1]][i]=987654321;
                            pdist[stack[top-1]][i]=temp;
                            temp++;
                            top--;
                        }
                    }
                    continue;
                }
                l=loops[pos][i];
                temp = pdist[pos][i]+1;
                top = origtop;
                while(top!=0)
                {
                    pdist[stack[top-1]][i]=temp;
                    loops[stack[top-1]][i]=l;
                    temp++;
                    top--;
                }
            }
            
            break;
        }


        if(bef!=-1) dists[pos] = dists[bef] + 1;
        else dists[pos]=0;

        if(pos == p)
        {
            metpdist[0] = dists[pos];
        }
        else if(pos==p+150000)
        {
            metpdist[1] = dists[pos];
        }

        stack[top++]=pos;
        visit[pos]=vn;

        bef=pos;
        pos = next[pos];
    }
    vn++;
}

void findP(int n,int steps)
{
    int i,j;
    int ans=0;
    for(i=0; i<n; i++)
    {
        for(j=0; j<2; j++)
        {
            if(pdist[i][j]!=-1)
            {
                
                if(loops[i][j] == 987654321)
                {
                    if(pdist[i][j]==steps)
                    {
                        ans++;
                        break;
                    }
                    continue;
                }
                if(steps>=pdist[i][j] && !((steps-pdist[i][j])%loops[i][j]))
                {
                    ans++;
                    break;
                }
            }
        }
    }
    answer(ans);
}

void count_routes(int n, int m, int P, int R[][2], int Q, int G[])
{
    p=P;
    int i;
    int a,b;
    for(i=0; i<m; i++)
    {
        a=R[i][0];
        b=R[i][1];
        addEdge(a,b);
    }
    for(i=0; i<n; i++)
    {
        if(nc[i]>=1)
        {
            next[i]=befnext[i][0];
            if(befnext[befnext[i][0]][0]==i)
            {
                next[i]+=150000;
            }
            if(nc[i]==2)
            {
                next[i+150000]=befnext[i][1];
                if(befnext[befnext[i][1]][0]==i)
                {
                    next[i+150000]+=150000;
                }
            }
            else {
                next[i+150000]=next[i];
            }
        }

        visit[i]=visit[i+150000]=-1;
        
        pdist[i][0]=pdist[i][1]=-1;
        loops[i][0]=loops[i][1]=-1;
        
        pdist[i+150000][0]=pdist[i+150000][1]=-1;
        loops[i+150000][0]=loops[i+150000][1]=-1;
    }

    vn=1;

    for(i=0; i<n; i++)
    {
        if(visit[i]==-1 && nc[i]) run(i);
        if(visit[i+150000]==-1 && nc[i]) run(i+150000);
    }

    for(i=0; i<Q; i++) findP(n,G[i]);
}
