#ident "$Id: vidjdyx.h,v 3.27 2002-01-06 16:23:48+02 rl Exp $"
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
/* JDyx graphics library is Copyright © 1989, 1990 by JDyx Enterprises */
#include "site.h"
#include "ncenI24.h"
#include "ncenI12.h"
#define INTENSITY_DELTA 3
#define VIDEOSPLIT 0

static struct {
	struct _Font bigfont, smallfont;
	int color;
	double width, height;
	short x, y;
} video;

#define videoclose() vt_Close()
#define videoclear() (*vt_Clrscr)()
#define videoreadkey() vt_ReadKey()
#define videokeypressed() vt_KeyPressed()
#define videobeep() vt_Sound(1200,200)
#define videotitle(x,c) Font_Display(&video.bigfont,x,0,25,c)
#define videosubtitle(x,c) Font_Display(&video.smallfont,x,0,50,c)
#define videosubsub(x,c) Font_Display(&video.smallfont,x,0,75,c)
#define videoredraw() 0 /*always fail*/
#define videomoveto(a,b) (video.x=a,video.y=b)
#define videosetcolor(c) (video.color=c)
#define videolineto(a,b) \
	((*vt_Line)(video.color,video.x,video.y,(short)(a),(short)(b)),\
	video.x=a,video.y=b)


static
videoinit(x,red,green,blue,light)
{
	int i;
	unsigned j;
	if (x<0) x = VGA_640;
	if (vt_Init (x)) return 0;
	if (vt_Colors < 16) return 0;
	video.bigfont.font = ncenI24;
	video.bigfont.size = ncenI24_size;
	video.smallfont.font = ncenI12;
	video.smallfont.size = ncenI12_size;
	video.width=vt_Width;
	video.height=vt_Height;
	for (i = 16, j=0; --i; j+=INTENSITY_DELTA) {
		vt_SetColorMapValue (i, !red?0:light?j:63-j,
			!green?0:light?j:63-j, !blue?0:light?j:63-j);
	}
	vt_SetColorMapValue (0, !red||!light?0:63,
		!green||!light?0:63, !blue||!light?0:63);
	return 1;
}
