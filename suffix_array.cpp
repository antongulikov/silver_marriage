string s;
int n, l, j, old_a[MAXN], new_a[MAXN], old_color[MAXN], new_color[MAXN];
int cnt[MAXN], h[MAXN];
int *a, *b, *clr_a, *clr_b;

<...>

	a = &old_a[0];
	b = &new_a[0];
	clr_a = &old_color[0];
	clr_b = &new_color[0];
	
	cin >> s;
	n = s.size();
	forn(i, n)
		a[i] = s[i];

	forn(i, MAXN)
		cnt[i] = 0;
	forn(i, n) {
		cnt[a[i]]++;
		clr_a[i] = a[i];
	}
	h[0] = 0;
	forab(i, 1, MAXN)
		h[i] = h[i - 1] + cnt[i - 1];
	forn(i, n) 
		a[h[clr_a[i]]++] = i;

	h[0] = 0;
	forab(i, 1, MAXN)
		h[i] = h[i - 1] + cnt[i - 1];

	l = 1;
	while (l < n) {
		forn(i, n) {
			j = (2 * n + a[i] - l) % n;
			b[h[clr_a[j]]] = j;
			h[clr_a[j]]++;
		}
		clr_b[b[0]] = 0;
		h[0] = 0;
		forab(i, 1, n) {
			if (clr_a[b[i]] == clr_a[b[i - 1]] && clr_a[(b[i] + l) % n] == clr_a[(b[i - 1] + l) % n])
				clr_b[b[i]] = clr_b[b[i - 1]];
			else {
				clr_b[b[i]] = clr_b[b[i - 1]] + 1;
				h[clr_b[b[i]]] = i;
			}
		}

		swap(a, b);
		swap(clr_a, clr_b);
		l <<= 1;
	}