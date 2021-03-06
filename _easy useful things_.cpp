File Assotiation of *.cpp:
g++ !.cpp -o !.exe -O2 -DLOCAL -Wall -Wextra -Dsome -std=c++11 -static-libstdc++ -D DEBUG

//my set with blackjack
struct a
{
        int key;
        a(){}
        a(int key):key(key){}
        bool operator <(a const &tmp) const
        {
                return key < tmp.key;
        }
        bool operator ==(a const &tmp) const
        {
                return key == tmp.key;
        }
};
 
set <a> q;

//how to unique
int n = unique(a.begin(), a.end()) - a.begin();
a.resize(n);    

//enlarge your stack
#pragma comment(linker, "/STACK:16777216")

//����������� �������
f[0][0] = 1;
FORN(i, 1, n) {
    f[i][0] = 1;
    FORN(j, 1, i)
        f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
}

//������ ���������
vector<int> num, assoc;

void compress() {
    sort(all(num));
    assoc.push_back(num[0]);
    for (int i = 1; i < num.size(); i++)
        if (num[i - 1] != num[i])
            assoc.push_back(num[i]);
}

<...>

    compress();
    for (int i = 0; i < num.size(); i++)
        cout << lower_bound(all(assoc), num[i]) - assoc.begin() << endl;

//�������� ����������
int a[MAXN], b[MAXN], cnt[base];
int n, *curr = &a[0], *prev = &b[0];
int64 divby;
bool sorted;

inline int num(int x) {
	return ((x / divby) % base);
}

<...>
	sorted = 0;
	divby = 1;
	while (!sorted) {
		swap(prev, curr);
		memset(cnt, 0, base * sizeof(int));
		for (int i = 0; i < n; i++)
			cnt[num(prev[i])]++;
		for (int i = 1; i < base; i++)
			cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; i--)
			curr[--cnt[num(prev[i])]] = prev[i];

		divby *= base;
		sorted = 1;
		for (int i = 0; i < n; i++)
			sorted &= (curr[i] < divby);
	}