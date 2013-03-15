#ident "$Id: schwarz.c,v 3.27 2002-01-06 16:36:03+02 rl Exp $"
/*
 *****************************************************************************
 * kaleido
 *
 *	Kaleidoscopic construction of uniform polyhedra
 *	Copyright © 1991-2002 Dr. Zvi Har'El <rl@math.technion.ac.il>
 *
 *	Redistribution and use in source and binary forms, with or without
 *	modification, are permitted provided that the following conditions
 *	are met:
 *
 *	1. Redistributions of source code must retain the above copyright
 *	   notice, this list of conditions and the following disclaimer.
 *
 *	2. Redistributions in binary form must reproduce the above copyright
 *	   notice, this list of conditions and the following disclaimer in
 *	   the documentation and/or other materials provided with the
 *	   distribution.
 *
 *	3. The end-user documentation included with the redistribution,
 *	   if any, must include the following acknowledgment:
 *		"This product includes software developed by
 *		 Dr. Zvi Har'El (http://www.math.technion.ac.il/~rl/)."
 *	   Alternately, this acknowledgment may appear in the software itself,
 *	   if and wherever such third-party acknowledgments normally appear.
 *
 *	This software is provided 'as-is', without any express or implied
 *	warranty.  In no event will the author be held liable for any
 *	damages arising from the use of this software.
 *
 *	Author:
 *		Dr. Zvi Har'El
 *		Department of Mathematics,
 *		Technion, Israel Institute of Technology,
 *		Haifa 32000, Israel.
 *		E-Mail: rl@math.technion.ac.il
 *****************************************************************************
 */
#include <stdio.h>
#include <math.h>
#ifndef MAXLONG
#define MAXLONG 0x7FFFFFFF
#endif
typedef struct Trian {
    int density;
    char index[2];
    double p[3];
    int a[3][3];
    struct Sum *sum;
    struct Trian *next;
} Trian;
typedef struct Sum {
    struct Trian *left, *right;
    struct Sum *next;
} Sum;

Trian* moebius(int n);
void units (int n);
double peri(Trian *result);
void install(Trian *head, Trian *trian, Trian *left, Trian *right);
Trian* add (Trian *left, Trian *right);
void push(Trian *trian, double p, int a[3]);
void side(int a[3]);
void frac(double x);
double combine (double x, double y);
void printfrac (double x);
void printpi(double x);

int
main(int argc, char **argv)
{
    int n;
    for (n = 3; n <= 5; n++) {
	Trian *u, *v, *head, *moebius(), *sorted = 0;
	Sum *s;
	int index = 0;
	static char *names[3] = {"Tetr", "Oct", "Icos"};
	char *name = names[n-3];
	printf("%sahedral Schwarz Triangles\n\n", name);
	units(n);
/*
 * generate the triangles
 */
	head = moebius(n);
	for(u = head; u; u = u->next) {
	    for(v = head; v != u->next; v=v->next) {
		Trian *result, *add(), *next;
		for (result = add(u, v); result; result = next) {
		    next = result->next;
		    install(head, result, u, v);
		}
	    }
	}
/*
 * sort the triangles  by increasing density and perimeter
 */
	for (u = head; u; u = v) {
	    double peri();
	    Trian **z;
	    for (z = &sorted; *z && ((*z)->density < u->density ||
			(*z)->density == u->density && peri(*z) < peri(u));
		    z = &(*z)->next)
		;
	    v = u->next;
	    u->next = *z;
	    *z = u;
	}
/*
* print the triangles and splittings
*/
	for (u = sorted; u; u = u->next) {
	    int i;
	    if (index)
		index++;
	    else if (u->next && u->next->density == u->density)
		index='a';
	    u->index[0] = index;
	    u->index[1] = 0;
	    printf("\n%c%d%s", *name, u->density, u->index);
	    printf("\t( ");
	    for (i = 0; i < 3; i++){
		printfrac(u->p[i]);
		putchar(' ');
	    }
	    printf("; ");
	    for (i = 0; i < 3; i++)
		side(u->a[i]);
	    printf(")\n\t");
	    if (u->next && u->next->density != u->density)
		index = 0;
	    for (s = u->sum; s; s = s->next)
		if (s->left != s->right)
		    printf("\t%c%d%s+%c%d%s", *name, s->left->density,
			    s->left->index, *name, s->right->density,
			    s->right->index);
		else
		    printf("\t2%c%d%s", *name, s->left->density,
			    s->left->index);
	    putchar('\n');
	}
/*
 * free the list
 */
	for (u = sorted; u; u = v) {
	    v = u->next;
	    free(u);
	}
	if (n < 5)
	    putchar('\f');
    }
    exit(0);
}

