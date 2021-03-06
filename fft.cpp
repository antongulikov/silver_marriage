const int MAXK = 18;
const int MAXN = 1 << MAXK;				   

struct comp {
	ld x, y;
	
	comp() {};
	comp(ld _x, ld _y): x(_x), y(_y) {};
	comp(ld _x) {
		x = _x;
		y = 0;
	}
	
	ld real() {
		return x;	
	}	
	ld image() {
		return y;	
	}
	
	void operator+=(comp a) {
		x += a.x;
		y += a.y;	
	}		
	void operator/=(ld k) {
		x /= k;
		y /= k;	
	}
};

inline comp operator+(comp a, comp b) {
	return comp(a.x + b.x, a.y + b.y);
}

inline comp operator-(comp a, comp b) {
	return comp(a.x - b.x, a.y - b.y);
}

inline comp operator*(comp a, comp b) {
	return comp(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
}

typedef vector<comp> polynom;

int inv(int n) {
	int res = 0;
	forn(i, MAXK)
		res |= ((n >> (MAXK - i - 1)) & 1) << i;
	return res;
}

void fft(polynom &a, bool invert) {
	int n = a.size();
	if (n == 1)
		return;
		
	forn(i, n)
		if (i < inv(i))	
			swap(a[i], a[inv(i)]);
			
	for (int len = 2; len <= n; len <<= 1) {
		ld angle = pi * 2 / len * (invert ? -1 : 1);
		comp w, wn(cos(angle), sin(angle));
	
		for (int i = 0; i < n; i += len) {
			w = 1;
			for (int j = 0; j < len / 2; j++) {
				comp a0 = a[i + j], a1 = a[i + j + len / 2];
				a[i + j] = a0 + w * a1;
				a[i + j + len / 2] = a0 - w * a1;
				
				w = w * wn;
			}
		}	
	}
	
	if (invert)
		forn(i, n)
			a[i] /= n;
}

vi multiply(vi a, vi b) {
	polynom fa(a.size()), fb(b.size()), fc(a.size());
	forn(i, a.size())
		fa[i] = a[i];
	forn(i, b.size())
		fb[i] = b[i];
	
	fft(fa, 0);
	fft(fb, 0);
	forn(i, fc.size())
		fc[i] = fa[i] * fb[i];
	fft(fc, 1); 
	
	vi res(fc.size());
	forn(i, fc.size())
		res[i] = fc[i].real() + 0.5;		
	
	return res;
}
