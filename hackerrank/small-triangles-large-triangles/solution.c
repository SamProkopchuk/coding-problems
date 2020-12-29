#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct triangle {
	int a;
	int b;
	int c;
} triangle;

int foursqred_area(const triangle * tr) {
	int perim = tr->a + tr->b + tr->c;
	return perim * (perim - 2 * tr->a) * (perim - 2 * tr->b) * (perim - 2 * tr->c);
}

int cmpf (const triangle * tr1, const triangle * tr2) {
	return foursqred_area(tr1) - foursqred_area(tr2);
}

void sort_by_area(triangle* tr, int n) {
    qsort(tr, n, sizeof(tr[0]), cmpf);
}

int main() {
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
