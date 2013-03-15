#ident "$Id: uniform.c,v 3.27 2002-01-06 16:23:40+02 rl Exp $"
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

/*
 *****************************************************************************
 *	List of Uniform Polyhedra and Their Kaleidoscopic Formulae
 *	==========================================================
 *
 *	Each entry contains the following items:
 *
 *	1)	Wythoff symbol.
 *	2)	Polyhedron name.
 *	3)	Dual name.
 *	4)	Coxeter &al. reference figure.
 *	5)	Wenninger reference figure.
 *
 *	Notes:
 *
 *	(1)	Cundy&Roulette's trapezohedron has been renamed to
 *		deltohedron, as its faces are deltoids, not trapezoids.
 *	(2)	The names of the non-dihedral polyhedra are those
 *		which appear in Wenninger (1984). Some of them are
 *		slightly modified versions of those in Wenninger (1971).
 *
 *	References:
 *
 *	Coxeter, H.S.M., Longuet-Higgins, M.S. & Miller, J.C.P.,
 *		Uniform polyhedra, Phil. Trans. Royal Soc. London, Ser. A,
 *		246 (1953), 401-409.
 *	Cundy, H.M. & Rollett, A.P.,
 *		"Mathematical Models", 3rd Ed., Tarquin, 1981.
 *	Har'El, Z.
 *		Unifom solution for uniform polyhedra, Geometriae Dedicata,
 *		47 (1993), 57-110.
 *	Wenninger, M.J.,
 *		"Polyhedron Models", Cambridge University Press, 1971.
 *		"Dual Models", Cambridge University Press, 1984.
 *
 *****************************************************************************
 */
#include "kaleido.h"

