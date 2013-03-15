#ident "$Id: scope.c,v 3.27 2002-01-06 16:34:46+02 rl Exp $"
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
 *		Dr. Zvi Har'El,
 *		Deptartment of Mathematics,
 *		Technion, Israel Institue of Technology,
 *		Haifa 32000, Israel.
 *		E-Mail: rl@math.technion.ac.il
 *****************************************************************************
 */
#include "kaleido.h"
#ifdef MSDOS
#include "vidmsdos.h"
#else
#ifdef JDYX
#include "vidjdyx.h"
#else
#ifdef LUCAS
#include "vidlucas.h"
#else
#include "vidx11.h"
#endif
#endif
#endif
int gcont = VIDEOSPLIT;
static void draw (Vector a, Vector b, int pen);

int
ginit(int mode, int color)
/* Initialize graphics */
{
    if (!(color&7))
	color |= 7;
    if (!videoinit(mode, color&1, color&2, color&4, color&8)) {
	gcont = 0;
	Err("cannot initialize graphics")
    }
    return 1;
}

int
gshow(Polyhedron *P, int rate, double azimuth, double elevation, double freeze,
	char *prefix, char *Prefix)
{
    int c, totalsteps, freezesteps;
    double rotangle;
    char *title, *dual_title;
    totalsteps = rate / P->E;
    if (totalsteps  < 2)
	totalsteps = 2;
    /* If rate is very low, totalsteps may vanish. */
    /* Reported by John Firth <jrf@minster.york.ac.uk> */
    rotangle  = 2 * M_PI / totalsteps;
    freezesteps = mod((int) (freeze / rotangle), totalsteps);
    rotframe(azimuth, elevation, rotangle);
    if (P->index >= 0) {
	Malloc(title, strlen(P->name) + 4, char)
	sprintf(title, "%d)%s", P->index + 1, P->name);
	Malloc(dual_title, strlen(P->dual_name) + 5, char)
	sprintf(dual_title, "%d*)%s",P->index + 1, P->dual_name);
    } else {
	title = P->name;
	dual_title = P->dual_name;
    }
    for (;;) {
	c = scope(P->v, P->V, P->e, P->E, (int *) 0, title, P->config,
		P->polyform, totalsteps, freezesteps, prefix, P->index, "");
	if (c != '\t')
	    break;
	c = scope(P->f, P->F, P->dual_e, P->E, P->anti, dual_title, P->config,
		P->polyform, totalsteps, freezesteps, Prefix, P->index, "*");
	if (c != '\t')
	    break;
    }
    if (P->index >= 0) {
	free(title);
	free(dual_title);
    }
    if (c == '\n' || c == '\r')
	return 1;
    if (c == '\b')
	return -1;
    return 0;
}
/* end graphics */
void
gend(void)
{
    videoclose();
}


/*
 * Draw a polyhedron, given its vertices v[V] and edge list e[2][E].
 *
 * To enable drawing the duals of hemi-polyhedra, which have ideal vertices as
 * the polar reciprocals of hemispherical faces, anti[V] may be
 * given.
 *
 * anti[i] is set if the ray from the v[e[0][i]] to the ideal vertex v[e[1][i]]
 * is anti-parallel to the (unit) Vector representing that vertex.
 * In a finite polyhedron, anti should be null.
 */
Vector center;
double radius;

