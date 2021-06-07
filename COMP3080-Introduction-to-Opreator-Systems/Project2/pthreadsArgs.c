#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct rowcol {
	int row;
	int col;
} parameters;

void *test(void * args) {
	struct rowcol a = *((struct rowcol *) args);
	struct rowcol *b = ((struct rowcol *) args);
	parameters c = *((parameters *) args);
	parameters *d = ((parameters *) args);

	printf("struct rowcol a row: %d col %d\n", a.row, a.col);	
	printf("struct rowcol *b row: %d col %d\n", b->row, b->col);	
	printf("parameters c row: %d col %d\n", c.row, c.col);	
	printf("parameters *d row: %d col %d\n", d->row, d->col);	
}

int main() {
	pthread_t p, q, r, s;

	struct rowcol a;
	struct rowcol *b = (struct rowcol *) malloc(sizeof(struct rowcol));
	parameters c;
	parameters *d = (struct rowcol *) malloc(sizeof(struct rowcol));
	
	a.row = 1;
	a.col = 2;
	b->row = 3;
	b->col = 4;
	c.row = 5;
	c.col = 6;
	d->row = 7;
	d->col = 8;

	pthread_create(&p, 0, test, &a);
	pthread_create(&q, 0, test, b);
	pthread_create(&r, 0, test, &c);
	pthread_create(&s, 0, test, d);

	pthread_join(p, 0);
	pthread_join(q, 0);
	pthread_join(r, 0);
	pthread_join(s, 0);
}
