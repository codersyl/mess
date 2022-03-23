// mapping
// 建图

// 链式向前星存图
// 适合边数较少的稀疏图
int N = , M = N * 2, INF = INT_MAX;
// he 代表第一个边，ne代表下一个边
// 获取某个节点e[i]连接的所有边的方法:
// e[i] 为此节点

// he[node] 为结点node连接的第一个节点的边的序号，令其为e1，则结点为e[e1]
int he[N];
// e[i]，代表编号为i的边的目标结点
// ne[i] 为与边i同源结点的下一条边的编号，如此可得到所有边
// w[i] 为边i的权重，如无必要，则可不设
int e[M], ne[M], w[M];
int idx = 0;	// idx 为边的序号
// 使用前需要
// 1. 
// 建立一条从a到b的有向边
void add(int a, int b, int c) {
	// 把边idx的目标设置为b
	e[idx] = b;
	// 把边idx的下一条边设置为a的第一条边
	ne[idx] = he[a];
	// 取代a的第一条边
	he[a] = idx;
	// 把边的权重设为c，如无权重则把c从形参中删除
	w[idx] = c;
	// 边序号递增
	idx++;
}
// 遍历结点a的所有相连结点
for(int i = he[a]; i != -1; i = ne[i]) {
	// b为与a相连的结点，c为边[a,b]的权重
	int b = e[i], c = w[i];
}