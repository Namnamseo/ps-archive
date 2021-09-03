#include <cstdio>
#include <vector>
#include "library.h"
using namespace std;

int nok[1010], nn;

void Solve(int N)
{
    vector<int> M(N, 1);
    if(N == 1){
        Answer(M);
        return;
    }

    int left;

    for(left = 0; left < N; ++left){
        M[left] = 0;
        if(Query(M) == 1) break;
        M[left] = 1;
    }

    vector<int> ans(N);
    ans[0]=left+1;

    for(int i=0; i<N; ++i) if(i != left) nok[nn++] = i;

    fill(M.begin(), M.end(), 0);
    for(int i=1; i<N; ++i){
        int l=0, r=nn;
        while(l+1 < r){
            int mid=(l+r)/2;
            for(int i=l; i<mid; ++i) M[nok[i]] = 1;
            int res1 = Query(M);
            M[ans[i-1]-1] = 1;
            int res2 = Query(M);
            for(int i=l; i<mid; ++i) M[nok[i]] = 0; M[ans[i-1]-1]=0;
            if(res1 == res2) r=mid;
            else l=mid;
        }
        ans[i] = nok[l]+1;
        swap(nok[nn-1], nok[l]); --nn;
    }

    Answer(ans);
}
