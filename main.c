#ident "$Id: main.c,v 3.27 2002-01-06 16:23:01+02 rl Exp $"
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
static char *message[] = {
    "Kaleidoscopic Construction of Uniform Polyhedra, $Revision: 3.27 $",
    "\n",
    "Copyright © 1991-2002 Dr. Zvi Har'El <rl@math.technion.ac.il>",
    "\n",
    "Usage: ",
    "", /* stick program name here */
    " [options] [symbols], where the options are:\n",
    "-s: display polyhedra in the Standard list.\n",
    "-i: display polyhedra in an Input list (one per line).\n",
    "-l: List polyhedron names, symbols and reference figures.\n",
    "-x: print successive approXimations on stderr.\n",
    "-v: print Vertex and face coordinates.\n",
    "-w: Write polyhedra as virtual reality models.\n",
    "-d digits: number of significant Digits.\n",
    "-a degrees: rotation axis Azimouth.\n",
    "-e degrees: rotation axis Elevation.\n",
    "-f degrees: angle of rotation until Freezing.\n",
    "-[pP] prefix: Prefix for file names.\n",
#ifndef NOSCOPE
    "-g: display polyhedron on a Graphics monitor\n",
    "    (hit Enter for next, Backspace for previous, Tab for dual,\n",
    "    S for a snapshot, F to freeze, Esc to exit).\n",
    "-n: display Numerical data in addition to graphical.\n",
    "-L: use a Light background.\n",
    "-[RGB]: display colors: Red, Green, Blue, or combinations.\n",
    "-m mode: video Mode.\n",
    "-r edges: drawing Rate: edges per revolution.\n",
#endif
    "Unless the -s or -i options are selected, the command line may contain\n",
    "polyhedron symbols: Wythoff symbols (3 fractions and a |) \n",
    "or indices (# and an integer in the range 1 through ",
    0
};

char *
usage(void)
{
    char **p;
    for (p = message; *p; p++)
	fputs(*p, stderr);
    fprintf(stderr, "%d).\n", last_uniform);
    exit(1);
}

void
warning(void)
{
    if (!error.message) {
	if (errno)
	    error.message = strerror(errno);
	errno = 0;
    }
    fprintf(stderr, "Error: %s [%s:%d]\n", error.message, error.file,
	    error.line);
}

void
errexit(void)
{
#ifndef NOSCOPE
    if(gcont)
	gend();
#endif
    warning();
    exit(1);
}


