OBJS:= main.o 

LIBCYAML_LIBS:=$$(pkgconf --with-path=/usr/local/lib/pkgconfig --libs libcyaml)
LIBCYAML_CFLAGS:=$$(pkgconf --with-path=/usr/local/lib/pkgconfig --cflags libcyaml)

LDFLAGS=$(LIBCYAML_LIBS) 
CFLAGS=$(LIBCYAML_CFLAGS) -Wall -O3


kube-ps1: $(OBJS) libcyaml.a
		$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o:%.c 
	$(CC) $(CFLAGS) -c $< -o $@ -I.

clean:
		rm -f kube-ps1 main.o
