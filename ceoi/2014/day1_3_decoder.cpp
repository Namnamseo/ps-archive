int c[30][30];

void build_table() {
    int i,j;
    c[0][0]=1;
    for(i=1;i<30;++i){
        c[i][0]=1; c[i][i]=1;
        for(j=1;j<i;++j) c[i][j]=c[i-1][j-1]+c[i-1][j];
    }
}

void build_array(int value,bool chk[12]){
    int i;
    for(i=0;i<12;++i) chk[i]=0;
    int now_left = 6;
    for(i=0;i<12;++i){
        if(value > c[11-i][now_left]){
            value -= c[11-i][now_left--];
            chk[i]=1;
        }
    }
}

int decode (int n, int q, int h) {
	bool qt[12];
	build_array(q,qt);
	return qt[h-1];
}