int
main(int argc, char **argv)
{
    int digits = 6;
    double freeze = 0;
    double azimuth = AZ;
    double elevation = EL;
    char *prefix = 0;
    char *Prefix = 0;
    int mode = -1;
    int rate = 25200;
    int more_lines = 23;
    int index = 0, input = 0, just_list = 0, graphics = 0, numeric = 0;
    int color = 0, need_coordinates = 0, need_approx = 0, need_edgelist = 0;
    int vrml = 0;
    char *s;
/*
 * Process command line options
 */
    message[5] = *argv;
    if (argc == 1) usage();
    while (--argc)
	if (*(s = *++argv) == '-') {
	    while (*++s) switch (*s) {
		char *argp;
	    case 'd':
		digits = atoi(VAL);
		break;
	    case 'f':
		need_edgelist = 1;
		freeze = atof(VAL) / DEG;
		break;
	    case 'a':
		azimuth = atof(VAL) / DEG;
		break;
	    case 'e':
		elevation = atof(VAL) / DEG;
		break;
	    case 'p':
		prefix = VAL;
		break;
	    case 'P':
		Prefix = VAL;
		break;
	    case 'l':
		just_list = 1;
		break;
	    case 's':
		if (!input) input = 1;
		break;
	    case 'i':
		input = -1;
		break;
	    case 'v':
		need_coordinates = 1;
		numeric = 1;
		break;
	    case 'w':
		vrml = 1;
		need_coordinates = 1;
		break;
	    case 'x':
		need_approx = 1;
		break;
#ifndef NOSCOPE
	    case 'g':
		need_edgelist = 1;
		graphics = 1;
		break;
	    case 'n':
		numeric = 1;
		break;
	    case 'R':
		color |= 1;
		break;
	    case 'G':
		color |= 2;
		break;
	    case 'B':
		color |= 4;
		break;
	    case 'L':
		color |= 8;
		break;
	    case 'm':
		mode = atoi(VAL);
		break;
	    case 'r':
		rate = atoi(VAL);
		break;
#endif
	    default:
		fprintf(stderr, "illegal option: -%c\n", *s);
		usage ();
	    }
	} else
	    break; /* rest of arguments are symbols */
/*
 * Process enviroment variables
 */
    if (s = getenv("LINES"))
	more_lines = atoi (s) - 1;
/*
 * Set defaults
 */
    if (need_coordinates || need_edgelist) {
	if (!prefix && !Prefix) {
		static char default_prefix[6];
		sprintf (default_prefix, "%05d", getpid());
		Prefix = prefix = default_prefix;
	} else if (!prefix) prefix = Prefix;
	else if (!Prefix) Prefix = prefix;
    }
    if (!graphics && !vrml) numeric = 1;
/*
 * Initialize continuous graphics
 */
#ifndef NOSCOPE
    if (graphics) {
	if (!gcont && !numeric && !(input < 0 &&
		(isatty(fileno(stdin)) || isatty(fileno(stdout)))))
	    gcont = 1;
	if (gcont && !ginit(mode, color))
	    errexit();
    } else
	gcont = 0;
#endif
/*
 * Main loop
 */
    for (;;) {
	char *sym;
	Polyhedron *P;
/*
 * Get next polyhedron
 */
	if (!(sym = nextsym(input, index, &argc, &argv)))
	    break;
/*
 * Solve polyhedron
 */
	if (!(P = kaleido(sym, need_coordinates, need_edgelist, need_approx,
			just_list))) {
	    if (input >= 0 || !isatty(fileno(stdin)) ||
		    !isatty(fileno(stdout)))
		errexit ();
	    warning();
	    continue;
	}
/*
 * Print data
 */
	if (numeric && !printit(P, need_coordinates, just_list, digits,
		    more_lines))
	    errexit();
/*
* Write data as a virtual reality model
*/
	if (vrml) {
	    if (!vrmodel(P, P->v, P->V, P->f, P->F, P->name, "", prefix,
			digits, azimuth, elevation, freeze))
		errexit();
	    if (!vrmodel(P, P->f, P->F, P->v, P->V, P->dual_name, "*", Prefix,
			digits, azimuth, elevation, freeze))
		errexit();
	}
/*
 * Show pictures of polyhedron and its dual.
 */
	if (graphics) {
#ifndef NOSCOPE
	    int c;
	    if (!gcont && !ginit(mode, color))
		errexit();
	    c = gshow(P, rate, azimuth, elevation, freeze, prefix, Prefix);
	    if (!gcont)
		gend();
	    if (!c) break;
	    if (input > 0)
		index += c;
#endif
/*
* Save picture on file
*/
	} else {
	    if (!vrml && need_edgelist && !savepic(P, azimuth, elevation,
		    freeze, prefix, Prefix))
		errexit();
	    if (input > 0) index++;
	}
	polyfree(P);
    }
/*
* Normal termination
*/
#ifndef NOSCOPE
    if(gcont)
	gend();
#endif
    exit(0);
}

/*
 * Returns the next input symbol.
 */
char *
nextsym(int input, int index, int *pargc, char ***pargv)
{
    if (!input){ /* get symbol from command line */
	if (!(*pargc)--)
	    return 0;
	return *(*pargv)++;
    } else if (input > 0) { /* get symbol from standard list */
	static char sym[4];
	if (index < 0 || index >= last_uniform)
	    return 0;
	sprintf(sym, "#%d", index + 1);
	return sym;
    } else { /* get symbol from standard input */
	int c, len = 0;
	static char *sym;
	if (!sym) Malloc (sym,1,char)
	if (isatty(fileno(stdout)) && isatty(fileno(stdin)))
	    fputs ("Enter symbol: ",stdout);
	if ((c = getchar ()) == EOF) {
	    if (isatty(fileno(stdout)) && isatty(fileno(stdin)))
		fputs("EOF\n", stdout);
	    return 0;
	}
	ungetc (c, stdin);
	while ((c = getchar ()) != EOF && c != '\n') {
	    sym[len++] = c;
	    Realloc(sym, len+1, char)
	}
	sym[len] = 0;
	return sym;
    }
}

/*
 * Print polyhedron data
 */