/*
 * generate a moebius triangle
 */
Trian*
moebius(int n)
{
    static int a[3][3][3] = {
	{{0, 1, 0}, {0, 1, 0}, {4, -2, 0}},
	{{2, -1, 0}, {1, 0, 0}, {0, 1, 0}},
	{{0, 1, 0}, {0, 0, 1}, {2, -1, -1}}
    };
    int i, j;
    Trian *u;
    u = (Trian*) malloc(sizeof(Trian));
    u->density = 1;
    u->p[0] = n;
    u->p[1] = 3;
    u->p[2] = 2;
    for(i = 0, j = 0; i < 3; ++j < 3 || (j = 0, i++))
	u->a[i][j] = a[n-3][i][j];;
    u->sum = 0;
    u->next = 0;
    return u;
}

double unit_length[3];
char unit_name[2] = {'s', 'v'};

/*
 * Initialize unit lengths (used by peri()) and names (used by side()).
 */
void
units (int n)
{
    double acos(), sqrt();
    if (n == 3) { /* pi/4 and s */
	unit_length[0] = acos(0.) / 2;
	unit_length[1] = acos(-1. / 3) / 2;
    } else if (n == 5) { /* u and v */
	unit_length[1] = acos(sqrt(5.) / 3) / 2;
	unit_length[2] = acos(sqrt(5.) / 5) / 2;
	unit_name[0] = 'u';
    }
}

/*
 * compute the perimeter of a triangle
 */
double
peri(Trian *result)
{
    int i,j;
    double x = 0;
    for(i = 0, j = 0; i < 3; ++j < 3 || (j = 0, i++))
	x += result->a[i][j] * unit_length[j];
    return x;
}

/*
 * install a triangle and a splitting in list
 */
void
install(Trian *head, Trian *trian, Trian *left, Trian *right)
{
    Trian **z;
    Sum *s, **t;
    int i;
/*
 * if not convex triangle, nothing to do
 */
    if (trian->p[2] <= 1) {
	free(trian);
	return;
    }
/*
 * generate a Sum structure to hold splitting
 */
    trian->next = 0;
    s = (Sum*)malloc(sizeof(Sum));
    s->left = left;
    s->right = right;
    s->next = 0;
/*
 * look if triangle already there
 */
    for (z = &head->next; *z; z = &(*z)->next) {
	if ((*z)->density != trian->density)
	    continue;
	for (i = 0; i < 3 && (*z)->p[i] == trian->p[i]; i++)
	    ;
	if (i == 3)
	    break;
    }
    if (*z) {
	free(trian);
/*
* look if splitting already there
*/
	for (t = &(*z)->sum;
		*t && ((*t)->left != left || (*t)->right != right);
		t = &(*t)->next)
	    ;
	if (*t)
	    free(s);
	else
	    *t = s;
    } else {
/*
* insert new triangle and splitting
*/
	trian->next = *z;
	trian->sum = s;
	*z = trian;
    }
}

/*
 * paste two triangles together
 */
