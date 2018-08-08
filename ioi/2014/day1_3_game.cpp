int c[1510];
void initialize(int n) {};
int hasEdge(int u,int v) {
    return ++c[u=u>v?u:v]==u;
}
