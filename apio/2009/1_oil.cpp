#include <iostream>

using namespace std;

int m,n,k;

int dat[1510][1510];

int ul[1510][1510];
int ur[1510][1510];
int dl[1510][1510];
int dr[1510][1510];

int u[1510];
int d[1510];
int l[1510];
int r[1510];

int uu[1510];
int dd[1510];
int ll[1510];
int rr[1510];

int ulu[1510][1510];
int ull[1510][1510];

int rect[1510][1510];

int i,j;

int sum(int u,int d,int l,int r){
    return rect[d][r]-rect[u-1][r]-rect[d][l-1]+rect[u-1][l-1];
}

int max(int a,int b){ return a>b?a:b; }

int main()
{
    // in 
    {
        cin>>n>>m>>k;
        int i,j;
        for(i=1;i<=n;++i){
            for(j=1;j<=m;++j){
                cin>>rect[i][j];
                rect[i][j]+=rect[i-1][j]+rect[i][j-1]-rect[i-1][j-1];
            }
        }
    }
    
    // fill
    {
        int i,j;
        for(i=k;i<=n;++i){
            for(j=k    ;j<=m;++j) ul[i][j]=max(max(ul[i-1][j],ul[i][j-1]),sum(i-k+1,i,j-k+1,j));
            for(j=m-k+1;j>=1;--j) ur[i][j]=max(max(ur[i-1][j],ur[i][j+1]),sum(i-k+1,i,j,j+k-1));
        }
        for(i=n-k+1;i>=1;--i){
            for(j=k    ;j<=m;++j) dl[i][j]=max(max(dl[i+1][j],dl[i][j-1]),sum(i,i+k-1,j-k+1,j));
            for(j=m-k+1;j>=1;--j) dr[i][j]=max(max(dr[i+1][j],dr[i][j+1]),sum(i,i+k-1,j,j+k-1));
        }
        for(i=k    ;i<=n;++i) for(j=1;j<m;++j) u[i]=max(u[i],ul[i][j]+ur[i][j+1]);
        for(i=n-k+1;i>=1;--i) for(j=1;j<m;++j) d[i]=max(d[i],dl[i][j]+dr[i][j+1]);
        for(j=k    ;j<=m;++j) for(i=1;i<n;++i) l[j]=max(l[j],ul[i][j]+dl[i+1][j]);
        for(j=m-k+1;j>=1;--j) for(i=1;i<n;++i) r[j]=max(r[j],ur[i][j]+dr[i+1][j]);
        
        for(i=k    ;i<=n;++i) uu[i]=max(ul[i][m],ur[i][1]);
        for(i=n-k+1;i>=1;--i) dd[i]=max(dl[i][m],dr[i][1]);
        for(j=k    ;j<=m;++j) ll[j]=max(ul[n][j],dl[1][j]);
        for(j=m-k+1;j>=1;--j) rr[j]=max(ur[n][j],dr[1][j]);
        
        for(i=k+k;i<=n;++i) for(j=k;j<=m;++j) ulu[i][j]=max(max(ulu[i][j-1],ulu[i-1][j]),sum(i-k+1,i,j-k+1,j)+ul[i-k][j]);
        for(i=k;i<=n;++i) for(j=k+k;j<=m;++j) ull[i][j]=max(max(ull[i][j-1],ull[i-1][j]),sum(i-k+1,i,j-k+1,j)+ul[i][j-k]);
    }
    
    int ans=0;
    
    for(j=1;j<m;++j) ans=max(ans,max(max(ll[j]+r[j+1],l[j]+rr[j+1]),ull[n][j]+dr[1][j+1]));
    
    for(j=1;j<n;++j) ans=max(ans,max(max(uu[j]+d[j+1],u[j]+dd[j+1]),ulu[j][m]+dr[j+1][1]));
    
    cout<<ans;
    
    return 0;
}
