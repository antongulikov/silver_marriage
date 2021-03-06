int rt[MAXN], rk[MAXN];

void make_set(int v) {
	rt[v] = v;
}

int find_set(int v) {
	if (rt[v] != v)
		rt[v] = find_set(rt[v]);
	return rt[v];
}

void union_set(int a, int b) {
	int x = find_set(a);
	int y = find_set(b);
	if (x != y) {
		if (rk[x] > rk[y])
			rt[y] = x;
		else
			rt[x] = y;
		if (rk[x] == rk[y])
			rk[y]++;
	}
}