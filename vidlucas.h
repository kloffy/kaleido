#ident "$Id: vidlucas.h,v 3.27 2002-01-06 16:24:03+02 rl Exp $"
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

/* Lucasfilm graphics interface
 * written by John Firth <jrf@uk.ac.york.minster>
 * black and white only
 */

#include <display.h>

#define MAXX 512	/* polyhedra box width */
#define MAXY 512	/* polyhedra box height */
#define MAXT 20		/* title box height */
#define VIDEOSPLIT	1

static struct {
	double width,height;
	short x, y;
	int col;
} video;

#define videoclose()
#define videobeep()
#define videoredraw()	0
#define videotitle(x, c)	videostring(x, c, 2)
#define videosubtitle(x, c)	videostring(x, c, 1)
#define videosubsub(x, c)	videostring(x, c, 0)
#define videoclear() rect(Display, Rect(0, 0, MAXX, MAXY), F_CLR)
/*
 * Unfortunately F_XOR produces some odd effects which need investigating
 */
#define videosetcolor(c) (video.col = (c) ? F_STORE : F_CLR)
#define videomoveto(a, b) (video.x = (short)(a), video.y = (short)(b))
#define videolineto(a, b)\
	(segment(Display, Pt(video.x, video.y), Pt((short)(a), (short)(b)), video.col),\
	video.x = (short)(a), video.y = (short)(b))

static void
videostring(x,c,p)
char *x;
int c,p;
{
	int w = (MAXX-StrHS(defont, x))/2;

	if (w < 0) w = 0;
	rect(Display, Rect(0, MAXY+p*MAXT, MAXX, MAXY+(p+1)*MAXT), F_CLR);
	segment(Display, Pt(0, MAXY+p*MAXT), Pt(MAXX, MAXY+p*MAXT), F_STORE);
	segment(Display, Pt(0, MAXY+(p+1)*MAXT), Pt(MAXX, MAXY+(p+1)*MAXT), F_STORE);
	string(Display, Pt(w, MAXY+p*MAXT+MAXT/4), x, defont, F_STORE);
}

static int
videoinit(x,red,green,blue,light)
{
	video.width = (double)MAXX;
	video.height = (double)MAXY;
	SetDisplayRect(Rect(0, 0, MAXX, MAXY+3*MAXT));
	InitDisplay();
	InitDevices(KBD);
	Show();
	return 1;
}
	
static int
videoreadkey()
{
	int w = Wait(KBD);

	if (w&KBD)
		return kbdchar();
	else
		return 0;
}

static int
videokeypressed()
{
	int w = Poll(KBD);

	if (w&KBD)
		return kbdchar();
	else
		return 0;
}