Uniform uniform[] = {

/******************************************************************************
*		Dihedral Schwarz Triangles (D5 only)
******************************************************************************/

/* (2 2 5) (D1/5) */

/*1*/	{"2 5|2","pentagonal prism",
			"pentagonal dipyramid",0,0},
/*2*/	{"|2 2 5","pentagonal antiprism",
			"pentagonal deltohedron",0,0},

/* (2 2 5/2) (D2/5) */

/*3*/	{"2 5/2|2","pentagrammic prism",
			"pentagrammic dipyramid",0,0},
/*4*/	{"|2 2 5/2","pentagrammic antiprism",
			"pentagrammic deltohedron",0,0},

/* (5/3 2 2) (D3/5) */

/*5*/	{"|2 2 5/3","pentagrammic crossed antiprism",
			"pentagrammic concave deltohedron",0,0},

/*******************************************************************************
*		Tetrahedral Schwarz Triangles
*******************************************************************************/

/* (2 3 3) (T1) */

/*6*/	{"3|2 3","tetrahedron",
			"tetrahedron",15,1},
/*7*/	{"2 3|3","truncated tetrahedron",
			"triakistetrahedron",16,6},

/* (3/2 3 3) (T2) */

/*8*/	{"3/2 3|3","octahemioctahedron",
			"octahemioctacron",37,68},

/* (3/2 2 3) (T3) */

/*9*/	{"3/2 3|2","tetrahemihexahedron",
			"tetrahemihexacron",36,67},

/******************************************************************************
*		Octahedral Schwarz Triangles
******************************************************************************/

/* (2 3 4) (O1) */

/*10*/	{"4|2 3","octahedron",
			"cube",17,2},
/*11*/	{"3|2 4","cube",
			"octahedron",18,3},
/*12*/	{"2|3 4","cuboctahedron",
			"rhombic dodecahedron",19,11},
/*13*/	{"2 4|3","truncated octahedron",
			"tetrakishexahedron",20,7},
/*14*/	{"2 3|4","truncated cube",
			"triakisoctahedron",21,8},
/*15*/	{"3 4|2","rhombicuboctahedron",
			"deltoidal icositetrahedron",22,13},
/*16*/	{"2 3 4|","truncated cuboctahedron",
			"disdyakisdodecahedron",23,15},
/*17*/	{"|2 3 4","snub cube",
			"pentagonal icositetrahedron",24,17},

/* (3/2 4 4) (O2b) */

/*18*/	{"3/2 4|4","small cubicuboctahedron",
			"small hexacronic icositetrahedron",38,69},

/* (4/3 3 4) (O4) */

/*19*/	{"3 4|4/3","great cubicuboctahedron",
			"great hexacronic icositetrahedron",50,77},
/*20*/	{"4/3 4|3","cubohemioctahedron",
			"hexahemioctacron",51,78},
/*21*/	{"4/3 3 4|","cubitruncated cuboctahedron",
			"tetradyakishexahedron",52,79},

/* (3/2 2 4) (O5) */

/*22*/	{"3/2 4|2","great rhombicuboctahedron",
			"great deltoidal icositetrahedron",59,85},
/*23*/	{"3/2 2 4|","small rhombihexahedron",
			"small rhombihexacron",60,86},

/* (4/3 2 3) (O7) */

/*24*/	{"2 3|4/3","stellated truncated hexahedron",
			"great triakisoctahedron",66,92},
/*25*/	{"4/3 2 3|","great truncated cuboctahedron",
			"great disdyakisdodecahedron",67,93},

/* (4/3 3/2 2) (O11) */

/*26*/	{"4/3 3/2 2|","great rhombihexahedron",
			"great rhombihexacron",82,103},

/******************************************************************************
*		Icosahedral Schwarz Triangles
******************************************************************************/

/* (2 3 5) (I1) */

/*27*/	{"5|2 3","icosahedron",
			"dodecahedron",25,4},
/*28*/	{"3|2 5","dodecahedron",
			"icosahedron",26,5},
/*29*/	{"2|3 5","icosidodecahedron",
			"rhombic triacontahedron",28,12},
/*30*/	{"2 5|3","truncated icosahedron",
			"pentakisdodecahedron",27,9},
/*31*/	{"2 3|5","truncated dodecahedron",
			"triakisicosahedron",29,10},
/*32*/	{"3 5|2","rhombicosidodecahedron",
			"deltoidal hexecontahedron",30,14},
/*33*/	{"2 3 5|","truncated icosidodechedon",
			"disdyakistriacontahedron",31,16},
/*34*/	{"|2 3 5","snub dodecahedron",
			"pentagonal hexecontahedron",32,18},

/* (5/2 3 3) (I2a) */

/*35*/	{"3|5/2 3","small ditrigonal icosidodecahedron",
			"small triambic icosahedron",39,70},
/*36*/	{"5/2 3|3","small icosicosidodecahedron",
			"small icosacronic hexecontahedron",40,71},
/*37*/	{"|5/2 3 3","small snub icosicosidodecahedron",
			"small hexagonal hexecontahedron",41,110},

/* (3/2 5 5) (I2b) */

/*38*/	{"3/2 5|5","small dodecicosidodecahedron",
			"small dodecacronic hexecontahedron",42,72},

/* (2 5/2 5) (I3) */

/*39*/	{"5|2 5/2","small stellated dodecahedron",
			"great dodecahedron",43,20},
/*40*/	{"5/2|2 5","great dodecahedron",
			"small stellated dodecahedron",44,21},
/*41*/	{"2|5/2 5","great dodecadodecahedron",
			"medial rhombic triacontahedron",45,73},
/*42*/	{"2 5/2|5","truncated great dodecahedron",
			"small stellapentakisdodecahedron",47,75},
/*43*/	{"5/2 5|2","rhombidodecadodecahedron",
			"medial deltoidal hexecontahedron",48,76},
/*44*/	{"2 5/2 5|","small rhombidodecahedron",
			"small rhombidodecacron",46,74},
/*45*/	{"|2 5/2 5","snub dodecadodecahedron",
			"medial pentagonal hexecontahedron",49,111},

/* (5/3 3 5) (I4) */

/*46*/	{"3|5/3 5","ditrigonal dodecadodecahedron",
			"medial triambic icosahedron",53,80},
/*47*/	{"3 5|5/3","great ditrigonal dodecicosidodecahedron",
			"great ditrigonal dodecacronic hexecontahedron",54,81},
/*48*/	{"5/3 3|5","small ditrigonal dodecicosidodecahedron",
			"small ditrigonal dodecacronic hexecontahedron",55,82},
/*49*/	{"5/3 5|3","icosidodecadodecahedron",
			"medial icosacronic hexecontahedron",56,83},
/*50*/	{"5/3 3 5|","icositruncated dodecadodecahedron",
			"tridyakisicosahedron",57,84},
/*51*/	{"|5/3 3 5","snub icosidodecadodecahedron",
			"medial hexagonal hexecontahedron",58,112},

/* (3/2 3 5) (I6b) */

/*52*/	{"3/2|3 5","great ditrigonal icosidodecahedron",
			"great triambic icosahedron",61,87},
/*53*/	{"3/2 5|3","great icosicosidodecahedron",
			"great icosacronic hexecontahedron",62,88},
/*54*/	{"3/2 3|5","small icosihemidodecahedron",
			"small icosihemidodecacron",63,89},
/*55*/	{"3/2 3 5|","small dodecicosahedron",
			"small dodecicosacron",64,90},

/* (5/4 5 5) (I6c) */

/*56*/	{"5/4 5|5","small dodecahemidodecahedron",
			"small dodecahemidodecacron",65,91},

/* (2 5/2 3) (I7) */

/*57*/	{"3|2 5/2","great stellated dodecahedron",
			"great icosahedron",68,22},
/*58*/	{"5/2|2 3","great icosahedron",
			"great stellated dodecahedron",69,41},
/*59*/	{"2|5/2 3","great icosidodecahedron",
			"great rhombic triacontahedron",70,94},
/*60*/	{"2 5/2|3","great truncated icosahedron",
			"great stellapentakisdodecahedron",71,95},
/*61*/	{"2 5/2 3|","rhombicosahedron",
			"rhombicosacron",72,96},
/*62*/	{"|2 5/2 3","great snub icosidodecahedron",
			"great pentagonal hexecontahedron",73,113},

/* (5/3 2 5) (I9) */

/*63*/	{"2 5|5/3","small stellated truncated dodecahedron",
			"great pentakisdodekahedron",74,97},
/*64*/	{"5/3 2 5|","truncated dodecadodecahedron",
			"medial disdyakistriacontahedron",75,98},
/*65*/	{"|5/3 2 5","inverted snub dodecadodecahedron",
			"medial inverted pentagonal hexecontahedron",76,114},

/* (5/3 5/2 3) (I10a) */

/*66*/	{"5/2 3|5/3","great dodecicosidodecahedron",
			"great dodecacronic hexecontahedron",77,99},
/*67*/	{"5/3 5/2|3","small dodecahemicosahedron",
			"small dodecahemicosacron",78,100},
/*68*/	{"5/3 5/2 3|","great dodecicosahedron",
			"great dodecicosacron",79,101},
/*69*/	{"|5/3 5/2 3","great snub dodecicosidodecahedron",
			"great hexagonal hexecontahedron",80,115},

/* (5/4 3 5) (I10b) */

/*70*/	{"5/4 5|3","great dodecahemicosahedron",
			"great dodecahemicosacron",81,102},

/* (5/3 2 3) (I13) */

/*71*/	{"2 3|5/3","great stellated truncated dodecahedron",
			"great triakisicosahedron",83,104},
/*72*/	{"5/3 3|2","great rhombicosidodecahedron",
			"great deltoidal hexecontahedron",84,105},
/*73*/	{"5/3 2 3|","great truncated icosidodecahedron",
			"great disdyakistriacontahedron",87,108},
/*74*/	{"|5/3 2 3","great inverted snub icosidodecahedron",
			"great inverted pentagonal hexecontahedron",88,116},

/* (5/3 5/3 5/2) (I18a) */

/*75*/	{"5/3 5/2|5/3","great dodecahemidodecahedron",
			"great dodecahemidodecacron",86,107},

/* (3/2 5/3 3) (I18b) */

/*76*/	{"3/2 3|5/3","great icosihemidodecahedron",
			"great icosihemidodecacron",85,106},

/* (3/2 3/2 5/3) (I22) */

/*77*/	{"|3/2 3/2 5/2","small retrosnub icosicosidodecahedron",
			"small hexagrammic hexecontahedron",91,118},

/* (3/2 5/3 2) (I23) */

/*78*/	{"3/2 5/3 2|","great rhombidodecahedron",
			"great rhombidodecacron",89,109},
/*79*/	{"|3/2 5/3 2","great retrosnub icosidodecahedron",
			"great pentagrammic hexecontahedron",90,117},

/******************************************************************************
*		Last But Not Least
******************************************************************************/

/*80*/	{"3/2 5/3 3 5/2","great dirhombicosidodecahedron",
			"great dirhombicosidodecacron",92,119}
};

int last_uniform = sizeof (uniform) / sizeof (uniform[0]);
