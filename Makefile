VERSION=0.0.1

all: open_no_excl.so

.PHONY: open_no_excl.so

open_no_excl.so:
	gcc -shared -fPIC open_no_excl.c -o open_no_excl.so -ldl

clean:
	rm *.so

tag:
	git tag v${VERSION}
	git push origin v${VERSION}
	git push origin master
