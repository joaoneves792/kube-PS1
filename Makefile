OBJS:= main.o 

LIBCYAML_LIBS:=$(shell pkgconf --with-path=/usr/local/lib/pkgconfig --libs-only-L libcyaml)
LIBCYAML_CFLAGS:=$(shell pkgconf --with-path=/usr/local/lib/pkgconfig --cflags libcyaml)

LDFLAGS=  $(LIBCYAML_LIBS) -Wl,-Bstatic -lcyaml -Wl,-Bdynamic -lyaml
CFLAGS=$(LIBCYAML_CFLAGS) -Wall -O3


kube-ps1: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o:%.c 
	$(CC) $(CFLAGS) -c $< -o $@ -I.

clean:
		rm -f kube-ps1 main.o
