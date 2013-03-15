#$Id: makefile,v 3.27 2002-01-06 16:39:02+02 rl Exp $
#******************************************************
# kaleido
#
#	Kaleidoscopic construction of uniform polyhedra
#	Copyright © 1991-2002 Dr. Zvi Har'El <rl@math.technion.ac.il>
#
# 	Redistribution and use in source and binary forms, with or without
# 	modification, are permitted provided that the following conditions
# 	are met:
# 
# 	1. Redistributions of source code must retain the above copyright
# 	   notice, this list of conditions and the following disclaimer.
# 
# 	2. Redistributions in binary form must reproduce the above copyright
# 	   notice, this list of conditions and the following disclaimer in
# 	   the documentation and/or other materials provided with the
# 	   distribution.
# 
# 	3. The end-user documentation included with the redistribution,
# 	   if any, must include the following acknowledgment:
# 		"This product includes software developed by
# 		 Dr. Zvi Har'El (http://www.math.technion.ac.il/~rl/)."
# 	   Alternately, this acknowledgment may appear in the software itself,
# 	   if and wherever such third-party acknowledgments normally appear.
# 
# 	This software is provided 'as-is', without any express or implied
# 	warranty.  In no event will the author be held liable for any
# 	damages arising from the use of this software.
#
#	Author:
#		Dr. Zvi Har'El,
#		Deptartment of Mathematics,
#		Technion, Israel Institue of Technology,
#		Haifa 32000, Israel.
#		E-Mail: rl@math.technion.ac.il
#******************************************************

BINDIR =	/usr/local/bin
MANDIR =	/usr/local/man/man1
INSTALL=	cp
OBJS   =	main.o kaleido.o scope.o uniform.o
GRAPH  =	-lX11
MATH   =	-lm
INCS   =	vidx11.h
PROGS  =	main.c kaleido.c scope.c uniform.c \
		    kaleido.h vidx11.h vidmsdos.h vidjdyx.h vidlucas.h \
		    schwarz.c
MSS    =	kaleido.man uniform.ms
UTILS  =	README makefile combine

# UNIX with X windows.

all:	kaleido schwarz

# MS-DOS, with MSC 5.10 graphics library.
exe:
	@$(MAKE) kaleido.exe schwarz.exe \
	    "OBJS=main.obj kaleido.obj scope.obj uniform.obj" \
	    GRAPH=graphics.lib MATH= INCS=vidmsdos.h CFLAGS="-F 1000"
	
# Linux, with XFree86.
linux:
	@$(MAKE) "GRAPH=-L/usr/X11R6/lib -lX11"

# UNIX Systen V/386 release 4, with X windows.
x386:
	@$(MAKE) "GRAPH=-lX11 -lsocket -lnsl"

# UNIX System V/386, with JDyx graphics library.
jdyx:
	@$(MAKE) "CFLAGS=-DJDYX $(CFLAGS)" \
	    GRAPH=libvt.a INCS=vidjdyx.h

# UNIX, no graphics.
noscope:
	@$(MAKE) "CFLAGS=-DNOSCOPE $(CFLAGS)" \
	    "OBJS=main.o kaleido.o uniform.o" GRAPH=

kaleido kaleido.exe:	$(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(GRAPH) $(MATH)

$(OBJS):	kaleido.h

scope.o scope.obj:	$(INCS)

schwarz schwarz.exe:	schwarz.c
	$(CC) -o $@ $(CFLAGS) $? $(MATH)
	
install:	$(BINDIR)/kaleido $(MANDIR)/kaleido.1

$(BINDIR)/kaleido:	kaleido
	$(INSTALL) $? $@
	chmod a=rx $@

$(MANDIR)/kaleido.1:	kaleido.man
	$(INSTALL) $? $@
	chmod a=r $@

clean:
	rm -f *.o *.obj *~

distclean:	clean
	rm -f kaleido schwarz *.exe
	
tar:	kaleido.tar.gz kaleido-rcs.tar.gz

kaleido.tar.gz: $(PROGS) $(UTILS) $(MSS) 
	tar zcvf $@ $(PROGS) $(UTILS) $(MSS)

kaleido-rcs.tar.gz: $(PROGS) $(UTILS) $(MSS) 
	tar zcvf $@ RCS

doc:	kaleido.txt kaleido.ps uniform.txt uniform.ps sources.ps tables.ps

kaleido.txt:	kaleido.man
	groff -Tutf8 -man -P-u -P-b kaleido.man >$@

kaleido.ps:		kaleido.man
	groff -man kaleido.man >$@

uniform.txt:	uniform.ms
	sed "/^define \//d" uniform.ms | \
	     groff -Tutf8 -t -N -e -ms -P-b -P-u >$@

uniform.ps:		uniform.ms kaleido combine
	rm -f poly???.pic dual???.pic
	kaleido -sppoly -Pdual -f25.71428 >/dev/null
	sh combine | groff -P-g -p -t -N -e -ms uniform.ms - >$@
	rm -f poly???.pic dual???.pic

sources.ps:	$(PROGS) $(UTILS)
	pp -u $(PROGS) -x $(UTILS)>$@

tables.ps:	kaleido schwarz
	kaleido -sd8 | pp -xn0 -."ds R Uniform Polyhedra" >$@
	schwarz | pp -xn0 -."ds R Schwarz Triangles" >>$@
