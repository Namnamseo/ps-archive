#include <cstdio>
 
const int inf = 2147480000;
 
struct Node {
    int rangel,ranger;
    Node *lc, *rc;
    int minval,maxval;
    Node(int left,int right) {
        minval=0; maxval=inf;
        rangel = left; ranger = right;
        if(left==right) {
            maxval=0;
            return;
        }
        int mid = (left+right)>>1;
        lc = new Node(left,mid);
        rc = new Node(mid+1,right);
    }
    void applyRange(int nmin,int nmax){
        if(minval<nmin){
            minval = nmin;
            if(maxval<nmin) maxval=nmin;
        }
        if(nmax<maxval){
            maxval=nmax;
            if(nmax<minval) minval=nmax;
        }
    }
    void updateRange(int l,int r,int newmin,int newmax){
        if(l<=rangel && ranger <= r){
            applyRange(newmin,newmax);
        } else {
            if(r<rangel || ranger < l) return;
            lc->applyRange(minval,maxval);
            rc->applyRange(minval,maxval);
            minval=0; maxval=inf;
            lc->updateRange(l,r,newmin,newmax);
            rc->updateRange(l,r,newmin,newmax);
        }
    }
    int answer(int pos){
        if(pos==rangel && pos==ranger) return minval;
        int ret = ((pos<=((rangel+ranger)/2))?lc:rc)->answer(pos);
        if(ret<minval) return minval;
        if(maxval<ret) return maxval;
        return ret;
    }
};

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    Node* root = new Node(0,2097151);
    int i;
    int op,left,right,height;
    for(i=0;i<k;i++) {
    	scanf("%d%d%d%d",&op,&left,&right,&height);
        if(op==1) root->updateRange(left,right,height,inf);
        else root->updateRange(left,right,0,height);
    }
    for(i=0;i<n;i++){
        printf("%d\n",root->answer(i));
    }
    return 0;
}