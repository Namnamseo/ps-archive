#include <bits/stdc++.h>
using namespace std;
using pp=pair<int,int>;
using pic=vector<pp>;
#define x first
#define y second
#define pb push_back
#define eb emplace_back

pic a, b, c;
pp oa, ob, oc;

pp operator+(pp a, pp b){ return {a.x+b.x, a.y+b.y}; }
pp operator-(pp a, pp b){ return {a.x-b.x, a.y-b.y}; }

void read_pic(pic &v, pp &off){
	int n, m;
	cin >> n >> m;
	pp s; bool e=0;
	for(int i=0; i<n; ++i){
		static char buf[1010];
		cin >> buf;
		for(int j=0; j<m; ++j) if(buf[j]=='*'){
			if(!e){ e=1; s=off={i, j}; }
			v.eb(pp(i, j)-s);
		}
	}
}

pp last_res;

pic overlap(pic va, pic vb){
	va.insert(va.end(), vb.begin(), vb.end());
	sort(va.begin(), va.end());
	pic ret;
	int sz = va.size();

	for(int i=0; i<sz;){
		if(i+1<sz && va[i] == va[i+1]){
			i += 2;
			continue;
		}
		ret.pb(va[i]);
		++i;
	}

	if(ret.size()){
		last_res = ret[0];
		for(auto& tmp:ret) tmp = tmp - last_res;
	}

	return ret;
}

int main(){
	read_pic(a, oa);
	read_pic(b, ob);
	read_pic(c, oc);

#define x second
#define y first

	if(overlap(overlap(a, b), c).empty()){
		printf("YES\n%d %d\n", oa.x-ob.x, oa.y-ob.y);
	} else if(overlap(a, overlap(b, c)).empty()){
		pp tmp = oa-last_res-ob;
		printf("YES\n%d %d\n", tmp.x, tmp.y);
	} else if(overlap(overlap(c, a), b).empty()){
		pp tmp = oa+last_res-ob;
		printf("YES\n%d %d\n", tmp.x, tmp.y);
	} else puts("NO");
	return 0;
}
