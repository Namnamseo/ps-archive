#include <cstdio>

int gcd(int a,int b) { return b?gcd(b,a%b):a; }

bool chk[2010][2010];

int main()
{
    int a,b,c;
    scanf("%d%d",&a,&b);
    int ans=0;
    int p,q,g;
    for(;a<=b;++a){
        for(c=1;c<a;++c){
            p=a, q=c;
            g=gcd(p,q);
            p/=g; q/=g;
            if(!chk[p][q]){
                chk[p][q]=true; ++ans;
            }
        }
    }
    printf("%d\n",ans+1);
    return 0;
}
