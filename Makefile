all: formlog.cgi

CFLAGS.kcgi!=	pkg-config --cflags kcgi
LDLIBS.kcgi!=	pkg-config --static --libs kcgi

CFLAGS+=	${CFLAGS.kcgi}
LDFLAGS+=	-static
LDLIBS+=	${LDLIBS.kcgi}

all: formlog.cgi

install: formlog.cgi
	install -m755 formlog.cgi /var/www/cgi-bin/

clean:
	rm -f formlog.cgi formlog.o

formlog.cgi: formlog.o
	${CC} ${LDFLAGS} -o formlog.cgi formlog.o ${LDLIBS}

.PHONY: all install clean