printit(Polyhedron *P, int need_coordinates, int just_list, int digits,
	int more_lines)
{
    int j, i;
    double cosa;
    static char *group[] = {"di", "tetra", "octa", "icosa"};
    static char *alias[] = {"D", "A4", "S4", "A5"};
/*
 * Print polyhedron name, Wythoff symbol, and reference figures.
 */
    if (P->index != -1) printf("%d) ", P->index + 1);
    printf("%s %s", P->name, P->polyform);
    if (P->index != -1 && uniform[P->index].Coxeter)
	printf(" [%d,%d]",uniform[P->index].Coxeter,
		uniform[P->index].Wenninger);
    putchar('\n');
    if (just_list)
	return 1;
/*
 * Print combinatorial description.
 */
    printf("\tdual: %s\n\t%s, %shedral group %s", P->dual_name, P->config,
	    group[P->K-2], alias[P->K-2]);
    if (P->K == 2)
	printf("%d", P->g / 4);
    printf(", chi=%d", P->chi);
    if (P->D)
	printf(", D=%d", P->D);
    else if (P->onesided)
	printf(", one-sided");
    else
	printf(", two-sided");
    printf("\n\tV=%d, E=%d, F=%d=", P->V, P->E, P->F);
    for (j = 0; j < P->N; j++) {
	if (j)
	    putchar('+');
	printf("%d{", P->Fi[j]);
	printfrac(P->n[j]);
	putchar('}');
    }
/*
 * Print solution.
 */
    if (P->index == -1 && P->K == 2) {
	char *s;
	Sprintfrac(s, P->gon)
	i = strlen(s) + 2;
	if (i < 6)
	    i = 6;
	free (s);
    } else
	i = 6;
    printf("\n%*s%6s%*s%*s%*s%*s%*s%*s%*s%*s\n", i, "", "alpha",
	    digits + 3, "gamma", digits + 1, "a", digits + 1, "b",
	    digits + 1, "c", digits + 3, "rho/R", digits + 3, "r/rho",
	    digits + 3, "l/rho", digits + 3, "h/r");
    cosa = cos(M_PI / P->n[0]) / sin(P->gamma[0]);
    for (j = 0; j < P->N; j++) {
	double cosc = cos(P->gamma[j]) / sin(M_PI / P->n[j]);
	char *s, *t;
	Sprintfrac(s, P->n[j])
	Malloc(t, strlen(s) + 3, char)
	sprintf(t, "{%s}", s);
	free(s);
	printf("%*s%6.1f%*.*f%*.*f%*.*f%*.*f%*.*f%*.*f", i, t, 180. / P->n[j],
		digits + 3, digits - 2, DEG * P->gamma[j],
		digits + 1, digits - 4, DEG * acos(cosa),
		digits + 1, digits - 4, DEG * acos(cosa * cosc),
		digits + 1, digits - 4, DEG * acos(cosc),
		digits + 3, digits, cosa, digits + 3, digits, cosc);
	if (log10(fabs(cosa)) < -digits)
	    printf("%*s", digits + 3, "infinity");
	else
	    printf("%*.*f", digits + 3, digits, sqrt(1 - cosa * cosa) / cosa);
	if (log10(fabs(cosc)) < -digits)
	    printf("%*s", digits + 3, "infinity");
	else
	    printf("%*.*f", digits + 3, digits, sqrt(1 - cosc * cosc) / cosc);
	putchar('\n');
	free(t);
    }
    putchar('\n');
    more();
    if (!need_coordinates)
	return 1;
/*
 * Print vertices
 */
    printf("vertices:\n");
    for (i = 0; i < P->V; i++) {
	printf("v%-3d (%*.*f,%*.*f,%*.*f)", i + 1, digits + 3, digits,
		P->v[i].x, digits + 3, digits, P->v[i].y, digits + 3, digits,
		P->v[i].z);
	for (j = 0; j < P->M; j++)
	    printf(" v%-3d",P->adj[j][i] + 1);
	printf("\n%*s", 3 * digits + 20, "");
	for (j = 0; j < P->M; j++)
	    printf(" f%-3d",P->incid[j][i] + 1);
	putchar('\n');
	if (!((i + 1) % (more_lines / 2)))
	    more();
    }
    if (P->V % (more_lines / 2))
	more();
/*
* Print faces.
*/
    printf("faces (RHS=%*.*f", digits + 2, digits, P->minr);
    printf("):\n");
    for (i = 0; i < P->F; i++){
	printf("f%-3d (%*.*f,%*.*f,%*.*f) {", i + 1, digits + 3, digits,
		P->f[i].x, digits + 3, digits, P->f[i].y, digits + 3, digits,
		P->f[i].z);
	printfrac(P->n[P->ftype[i]]);
	putchar('}');
	if (P->hemi && !P->ftype[i])
	    putchar('*');
	putchar('\n');
	if (!((i + 1) % more_lines))
	    more();
    }
    if (P->F % more_lines)
	more();
    putchar('\n');
    return 1;
}

