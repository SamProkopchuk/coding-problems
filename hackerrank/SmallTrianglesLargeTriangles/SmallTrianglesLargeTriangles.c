#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

int cmpf (const void * triangle1, const void * triangle2) { // a and b are triangles
    triangle * tr1 = (triangle*) triangle1;
    triangle * tr2 = (triangle*) triangle2;
    int stretched_area_1 = 0, stretched_area_2 = 0, p1, p2;
    p1 = tr1->a + tr1->b + tr1->c;
    p2 = tr2->a + tr2->b + tr2->c;
    stretched_area_1 = p1*(p1-2*tr1->a)*(p1-2*tr1->b)*(p1-2*tr1->c);
    stretched_area_2 = p2*(p2-2*tr2->a)*(p2-2*tr2->b)*(p2-2*tr2->c);
    return stretched_area_1 - stretched_area_2;
}

void sort_by_area(triangle* tr, int n) {
    qsort(tr, n, sizeof(tr[0]), cmpf);
}

int main()
{
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