Trian*
add (Trian *left, Trian *right)
{
    Trian *result = 0;
    int i, j;
    for(i = 0, j = 0; i < 3; ++j < 3 || (j=0, i++)) {
/*
 * check if angles are complementary
*/
	double combine();
	int k, l;
	if (combine(left->p[i], right->p[j]) != 1)
	    continue;
	for (k = 1, l = 1; k < 3; ++l < 3 || (l = 1, k++)) {
	    int a[3], m;
	    Trian *u, **z;
/*
 * check if sides are equal
 */
	    for (m = 0; m < 3 && left->a[(i + k) % 3][m] ==
		    right->a[(j + l) % 3][m]; m++)
		;
	    if (m < 3)
		continue;
/*
 * generate the new triangle, with sorted angles and sides
 */
	    u = (Trian*) malloc(sizeof (Trian));
	    u->density = left->density + right->density;
	    u->p[0] = 0;
	    push(u, right->p[(j + l) % 3], left->a[i]);
	    push(u, left->p[(i + k) % 3], right->a[j]);
	    for (m = 0; m < 3; m++)
		a[m] = left->a[(i + 3 - k) % 3][m] +
			right->a[(j + 3 - l) % 3][m];
	    push(u, combine(left->p[(i + 3 - k) % 3],
			right->p[(j + 3 - l) % 3]), a);
	    u->next = 0;
/*
 * check if it is really new
 */
	    for (z = &result; *z; z = &(*z)->next) {
		for (m = 0; m < 3 && u->p[m] == (*z)->p[m]; m++)
			;
		if (m == 3)
		    break;
	    }
	    if (*z)
		free(u);
/*
 * add it to the list of results
 */
	    else
		*z = u;
	}
    }
    return result;
}

/*
 * insert angles and sides in order
 */
void
push(Trian *trian, double p, int a[3])
{
    int i, j;
    for (i = 0; i < 3 && trian->p[i] >= p; i++)
	;
    for (j = 2; j > i; j--) {
	int k;
	trian->p[j] = trian->p[j - 1];
	for (k = 0; k < 3; k++)
	    trian->a[j][k] = trian->a[j - 1][k];
    }
    trian->p[i] = p;
    for (j = 0; j < 3; j++)
	trian->a[i][j] = a[j];
}

/*
 * print the symbolic expression for a side
 */
void
side(int a[3])
{
    int i, j = a[0];
    printpi(j / 4.);
    for(i = 1; i < 3; i++){
	if (!a[i])
	    continue;
	if(j && a[i] > 0)
	    putchar('+');
	j = 1;
	if (a[i] == -1)
	    putchar('-');
	else if (a[i] != 1)
	    printf("%d", a[i]);
	putchar(unit_name[i - 1]);
    }
    putchar(' ');
}

typedef struct {
    long n, d;
} Fraction;
Fraction frax;

/*
 * Find the numerator and the denominator using the Euclidean algorithm.
 */
void
frac(double x)
{
    static Fraction zero = {0,1}, inf = {1,0};
    Fraction r;
    double s = x;
    r = zero;
    frax = inf;
    for(;;) {
	Fraction q;
	long f;
	double floor();
	if (fabs(s) > (double) MAXLONG)
	    return;
	f = (long) floor(s);
	q = r;
	r = frax;
	frax.n = frax.n * f + q.n;
	frax.d = frax.d * f + q.d;
	if (x == (double) frax.n / (double) frax.d)
	    return;
	s = 1 / (s - f);
    }
}

/*
 * compute 1/(1/x+1/y) using rational arithmetic.
 */
double
combine (double x, double y)
{
    Fraction q;
    frac(x);
    q = frax;
    frac(y);
    return (double)q.n * frax.n / (q.d * frax.n + q.n * frax.d);
}

/*
 * Print a fraction.
 */
void
printfrac (double x)
{
    frac(x);
    printf("%d", frax.n);
    if (frax.d != 1)
	printf("/%d", frax.d);
}

/*
 * Print a multiple of pi.
 */
void
printpi(double x)
{
	if (!x)
	    return;
	frac(x);
	if (frax.n != 1)
	    printf("%d", frax.n);
	printf("pi");
	if (frax.d != 1)
	    printf("/%d",frax.d);
}