void
more(void)
{
    int c;
    if (isatty(fileno(stdout)) && isatty(fileno(stdin))) {
	fputs("Enter for more...", stdout);
	while ((c = getchar()) != EOF && c != '\n')
	    ;
    }
}


int
vrmodel (Polyhedron *P, Vector *v, int V, Vector *f, int F, char *name,
	char *star, char *prefix, int digits, double azimuth, double elevation,
	double freeze)
{
    int i, j, k, l, ll, ii, *hit, facelets;
    FILE *fp;
    char *fn;
    Vector *temp;
    Malloc(fn, strlen(prefix) + 8, char)
    for (i = 1; i < 1000; i++) {
	sprintf(fn, "%s%03d.wrl", prefix, i);
	if (access(fn, 0)) {/* file doesn't exist */
	    fp = fopen(fn, "w");
	    break;
	}
    }
    if (i == 1000)
	Err("too many files")
    if (!fp)
	Err(0)
/*
 * Rotate polyhedron
 */
    rotframe(azimuth, elevation, freeze);
    Malloc(temp, V, Vector)
    rotarray(temp, v, V);
    v = temp;
    Malloc(temp, F, Vector)
    rotarray(temp, f, F);
    f = temp;
/*
 * File header
 */
    fprintf(fp, "#VRML V2.0 utf8\n");
    fprintf(fp, "WorldInfo{\n");
    fprintf(fp, "\tinfo[\n");
    fprintf(fp, "\t\t\"%s\"\n", message[0]);
    fprintf(fp, "\t\t\"%s\"\n", message[2]);
    fprintf(fp, "\t]\n");
    fprintf(fp, "\ttitle \"%d%s) %s %s %s\"\n", P->index + 1, star, name,
	    P->polyform, P->config);
    fprintf(fp, "}\n");
    fprintf(fp, "NavigationInfo {\n");
    fprintf(fp, "\ttype \"EXAMINE\"\n");
    /* fprintf(fp, "\theadlight TRUE\n"); */
    fprintf(fp, "}\n");
    fprintf(fp, "Shape{\n");
    fprintf(fp, "\tappearance Appearance{\n");
    fprintf(fp, "\t\tmaterial Material{\n");
    fprintf(fp, "\t\t\tshininess 1\n");
    fprintf(fp, "\t\t}\n");
    fprintf(fp, "\t}\n");
    fprintf(fp, "\tgeometry IndexedFaceSet{\n");
    if (P->D != 1) {
	fprintf(fp, "\t\tconvex FALSE\n");
	fprintf(fp, "\t\tsolid FALSE\n");
    }
    fprintf(fp, "\t\tcreaseAngle 0\n");
    fprintf(fp, "\t\tcolorPerVertex FALSE\n");
/*
 * Color map
 * Face colors are assigned as a function of the face valency.
 * Thus, pentagons and pentagrams will be colored alike.
 */
    fprintf(fp, "\t\tcolor Color{\n");
    fprintf(fp, "\t\t\tcolor[");
    if (*star)
	rgbcolor(fp, P->M);
    else
	for (i = 0; i < P->N; i++)
	    rgbcolor(fp, numerator(P->n[i]));
    fprintf(fp, "]\n");
    fprintf(fp, "\t\t}\n");
/*
 * Vertex list
 */
    fprintf(fp, "\t\tcoord Coordinate{\n");
    fprintf(fp, "\t\t\tpoint[\n");
    for (i = 0; i < V; i++)
	printvec(fp, v[i], digits);
/*
 * Auxiliary vertices (needed because current VRML browsers cannot handle
 * non-simple polygons, i.e., ploygons with self intersections):
 * Each non-simple face is assigned an auxiliary vertex. By connecting it to
 * the rest of the vertices the face is triangulated. The circum-center is used
 * for the regular star faces of uniform polyhedra. The in-center is used for
 * the pentagram (#79) and hexagram (#77) of the high-density snub duals, and
 * for the pentagrams (#40, #58) and hexagram (#52) of the stellated duals with
 * configuration (....)/2. Finally, the self-intersection of the crossed
 * parallelogram is used for duals with form p q r| with an even denominator.
 *
 * This method do not work for the hemi-duals, whose faces are not star-shaped
 * and have two self-intersections each.
 * Thus, for each face we need six auxiliary vertices: The self intersections
 * and the terminal points of the truncations of the infinite edges. The ideal
 * vertices are listed, but are not used by the face-list.
 * Note that the face of the last dual (#80) is octagonal, and constists of two
 * quadrilaterals of the infinite type.
 */
    fprintf(fp, "\t\t\t\t# auxiliary vertices:\n");
    if (*star && P->even != -1)
	Malloc(hit, F, int)
    for (i = 0; i < F; i++)
	if (!*star && (frac(P->n[P->ftype[i]]), frax.d != 1 &&
		    frax.d != frax.n - 1) || *star && (P->K == 5 &&
			P->D > 30 || denominator (P->m[0]) != 1)) {
	    /* find the center of the face */
	    double h;
	    if (!*star && P->hemi && !P->ftype[i])
		h = 0;
	    else
		h = P->minr / dot(f[i],f[i]);
	    printvec(fp, scale (h, f[i]), digits);
	} else if (*star && P->even != -1) {
	    /* find the self-intersection of a crossed parallelogram.
	     * hit is set if v0v1 intersects v2v3*/
	    Vector v0, v1, v2, v3, c0, c1, p;
	    double d0, d1;
	    v0 = v[P->incid[0][i]];
	    v1 = v[P->incid[1][i]];
	    v2 = v[P->incid[2][i]];
	    v3 = v[P->incid[3][i]];
	    d0 = sqrt(dot(diff(v0, v2), diff(v0, v2)));
	    d1 = sqrt(dot (diff(v1, v3), diff(v1, v3)));
	    c0 = scale(d1, sum(v0, v2));
	    c1 = scale(d0, sum(v1, v3));
	    p = scale(0.5 / (d0 + d1), sum(c0, c1));
	    printvec(fp, p, digits);
	    p = cross(diff(p, v2), diff(p, v3));
	    hit[i] = (dot(p, p) < 1e-6);
	} else if (*star && P->hemi && P->index != last_uniform - 1) {
	    /* find the terminal points of the truncation and the
	     * self-intersections.
	     *  v23       v0       v21
	     *  |  \     /  \     /  |
	     *  |   v0123    v0321   |
	     *  |  /     \  /     \  |
	     *  v01       v2       v03
	     */
	    Vector v0, v1, v2, v3, v01, v03, v21, v23, v0123, v0321 ;
	    Vector u;
	    double t = 1.5;/* truncation adjustment factor */
	    j = !P->ftype[P->incid[0][i]];
	    v0 = v[P->incid[j][i]];/* real vertex */
	    v1 = v[P->incid[j+1][i]];/* ideal vertex (unit vector) */
	    v2 = v[P->incid[j+2][i]];/* real */
	    v3 = v[P->incid[(j+3)%4][i]];/* ideal */
	    /* compute intersections
	     * this uses the following linear algebra:
	     * v0123 = v0 + a v1 = v2 + b v3
	     * v0 x v3 + a (v1 x v3) = v2 x v3
	     * a (v1 x v3) = (v2 - v0) x v3
	     * a (v1 x v3) . (v1 x v3) = (v2 - v0) x v3 . (v1 x v3)
	     */
	    u = cross(v1, v3);
	    v0123 = sum(v0, scale(dot(cross(diff(v2, v0), v3), u) / dot(u,u),
			v1));
	    v0321 = sum(v0, scale(dot(cross(diff(v0, v2), v1), u) / dot(u,u),
			v3));
	    /* compute truncations */
	    v01 = sum(v0 , scale(t, diff(v0123, v0)));
	    v23 = sum(v2 , scale(t, diff(v0123, v2)));
	    v03 = sum(v0 , scale(t, diff(v0321, v0)));
	    v21 = sum(v2 , scale(t, diff(v0321, v2)));
	    printvec(fp, v01, digits);
	    printvec(fp, v23, digits);
	    printvec(fp, v0123, digits);
	    printvec(fp, v03, digits);
	    printvec(fp, v21, digits);
	    printvec(fp, v0321, digits);
	} else if (*star && P->index == last_uniform - 1) {
	    /* find the terminal points of the truncation and the
	     * self-intersections.
	     *  v23       v0       v21
	     *  |  \     /  \     /  |
	     *  |   v0123    v0721   |
	     *  |  /     \  /     \  |
	     *  v01       v2       v07
	     *
	     *  v65       v4       v67
	     *  |  \     /  \     /  |
	     *  |   v4365    v4567   |
	     *  |  /     \  /     \  |
	     *  v43       v6       v45
	     */
	    Vector v0, v1, v2, v3, v4, v5, v6, v7, v01, v07, v21, v23;
	    Vector v43, v45, v65, v67, v0123, v0721, v4365, v4567;
	    double t = 1.5;/* truncation adjustment factor */
	    Vector u;
	    for (j = 0; j < 8; j++)
		if (P->ftype[P->incid[j][i]] == 3)
		    break;
	    v0 = v[P->incid[j][i]];/* real {5/3} */
	    v1 = v[P->incid[(j+1)%8][i]];/* ideal */
	    v2 = v[P->incid[(j+2)%8][i]];/* real {3} */
	    v3 = v[P->incid[(j+3)%8][i]];/* ideal */
	    v4 = v[P->incid[(j+4)%8][i]];/* real {5/2} */
	    v5 = v[P->incid[(j+5)%8][i]];/* ideal */
	    v6 = v[P->incid[(j+6)%8][i]];/* real {3/2} */
	    v7 = v[P->incid[(j+7)%8][i]];/* ideal */
	    /* compute intersections */
	    u = cross(v1, v3);
	    v0123 = sum(v0, scale(dot(cross(diff(v2, v0), v3), u) / dot(u,u),
			v1));
	    u = cross(v7, v1);
	    v0721 = sum(v0, scale(dot(cross(diff(v2, v0), v1), u) / dot(u,u),
			v7));
	    u = cross(v5, v7);
	    v4567 = sum(v4, scale(dot(cross(diff(v6, v4), v7), u) / dot(u,u),
			v5));
	    u = cross(v3, v5);
	    v4365 = sum(v4, scale(dot(cross(diff(v6, v4), v5), u) / dot(u,u),
			v3));
	    /* compute truncations */
	    v01 = sum(v0 , scale(t, diff(v0123, v0)));
	    v23 = sum(v2 , scale(t, diff(v0123, v2)));
	    v07 = sum(v0 , scale(t, diff(v0721, v0)));
	    v21 = sum(v2 , scale(t, diff(v0721, v2)));
	    v45 = sum(v4 , scale(t, diff(v4567, v4)));
	    v67 = sum(v6 , scale(t, diff(v4567, v6)));
	    v43 = sum(v4 , scale(t, diff(v4365, v4)));
	    v65 = sum(v6 , scale(t, diff(v4365, v6)));
	    printvec(fp, v01, digits);
	    printvec(fp, v23, digits);
	    printvec(fp, v0123, digits);
	    printvec(fp, v07, digits);
	    printvec(fp, v21, digits);
	    printvec(fp, v0721, digits);
	    printvec(fp, v45, digits);
	    printvec(fp, v67, digits);
	    printvec(fp, v4567, digits);
	    printvec(fp, v43, digits);
	    printvec(fp, v65, digits);
	    printvec(fp, v4365, digits);
	}
    fprintf(fp, "\t\t\t]\n");
    fprintf(fp, "\t\t}\n");
/*
 * Face list:
 * Each face is printed in a separate line, by listing the indices of its
 * vertices. In the non-simple case, the polygon is represented by the
 * triangulation, each triangle consists of two polyhedron vertices and one
 * auxiliary vertex.
 */
    fprintf(fp, "\t\tcoordIndex[\n");
    ii = V;
    facelets = 0;
    for (i = 0; i < F; i++) {
	fprintf(fp, "\t\t\t");
	if (*star) {
	    if (P->K == 5 && P->D > 30 || denominator (P->m[0]) != 1) {
		for (j = 0; j < P->M - 1; j++) {
		    fprintf(fp, "%d,%d,%d,-1,", P->incid[j][i],
			    P->incid[j+1][i], ii);
		    facelets++;
		}
		fprintf(fp, "%d,%d,%d,-1,", P->incid[j][i],
			P->incid[0][i], ii++);
		facelets++;
	    } else if (P->even != -1) {
		if (hit[i]) {
		    fprintf(fp, "%d,%d,%d,-1,%d,%d,%d,-1,", P->incid[3][i],
			    P->incid[0][i], ii, P->incid[1][i], P->incid[2][i],
			    ii);
		} else {
		    fprintf(fp, "%d,%d,%d,-1,%d,%d,%d,-1,", P->incid[0][i],
			    P->incid[1][i], ii, P->incid[2][i], P->incid[3][i],
			    ii);
		}
		ii++;
		facelets += 2;
	    } else if (P->hemi && P->index != last_uniform - 1) {
		j = !P->ftype[P->incid[0][i]];
		fprintf(fp, "%d,%d,%d,-1,%d,%d,%d,%d,-1,%d,%d,%d,-1,", ii,
			ii + 1, ii + 2, P->incid[j][i], ii + 2,
			P->incid[j+2][i], ii + 5, ii + 3, ii + 4, ii + 5);
		ii += 6;
		facelets += 3;
	    } else if (P->index == last_uniform - 1) {
		for (j = 0; j < 8; j++)
		    if (P->ftype[P->incid[j][i]] == 3)
			    break;
		fprintf(fp, "%d,%d,%d,-1,%d,%d,%d,%d,-1,%d,%d,%d,-1,", ii,
			ii + 1, ii + 2, P->incid[j][i], ii + 2,
			P->incid[(j+2)%8][i], ii + 5, ii + 3, ii + 4, ii + 5);
		fprintf(fp, "%d,%d,%d,-1,%d,%d,%d,%d,-1,%d,%d,%d,-1,", ii + 6,
			ii + 7, ii + 8, P->incid[(j+4)%8][i], ii + 8,
			P->incid[(j+6)%8][i], ii + 11, ii + 9, ii + 10,
			ii + 11);
		ii += 12;
		facelets += 6;
	    } else {
		for (j = 0; j < P->M; j++)
		    fprintf(fp, "%d,",P->incid[j][i]);
		fprintf(fp, "-1,");
		facelets++;
	    }
	} else {
	    int split = (frac(P->n[P->ftype[i]]),
		    frax.d != 1 && frax.d != frax.n - 1);
	    for (j = 0; j < V; j++) {
		for (k = 0; k < P->M; k++)
		    if (P->incid[k][j] == i)
			break;
		if (k != P->M)
		    break;
	    }
	    if (!split )
		fprintf(fp, "%d,",j);
	    ll = j;
	    for (l = P->adj[k][j]; l != j; l = P->adj[k][l]) {
		for (k = 0; k < P->M; k++)
		    if (P->incid[k][l] == i)
			break;
		if (P->adj[k][l] == ll)
		    k = mod(k + 1 , P->M);
		if (!split)
		    fprintf(fp, "%d,", l);
		else {
		    fprintf(fp, "%d,%d,%d,-1,", ll, l, ii);
		    facelets++;
		}
		ll = l;
	    }
	    if (!split) {
		fprintf(fp, "-1,");
		facelets++;
	    } else {
		fprintf(fp, "%d,%d,%d,-1,", ll, j, ii++);
		facelets++;
	    }
	}
	fprintf(fp, "\n");
    }
    fprintf(fp, "\t\t]\n");
/*
 * Face color indices - for polyhedra with multiple face types
 * For non-simple faces, the index is repeated as many times as needed by the
 * triangulation.
 */
    fprintf(fp, "\t\tcolorIndex[");
    if (!*star && P->N != 1) {
	for (i = 0; i < F; i++)
	    if (frac(P->n[P->ftype[i]]), frax.d == 1 || frax.d == frax.n - 1)
		fprintf(fp, "%d,", P->ftype[i]);
	    else
		for (j = 0; j < frax.n; j++)
		    fprintf(fp, "%d,", P->ftype[i]);
    } else {
	for (i = 0; i < facelets; i++)
	    fprintf(fp, "0,");
    }
    fprintf(fp, "]\n");
    fprintf(fp, "\t}\n");
    if (*star && P->even != -1)
	free(hit);
    free(v);
    free(f);
    fprintf(fp, "}\n");
    if (ferror(fp))
	Err(0)
    fclose(fp);
    fprintf(stderr, "%s: written on %s\n", name, fn);
    return 1;
}

