#include <bits/stdc++.h>
using namespace std;

int read_token(){
	static char buf[100];
	if(scanf("%s", buf) < 1) return -1;
	if(buf[0] == 'x') return -10;
	if(buf[0] == '>') return -20;
	if(buf[0] == '<') return -30;
	if(buf[0] == '&') return -40;
	if(buf[0] == '|') return -50;
	static int ret; sscanf(buf, "%d", &ret);
	return ret + 32768;
}

using pp=pair<int,int>;
#define x first
#define y second
pp inter(pp a, pp b){ return {max(a.x, b.x), min(a.y, b.y)}; }

bool is_end;

pp read_eq(){
	pp ret(-32768, 32767);
	bool ijou = 0;
	while(true){
		int t = read_token();
		if(t == -1){ is_end = 1; break; }
		if(t == -50) break;
		if(t == -40) continue;
		if(t == -10) continue;
		if(t == -20) ijou = 1;
		if(t == -30) ijou = 0;
		if(t < 0) continue;
		t -= 32768;
		if(ijou) ret = inter(ret, pp(t, 32767));
		else ret = inter(ret, pp(-32768, t));
	}
	if(ret.x > ret.y) ret.y = ret.x-1;
	return ret;
}

int s[65537];

vector<pp> av;

#define eb emplace_back

int main(){
	while(!is_end){
		int x, y; tie(x, y) = read_eq();
		s[x+32768] += 1;
		s[y+32768+1] -= 1;
	}

	int lev = 0;
	int lst = -1;
	for(int i=0; i<65536; ++i){
		int nl = lev + s[i];
		if(lev == 0 && nl){
			lst = i;
		} else if(lev && !nl){
			av.eb(lst, i-1);
			lst = -1;
		}
		lev = nl;
	}

	if(lst != -1) av.eb(lst, 65535);

	if(av.empty()){ puts("false"); return 0; }
	if(av.size() == 1u && av[0] == pp(0, 65535)){ puts("true"); return 0; }

	for(auto tmp:av){
		int x, y; tie(x, y) = tmp;
		x -= 32768; y -= 32768;
		if(x == -32768)
			printf("x <= %d", y);
		else if(y == 32767)
			printf("x >= %d", x);
		else
			printf("x >= %d && x <= %d",x, y);
		if(tmp == av.back()){
			puts("");
		} else {
			puts(" ||");
		}
	}

	return 0;
}

