#ident "$Id: vidx11.h,v 3.27 2002-01-06 16:24:23+02 rl Exp $"
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
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#define BIGFONT "-*-new century schoolbook-medium-i-*-*-*-240-*-*-*-*-*-*"
#define SMALLFONT "-*-new century schoolbook-medium-i-*-*-*-120-*-*-*-*-*-*"
#define DEFAULTFONT "-*-*-*-*-*-*-*-*-*-*-*-*-*-*"
#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 640
#endif
#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 480
#endif
#ifndef INTENSITY_DELTA
#define INTENSITY_DELTA 3072
#endif
#define VIDEOSPLIT 1

static struct {
	Display *dis;
	Colormap map;
	Window win;
	double width,height;
	GC gc;
	XColor color[16];
	XEvent evt;
	Font bigfont, smallfont;
	char str[2];
	short x, y;
} video;

#define videoclose() XCloseDisplay(video.dis)
#define videoclear() XClearWindow(video.dis,video.win)
#define videobeep()	XBell(video.dis,100)
#define videokeypressed() \
	(XCheckWindowEvent(video.dis,video.win,KeyPressMask,&video.evt)&&\
	XLookupString(&video.evt.xkey,video.str,1,NULL,NULL) ? *video.str : 0)
#define videotitle(x,c) \
	(XSetFont(video.dis,video.gc,video.bigfont),\
	XSetForeground(video.dis,video.gc,video.color[c].pixel),\
	XDrawString(video.dis,video.win,video.gc,0,25,x,strlen(x)))
#define videosubtitle(x,c) \
	(XSetFont(video.dis,video.gc,video.smallfont),\
	XSetForeground(video.dis,video.gc,video.color[c].pixel),\
	XDrawString(video.dis,video.win,video.gc,0,50,x,strlen(x)))
#define videosubsub(x,c) \
	(XSetFont(video.dis,video.gc,video.smallfont),\
	XSetForeground(video.dis,video.gc,video.color[c].pixel),\
	XDrawString(video.dis,video.win,video.gc,0,75,x,strlen(x)))
#define videomoveto(a,b) (video.x=a,video.y=b)
#define videosetcolor(c) XSetForeground(video.dis,video.gc,video.color[c].pixel)
#define videolineto(a,b) \
	(XDrawLine(video.dis,video.win,video.gc,video.x,video.y,\
	(short)(a),(short)(b)),video.x=a,video.y=b)

static
videoredraw ()
{
	XCheckWindowEvent (video.dis, video.win, ExposureMask | StructureNotifyMask,
		&video.evt);
	if (video.evt.type == ConfigureNotify &&
		(video.width !=  video.evt.xconfigure.width ||
		video.height != video.evt.xconfigure.height)) {
		video.width = video.evt.xconfigure.width;
		video.height = video.evt.xconfigure.height;
		XClearWindow(video.dis,video.win);
		return 1;
	}
	else if (video.evt.type == Expose) return 1;
	return 0;
}

static
videoinit(x,red,green,blue,light)
{
	int i;
	unsigned j;
	static XClassHint class={"Kaleido", "Kaleido"};
	XFontStruct *font;

	if (!(video.dis = XOpenDisplay (""))) return 0;

	if(!(video.map = XDefaultColormap (video.dis,
		DefaultScreen (video.dis)))) return 0;
	for (i=16, j=0; --i; j+= INTENSITY_DELTA) {
		video.color[i].red = !red ? 0 : light ? j : ~j;
		video.color[i].green = !green ? 0 : light ? j : ~j;
		video.color[i].blue = !blue ? 0 : light ? j : ~j;
		if(!XAllocColor(video.dis,video.map,&video.color[i])) return 0;
	}
	video.color[0].red = !red || !light ? 0 : ~0;
	video.color[0].green = !green || !light ? 0 : ~0;
	video.color[0].blue = !blue || !light ? 0 : ~0;
	if(!XAllocColor(video.dis,video.map,&video.color[0])) return 0;

	if (!(font=XLoadQueryFont(video.dis,BIGFONT)) &&
		!(font=XLoadQueryFont(video.dis,DEFAULTFONT))) return 0;
	video.bigfont = font->fid;
	if (!(font=XLoadQueryFont(video.dis,SMALLFONT)) &&
		!(font=XLoadQueryFont(video.dis,DEFAULTFONT))) return 0;
	video.smallfont = font->fid;

	video.win = XCreateSimpleWindow (video.dis,
		RootWindow (video.dis,DefaultScreen(video.dis)),
		(DisplayWidth (video.dis,DefaultScreen(video.dis)) - DEFAULT_WIDTH) / 2,
		(DisplayHeight (video.dis,DefaultScreen(video.dis)) - DEFAULT_HEIGHT) / 2,
		DEFAULT_WIDTH, DEFAULT_HEIGHT, 2, 
		video.color[15].pixel, video.color[0].pixel);

	video.gc=XCreateGC(video.dis,video.win,0,NULL);

	XStoreName (video.dis, video.win, "Kaleido");
	XSetIconName  (video.dis, video.win, "Kaleido");
	XSetClassHint (video.dis, video.win, &class);
	XSelectInput (video.dis, video.win,
		StructureNotifyMask | KeyPressMask | ExposureMask);
	XMapRaised(video.dis,video.win);
	
	return 1;
}
	
static char
videoreadkey()
{	
	for (;;) {
		XWindowEvent(video.dis,video.win,KeyPressMask,&video.evt);
		if (XLookupString(&video.evt.xkey,video.str,1,NULL,NULL))
			return *video.str;
	}
}