void
printvec(FILE *fp, Vector v, int digits)
{
    fprintf(fp, "\t\t\t\t%*.*f %*.*f %*.*f,\n", digits + 3, digits, v.x,
	    digits + 3, digits, v.y, digits + 3, digits, v.z);
}

/*
 * Choose a color for a given face valency.
 * 3-,4- and 5-sided polygons have the simple colors R, G, and B.
 * 6-,8- and 10-sided polygons, which also occur in the standard polyhedra,
 * have the blended colors RG (yellow), RB (magenta) and GB (cyan).
 * All othe polygons (which occur in kaleido only if a Whythoff formula is
 * entered) are colored pink (its RGB value is taken from X11's rgb.txt).
 */
void
rgbcolor(FILE *fp, int n)
{
    double R, G, B;
    switch (n) {
    case 3:	/* red */
	R = 1; G = 0; B = 0; break;
    case 4:	/* green */
	R = 0; G = 1; B = 0; break;
    case 5:	/* blue */
	R = 0; G = 0; B = 1; break;
    case 6:	/* yellow */
	R = 1; G = 1; B = 0; break;
    case 8:	/* magenta */
	R = 1; G = 0; B = 1; break;
    case 10:	/* cyan */
	R = 0; G = 1; B = 1; break;
    default:	/* pink */
	R = 1; G = 192./255.; B = 203./255.; break;
    }
    fprintf(fp, "%g %g %g,", R, G, B);
}

