PROGRAM=cterm
OBJECTS=cterm.o selectwindow.o window.o cluster.o misc.o errorhandler.o menu.o about.o
CFLAGS=`pkg-config --cflags gtk+-2.0` -Wall
LDFLAGS=`pkg-config --libs gtk+-2.0` -lXmu -L/usr/X11R6/lib/ -lX11
BIN=${DESTDIR}/usr/bin
CC=gcc

.PHONY: clean all

all: ${OBJECTS}
	${CC} -o ${PROGRAM} ${CFLAGS} ${OBJECTS} ${LDFLAGS}

.c.o:
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	rm -f *.o ${PROGRAM}

install:
	install -d ${BIN} ${DESTDIR}/usr/share/lintian/overrides
	install ${PROGRAM} ${BIN}
	install -m 644 debian/cterm.lintian-override ${DESTDIR}/usr/share/lintian/overrides/cterm
