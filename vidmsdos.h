#ident "$Id: vidmsdos.h,v 3.27 2002-01-06 16:24:16+02 rl Exp $"
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
#include <graph.h>
#include <conio.h>
#define INTENSITY_DELTA 3
#define VIDEOSPLIT 0

static struct {
	double width, height;
} video;

#define videoclose() _setvideomode(_DEFAULTMODE)
#define videoclear() _clearscreen(_GCLEARSCREEN)
#define videoreadkey() getch()
#define videokeypressed() (kbhit()?getch():0)
#define videobeep() putch('\007')
#define videotitle(x,c) (_settextcolor(c),_settextposition(1,1),\
	_outtext(x))
#define videosubtitle(x,c) (_settextcolor(c),_settextposition(3,1),\
	_outtext(x))
#define videosubsub(x,c) (_settextcolor(c),_settextposition(5,1),\
	_outtext(x))
#define videoredraw() 0 /*always fail*/
#define videomoveto(a,b) _moveto((short)(a),(short)(b))
#define videosetcolor(c) _setcolor(c)
#define videolineto(a,b) _lineto((short)(a),(short)(b))


static 
videoinit(x,red,green, blue,light)
{
	int i;
	long j;
	struct videoconfig cnf;
	if (!_getvideoconfig (&cnf)) return 0;
	if (x < 0)
		x = cnf.adapter & _VGA ?_VRES16COLOR : _MRES256COLOR;
	if (!_setvideomode (x)) return 0;
	if (!_getvideoconfig (&cnf)) return 0;
	video.width=cnf.numxpixels;
	video.height=cnf.numypixels;
	if (cnf.numcolors < 16) return 0;
	for (i=16,j=0; --i; j += INTENSITY_DELTA)
		_remappalette(i,(!red?0L:light?j:63-j)+
			(!green?0L:(light?j:63-j)<<8)+
			(!blue?0L:(light?j:63-j)<<16));
	_remappalette (0, (!red||!light?0L:63L) + (!green||!light?0L:63L<<8)+
		(!blue||!light?0L:63L<<16));
	return 1;
}