int
savepic(Polyhedron *P, double azimuth, double elevation, double freeze, char *prefix, char *Prefix)
{
    char *fn;
    rotframe(azimuth, elevation, freeze);
    fn = picfile(P->v, P->V, P->e, P->E, (int *) 0, P->index, "", P->config,
	    P->polyform, prefix, 1);
    if (!fn)
	Err(0)
    fprintf(stderr, "%s: saved on %s\n", P->name, fn);
    free(fn);
    fn = picfile(P->f, P->F, P->dual_e, P->E, P->anti, P->index, "*",
	    P->config, P->polyform, Prefix, 1);
    if (!fn)
	Err(0)
    fprintf(stderr, "%s: saved on %s\n", P->dual_name, fn);
    free(fn);
    return 1;
}

/*
 * Generate a pic file
 */
char *
picfile(Vector *v, int V, int **e, int E, int *anti, int index, char *star,
    char *subtitle, char *subsub, char *prefix, int need_rotation)
{
    int i;
    FILE *fp = 0;
    Vector temp, *new = 0;
    int *s, *t, *u;
    char *fn;
    Malloc(fn, strlen (prefix) + 8, char)
    for (i = 1; i < 1000; i++) {
	sprintf(fn, "%s%03d.pic", prefix, i);
	if (access(fn, 0)) {/* file doesn't exist */
	    fp = fopen(fn, "w");
	    break;
	}
    }
    if (i == 1000)
	Err("too many files")
    if (!fp)
	Err(0)
    if (!need_rotation)
	new = v;
    else {
	Malloc(new, V, Vector)
	rotarray(new, v, V);
    }
    fprintf(fp, ".PS\n");
    fprintf(fp, ".ps 8\nbox ht 2.5 wid 2.5 at 0,0\n");
    fprintf(fp, "\"%s \" at last box.se rjust above\n", subtitle);
    fprintf(fp, "\" %s\" at last box.sw ljust above\n", subsub);
    if (index != -1)
	fprintf(fp, "\"Fig. %d%s\" at last box.s below\n", index + 1, star);
    s = e[0];
    t = e[1];
    u = anti;
    for (i = E; !ferror(fp) && i--; ) {
	int j = *s++, k = *t++;
	if (!anti) {
	    pic(fp, new[j], new[k], j, k);
	} else if (*u++) {
	    temp = scale(.5, new[j]);
	    pic(fp, temp, diff(temp, new[k]), j, k);
	} else {
	    temp = scale(.5, new[j]);
	    pic(fp, temp, sum(temp, new[k]), j, k);
	}
    }
    fprintf(fp, ".PE\n");
    if (ferror(fp))
	Err(0);
    fclose(fp);
    if (need_rotation)
	Free(new)
    return fn;
}

/* generate pic command to draw a segment using variable pointsize */
pic (FILE *fp, Vector a, Vector b, int j, int k)
{
    int i;
    double aa, bb;
    if (a.z < b.z) {/* swap endpoints to get increasing point size */
	Vector temp;
	temp = a;
	a = b;
	b = temp;
	i = j;
	j = k;
	k = i;
    }
    aa = 8 * (1 - a.z);
    bb = 8 * (1 - b.z);
    fprintf(fp, "move to %g,%g #v%d\n", a.x, a.y, j);
    for (i = (int) aa + 1; i < (int) bb + 1; i++) {
	double f;
	f = ((double) i - aa) / (bb - aa);
	fprintf(fp, ".ps %d\nline to %g,%g\n", i, a.x + (b.x - a.x) * f,
		a.y + (b.y - a.y) * f);
    }
    fprintf(fp, ".ps %d\nline to %g,%g #v%d\n", i, b.x, b.y, k);
}
