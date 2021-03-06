struct pt {
	ld x, y;
	pt(): x(0), y(0) {}
	pt(ld _x, ld _y) {
		x = _x, y = _y;
	}
};

bool eq(ld a, ld b) {
	return (fabs(a - b) < eps);
}

pt read_pt() {
	ld a, b;
	cin >> a >> b;
	return pt(a, b);
}

bool operator==(pt a, pt b) {
	return a.x == b.x && a.y == b.y;
}

inline bool operator<(pt a, pt b) {
	return (a.x < b.x) || ((a.x == b.x) && (a.y < b.y));
}

pt operator-(pt p1, pt p2) {
	return pt(p1.x - p2.x, p1.y - p2.y);
}

pt operator+(pt p1, pt p2) {
	return pt(p1.x + p2.x, p1.y + p2.y);
}

ld len(pt a) {
	return sqrt(.0 + sqr(a.x) + sqr(a.y));
}

ld dist(pt p1, pt p2) {
	pt p3 = p1 - p2;
	return sqrt(p3.x * p3.x + p3.y * p3.y);
}

ld operator*(pt p1, pt p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

ld operator%(pt p1, pt p2) {
	return p1.x * p2.y - p2.x * p1.y;
}

ld corner(pt p1, pt p2) {
	return abs(atan2(p1 % p2, p1 * p2));
}

ld polar_corner(pt p1) {
	ld res = atan2(p1.y, p1.x);
	return (res < 0) ? res + 2 * pi : res;
}

pt rotate(pt a, ld w) {
	return pt(a.x * cos(w) - a.y * sin(w), a.x * sin(w) + a.y * cos(w));
}

bool cw(pt a, pt b, pt c) {
	return ((c - a) % (b - a)) > 0;
}

bool ccw(pt a, pt b, pt c) {
	return ((c - a) % (b - a)) < 0;
}

struct line {
	ld a, b, c;
	line(): a(0), b(0), c(0) {}
	line(ld x, ld y, ld z) {
		a = x, b = y, c = z;
	}
};

line segment2line(pt p1, pt p2) {
	ld a = p1.y - p2.y, b = p2.x - p1.x;
	return line(a, b, -(a * p1.x + b * p1.y));
}

bool pt_in_line(line l, pt c) {
	return eq(l.a * c.x + l.b * c.y + l.c, 0);
}

bool pt_in_arrow(pt a, pt b, pt c) {
	return pt_in_line(segment2line(a, b), c) && ((b - a) * (c - a)) >= 0;
}

bool pt_in_segment(pt a, pt b, pt c) {
	pt ab = b - a, ac = c - a;
	pt ba = a - b, bc = c - b;
	return eq(ab % ac, 0) && (ab * ac >= 0) && (bc * ba >= 0);
}

bool intersect_p(ld a, ld b, ld c, ld d) {
	return max(a, b) >= min(c, d) && max(c, d) >= min(a, b);
}

bool intersect(pt a, pt b, pt c, pt d) {
	ld v1 = (b - a) % (c - a); //sin(ab, ac)
	ld v2 = (b - a) % (d - a); //sin(ab, ad)
	ld v3 = (d - c) % (a - c); //sin(cd, ca)
	ld v4 = (d - c) % (b - c); //sin(cd, cb)
	if (eq(v1, 0) && eq(v2, 0) && eq(v3, 0) && eq(v4, 0)) //in the same line?
		return intersect_p(a.x, b.x, c.x, d.x) && intersect_p(a.y, b.y, c.y, d.y); //proections
	else
		return (v1 * v2 <= 0) && (v3 * v4 <= 0);
}

bool parallel(line m, line n) {
	return eq(m.a * n.b - m.b * n.a, 0);
}

bool equivalent(line m, line n) {
	return parallel(m, n) && eq(m.a * n.c - m.c * n.a, 0) && eq(m.b * n.c - m.c * n.b, 0);
}

int lines_intersection(line m, line n, pt &res) {
	if (parallel(m, n))
		if (equivalent(m, n))
			return 2;
		else
			return 0;
	ld zn = m.a * n.b - m.b * n.a;
	res.x = (m.b * n.c - m.c * n.b) / zn;
	res.y = (m.c * n.a - m.a * n.c) / zn;
	return 1;
}

int arrows_intersection(pt a, pt b, pt c, pt d, pt &res) {
	line l1 = segment2line(a, b), l2 = segment2line(c, d);
	switch(lines_intersection(l1, l2, res)) {
		case 1: {
			if (((b - a) * (res - a)) >= -eps && ((d - c) * (res - c)) >= -eps)
				return 1;
			break;
		}
		case 2: {
			if (((b - a) * (d - c)) >= -eps || ((b - a) * (c - a)) >= -eps)
				return 2;
			break;
		}
	}
	return 0;
}

int segments_intersection(pt a, pt b, pt c, pt d, pt &p1, pt &p2) {
	if (!intersect(a, b, c, d))
		return 0;
	line l1 = segment2line(a, b), l2 = segment2line(c, d);
	if (!equivalent(l1, l2)) {
		lines_intersection(l1, l2, p1);
		return 1;
	}
	vector<pt> p;
	p.push_back(a);
	p.push_back(b);
	p.push_back(c);
	p.push_back(d);
	sort(p.begin(), p.end(), compare_pt);
	p1 = p[1], p2 = p[2];
	if (p1.x == p2.x && p1.y == p2.y)
		return 1;
	return 2;
}