#include "memory2.h"
#include <vector>
#include <set>
#include <map>
using namespace std;

bool chk[100][100];
int  ret[100][100];

int flip(int a,int b){
    if(a>b) swap(a, b);
    int& ret=::ret[a][b];
    if(chk[a][b]) return ret;
    chk[a][b]=1;
    return ret = Flip(a, b);
}

void Solve(int T, int n){
    set<int> mxpt;
    mxpt.insert(0);
    mxpt.insert(1);
    
    vector<vector<int>> ans(n);
    
    for(int i=2; i<2*n; ++i){
        mxpt.insert(i);
        vector<int> pts(mxpt.begin(), mxpt.end());
        int k=pts.size();
        set<int> vars[k];
        set<int> szs;
        for(int a=0; a<k; ++a){
            for(int b=0; b<k; ++b) if(a!=b){
                vars[a].insert(flip(pts[a], pts[b]));
            }
            szs.insert(vars[a].size());
        }
        if(szs.size() == 1){
            continue;
        }
        mxpt.clear();
        for(int a=0; a<k; ++a){
            if(vars[a].size() != 1u) mxpt.insert(pts[a]);
            else ans[*vars[a].begin()].push_back(pts[a]);
        }
    }
    
    int a=*mxpt.begin(), b=*--mxpt.end();
    ans[flip(a,b)].push_back(a);
    ans[flip(a,b)].push_back(b);
    for(int i=0; i<n; ++i){
        Answer(ans[i][0], ans[i][1], i);
    }
	return;
}
