.PHONY: all static shared clean

all:bstrutils.c main.c
	@echo "all"
	gcc -c bstrutils.c -o bstrutils.o
	ar rcs libstrutils.a bstrutils.o
	nm libstrutils.a
	gcc main.c -L. -lstrutils -o main_static
	rm -rf bstrutils.o
	gcc -c -fPIC bstrutils.c
	gcc -shared -o libstrutils.so bstrutils.o
	gcc main.c -L. -lstrutils -o main_shared

static:bstrutils.c main.c
	@echo "static"
	gcc -c bstrutils.c -o bstrutils.o
	ar rcs libstrutils.a bstrutils.o
	nm libstrutils.a
	gcc main.c -L. -lstrutils -o main_static

shared:bstrutils.c main.c
	@echo "shared"
	gcc -c -fPIC bstrutils.c
	gcc -shared -o libstrutils.so bstrutils.o
	gcc main.c -L. -lstrutils -o main_shared

clean:
	@echo "clear"
	rm -f bstrutils.o
	rm -f libstrutils.a
	rm -f libstrutils.so
	rm -f main_static
	rm -f main_shared
	rm -f main.o