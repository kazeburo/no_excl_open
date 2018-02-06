open_no_excl.so:
	gcc -shared -fPIC open_no_excl.c -o open_no_excl.so -ldl

clean:
	rm *.so