int
scope (Vector *v, int V, int **e, int E, int *anti, char *title,
	char *subtitle, char *subsub, int N, int M, char *prefix, int index,
	char *star)
{
    Vector **vec, *old, *new;
    int *s, *t, *u;
    char c;
    int toggle = 0, freeze = 0, notfirst = 0, step, i;
    static char freezing[] = "freezing...";

/*
 * Allocate dynamic array.
 * vec[2][V] holds vertex coordinates, before and after each rotation step.
 */
    Matalloc(vec, 2, V, Vector)
    videoclear();
    for (step = 0; ; step = (step + 1) % N) {
	if (!notfirst || videoredraw()) {
/*
 * Display titles.
 * Compute picture center and radius.
 */
	    videotitle(title, 15);
	    videosubtitle(subtitle, 15);
	    videosubsub(subsub, 15);
	    radius = video.height / 1.2;
	    if (radius > video.width)
		radius = video.width;
	    radius /= 2;
	    center.x = video.width - radius;
	    center.y = video.height - radius;
	}
/*
 * Get original vertex coordinates or rotate old ones.
 */
	new = vec[toggle];
	old = vec[!toggle];
	toggle = !toggle;
	if (!step)
	    memcpy((char*) new, (char*) v, V * sizeof(Vector));
	else
	    rotarray(new, old, V);
/*
 * Draw new edges while erasing old ones.
 * Edges are colored according to the z-coordinate of their midpoint:
 * the higher - the dimmer (this is done because the vertices are generated
 * by BFS from (0,0,1), which implies that points with lower z-coordinates
 * are drawn later).
 */
	s = e[0];
	t = e[1];
	u = anti;
	for (i = E; i--; ) {
	    Vector temp;
	    int j = *s++, k = *t++;
	    if (!anti) {
		if(notfirst)
		    draw(old[j], old[k], 0);
		draw(new[j], new[k], 1);
	    } else if (*u++) {
		if(notfirst) {
		    temp = scale(.5, old[j]);
		    draw (temp, diff(temp, old[k]), 0);
		}
		temp = scale(.5, new[j]);
		draw (temp, diff(temp, new[k]), 1);
	    } else {
		if(notfirst) {
		    temp = scale(.5, old[j]);
		    draw(temp, sum (temp, old[k]), 0);
		}
		temp = scale(.5, new[j]);
		draw(temp, sum(temp, new[k]), 1);
	    }
	}
	notfirst = 1;

/*
 * Check for user kyboard entry.
 * If none, and no pending request to freeze, continue drawing.
 */
	if (!(c = videokeypressed()) && !(freeze && step == M))
	    continue;

	if (freeze) {
	    videosubtitle(freezing, 0);
	    videosubtitle(subtitle, 15);
	    freeze = 0;
	}

/*
 * If hit Enter, Backspace, Tab or Esc, free dynamic buffers and return.
 */
	if (c == '\n' || c == '\r' || c == '\b' || c == '\033' || c == '\t') {
	    matfree(vec, 2);
	    return c ;
	}
/*
 * If hit F, register request to freeze, and continue drawing.
 */
	if (c == 'F' || c == 'f') {
	    videosubtitle(subtitle, 0);
	    videosubtitle(freezing, 15);
	    freeze = 1;
	    continue;
	}
/*
 * Wait for another key hit.
 * If hit S, generate a pic snapshot and display file name.
 */
    if ((c = videoreadkey ()) == 'S' || c == 's') {
	    char *fn;
	    videosubtitle(subtitle, 0);
	    fn = picfile(new, V, e, E, anti, index, star, subtitle, subsub,
		    prefix, 0);
	    if (!fn) {
		    static char failed[] = "write error";
		    videobeep();
		    videosubtitle(failed, 15);
		    videoreadkey();
		    videosubtitle(failed, 0);
	    } else {
		    videosubtitle(fn, 15);
		    videoreadkey();
		    videosubtitle(fn, 0);
		    free(fn);
	    }
	    videosubtitle(subtitle, 15);
	}
    }
}

/* draw a segment using variable brightness */
/* when erasing a segment (pen is zero), although variable brightness is not
 * needed, we still use the same partition to ensure correct erasure */
static void
draw (Vector a, Vector b, int pen)
{
    int i, i1, i2;
    double aa, bb;
    if (a.z < b.z) {/* swap endpoints to get increasing point size */
	Vector temp;
	temp = a;
	a = b;
	b = temp;
    }
    aa = 8 * (1 - a.z);
    bb = 8 * (1 - b.z);
    i1 = aa + 1;
    i2 = bb + 1;
    if (i1 < 1) i1 = 1;
    if (i2 > 15) i2 = 15;
    a = sum(center, scale(radius, a));
    b = sum(center, scale(radius, b));
    videomoveto(a.x, a.y);
    for (i = i1; i < i2; i++) {
	double f;
	f = ((double) i - aa) / (bb - aa);
	videosetcolor(pen ? i : 0);
	videolineto(a.x + (b.x - a.x) * f, a.y + (b.y - a.y) * f);
    }
    videosetcolor(pen ? i2 : 0);
    videolineto(b.x, b.y);
}
