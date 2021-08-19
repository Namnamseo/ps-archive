#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define ind(x,y) lower_bound(all(x), y) - x.begin() + 1

const int M = 524288;

int tree[M<<1];
void upd(int l,int r,int v){
    l+=M; r+=M;
    while(l<=r){
        if(l%2==1) tree[l++]+=v;
        if(r%2==0) tree[r--]+=v;
        l>>=1; r>>=1;
    }
}

int get(int x){
    x+=M; int ret=0;
    while(x) ret+=tree[x], x>>=1;
    return ret;
}

vector<int> yp;

int qtype[200010];
int qx[200010];
int qy[200010];
int n, q;

int val[200010];

void treat(int pos,int dt){
    int a=val[pos], b=val[pos+1];
    a=ind(yp, a); b=ind(yp, b);
    if(a>b) upd(b+1, a, dt);
}

int main()
{
    yp.pb(0);
    scanf("%d%d",&n, &q);
    for(int i=1; i<=n; ++i){
        scanf("%d", val+i);
        yp.pb(val[i]);
    }

    for(int i=1; i<=q; ++i){
        scanf("%d", qtype+i);
        if(qtype[i] == 1){
            scanf("%d", qx+i);
        } else {
            scanf("%d", qx+i);
            scanf("%d", qy+i);
            yp.pb(qy[i]);
        }
    }

    sort(all(yp));
    yp.erase(unique(all(yp)), yp.end());

    for(int i=1; i<=n; ++i){
        treat(i, 1);
    }

    for(int i=1; i<=q; ++i){
        if(qtype[i] == 1){
            int a=ind(yp, qx[i]);
            printf("%d\n", get(a));
        } else {
            int a=qx[i], b=qy[i];
            if(1<a) treat(a-1, -1);
            treat(a, -1);
            val[a]=b;
            if(1<a) treat(a-1, 1);
            treat(a, 1);
        }
    }
    return 0;
}
