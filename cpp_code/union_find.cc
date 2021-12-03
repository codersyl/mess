// 并查集

int SIZE = (int) 1e5 + 10;
int p[SIZE];
for(int i = 0; i < SIZE; ++i)
    p[i] = i;


int find(int x) {
    if(p[x] != x)   p[x] = find(p[x]);
    return p[x];
}


void union(int a, int b) {
    p[find(a)] = p[find(b)];
}


bool query(int a, int b) {
    return find(a) == find(b);
}