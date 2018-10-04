#include <algorithm>
using namespace std;

typedef long long ll;

#define pardon for(int i=0; i<2; ++i) if(c[i])

struct splay_node {
	splay_node *p, *c[2];
	int val, cnt;
	int minV, maxV;
	ll sumV;
	bool shouldFlip;
	splay_node(splay_node* par, int init_val) : p(par), val(init_val), cnt(1){
		c[0] = c[1] = nullptr;
		sumV = minV = maxV = init_val;
		shouldFlip = false;
	}
	splay_node*& me(){ return p->c[p->c[1] == this]; }
	bool md(){ return p->c[1] == this; }

	void flush(){
		if(shouldFlip){
			swap(c[0], c[1]);
			pardon c[i]->shouldFlip ^= 1;
			shouldFlip = false;
		}
	}

	void reset(){
		cnt = 1; sumV = minV = maxV = val;
		pardon {
			cnt += c[i]->cnt;
			minV = min(minV, c[i]->minV);
			maxV = max(maxV, c[i]->maxV);
			sumV += c[i]->sumV;
		}
	}
};

splay_node *valp[300010];
int n, Q;

struct splay_tree
{
	splay_node *root;

	splay_tree(){ root = nullptr; }

	void rotate(splay_node *pt){
		bool dir = pt->md();
		splay_node *np = pt->p->p;
		((pt->p == root)?root:(pt->p->me())) = pt;
		splay_node *lst = pt->c[!dir];
		pt->c[!dir] = pt->p;
		pt->p->c[dir] = lst;
		if(lst) lst->p = pt->p;
		pt->p->p = pt;
		pt->p = np;

		pt->c[!dir]->reset(); pt->reset();
	}

	void splay(splay_node* node, splay_node*& root){
		while(true){
			if(node == root) break;
			if(node -> p == root){
				rotate(node);
				break;
			} else {
				bool a=node->md(), b=node->p->md();
				if(a == b){
					rotate(node->p); rotate(node);
				} else {
					rotate(node); rotate(node);
				}
			}
		}
	}

	void dfs(splay_node* pt){
		if(!pt) return;
		pt->flush();
		if(pt->c[0]) dfs(pt->c[0]);
		if(pt->val >= 1 && pt->val <= n)
			printf("%d ",pt->val);
		if(pt->c[1]) dfs(pt->c[1]);
	}

	splay_node* find_kth(int k){
		splay_node* pt = root;
		while(true){
			pt->flush();
			if(pt->c[0] && pt->c[0]->cnt >= k){
				pt = pt->c[0];
				continue;
			}
			if(pt->c[0]) k -= pt->c[0]->cnt;
			if(k == 1) return pt;
			--k; pt=pt->c[1];
		}
	}

	splay_node* flip(int L, int R){
		splay(find_kth(L), root);
		splay(find_kth(R+2), root->c[1]);
		auto pt = root->c[1]->c[0];
		pt->shouldFlip ^= 1;
		return pt;
	}
};

splay_tree tree;

splay_node* init(splay_node* par, int l,int r){
	if(l > r) return nullptr;
	int mid = (l+r)/2;
	splay_node *n = new splay_node(par, mid);
	n->c[0] = init(n, l, mid-1);
	n->c[1] = init(n, mid+1, r);
	valp[mid] = n;
	n->reset();
	return n;
}

int main(){
	scanf("%d%d", &n, &Q);
	tree.root = init(nullptr, 0, n+1);
	for(;Q--;){
		int cmd; scanf("%d",&cmd);
		if(cmd == 1){
			int l, r; scanf("%d%d", &l, &r);
			auto pt = tree.flip(l, r);
			printf("%d %d %lld\n", pt->minV, pt->maxV, pt->sumV);
		} else if(cmd == 2){
			int l, r, k; scanf("%d%d%d", &l, &r, &k);
			int dst = r-l+1;
			k = (-k%dst + dst) % dst;
			if(k>=1)
				tree.flip(l, l+k-1);
			if(l+k <= r)
				tree.flip(l+k, r);
			auto pt = tree.flip(l, r);
			printf("%d %d %lld\n", pt->minV, pt->maxV, pt->sumV);
		} else if(cmd == 3){
			int i; scanf("%d", &i);
			printf("%d\n", tree.find_kth(i+1) -> val);
		} else if(cmd == 4){
			int i; scanf("%d", &i);
			vector<splay_node*> v;
			auto pt = valp[i];
			for(;pt;){
				v.push_back(pt);
				pt = pt->p;
			}
			while(v.size()){
				v.back()->flush();
				v.pop_back();
			}
			pt = valp[i];
			int ans = 0;
			if(pt->c[0]) ans = pt->c[0]->cnt;
			for(;;){
				if(pt->p){
					if(pt->md()){
						ans += pt->p->cnt - pt->cnt;
					}
				} else break;
				pt=pt->p;
			}
			printf("%d\n", ans);
		}
	}
	tree.dfs(tree.root);
	return 0;
}
