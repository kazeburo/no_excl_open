#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>

void __attribute__((constructor)) unset_ld_preload() {
    unsetenv("LD_PRELOAD");
}

int open(const char *pathname, int flags, ...)
{
    static int (*func_open)(const char *, int, mode_t);
    va_list ap;
	mode_t mode;
    int fd;

    if (!func_open)
        func_open = dlsym (RTLD_NEXT, "open");

    va_start(ap, flags);
    mode = va_arg(ap, int);
    va_end(ap);

    // O_RDWR and ! O_TRUNC
    if ( (flags & O_RDWR) != 0 && (flags & O_TRUNC) == 0 ) {
        flags = flags & ~O_EXCL;
    }

    fd = func_open(pathname, flags, mode);
    return fd;
}

int open64(const char *pathname, int flags, ...)
{
    static int (*func_open64)(const char *, int, mode_t);
    va_list ap;
	mode_t mode;
    int fd;

    if (!func_open64)
        func_open64 = dlsym (RTLD_NEXT, "open64");

    va_start(ap, flags);
    mode = va_arg(ap, int);
    va_end(ap);

    // O_RDWR and ! O_TRUNC
    if ( (flags & O_RDWR) != 0 && (flags & O_TRUNC) == 0 ) {
        flags = flags & ~O_EXCL;
    }

    fd = func_open64(pathname, flags, mode);
    return fd;
}
