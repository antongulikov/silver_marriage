program qsort;

const
	MaxN = 100000;

type
	int = longint;
	MyArray = Array[1..MaxN] of int;

var
	N, q: int;
	Arr: MyArray;

procedure swap(var x1, x2: int);
var
	x3: int;
begin
	x3 := x1;
	x1 := x2;
	x2 := x3;
end;

procedure Quicksort(var a: MyArray; l, r: int);
var
	i, j: int;
	x: int;
begin
	if l >= r then exit;
	i := l;
	j := r;
	x := a[l + random(r - l + 1)];
	repeat
		while a[i] < x do
			inc(i);
		while a[j] > x do
			dec(j);
		if i <= j then begin
			swap(a[i], a[j]);
			inc(i);
			dec(j);
		end;
	until i > j;
	Quicksort(a, i, r);
	Quicksort(a, l, j);
end;

begin

	readln(N);

	for q := 1 to N do
		read(Arr[q]);
	
	Quicksort(Arr, 1, N);

	for q := 1 to N do
		write(Arr[q], ' ');

	close(input);
	close(output);
end.