#include <cstdio>

const int M=1000010;

char letter[M];    /// access by state
int depth[M];      /// access by state
int parent[M][21]; /// access by state
int state[M];      /// access by command

int coms, stats;

void Init(){
}

void TypeLetter(char x){
	coms++; stats++;
	 state[coms ]=stats;
	letter[stats]=x;
	int myp = state[coms-1];
	parent[stats][0]=myp;
	depth[stats]=depth[myp]+1;
	int i;
	for(i=1;i<=20;i++){
		parent[stats][i]=parent[parent[stats][i-1]][i-1];
	}
}

void UndoCommands(int x){
	coms++;
	state[coms]=state[coms-1-x];
}

char GetLetter(int pos){
	int cur=state[coms];
	pos = depth[cur]-pos-1;
	int i;
	for(i=0;i<=20;i++){
		if(pos&(1<<i)){
			cur = parent[cur][i];
		}
	}
	return letter[cur];
}