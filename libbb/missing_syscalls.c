/*
 * Copyright 2012, Denys Vlasenko
 *
 * Licensed under GPLv2, see file LICENSE in this source tree.
 */
//kbuild:lib-y += missing_syscalls.o

#include "libbb.h"

#if defined(ANDROID) || defined(__ANDROID__)
/*# include <linux/timex.h> - for struct timex, but may collide with <time.h> */
# include <sys/syscall.h>
# if __ANDROID_API__ < 17
pid_t getsid(pid_t pid)
{
	return syscall(__NR_getsid, pid);
}
#endif

# if __ANDROID_API__ < 23
int _sethostname(const char *name, size_t len);
int _sethostname(const char *name, size_t len)
{
	return syscall(__NR_sethostname, name, len);
}

weak_alias(_sethostname, sethostname);
#endif

# if __ANDROID_API__ < 24
struct timex;
int _adjtimex(struct timex *buf);
int _adjtimex(struct timex *buf)
{
	return syscall(__NR_adjtimex, buf);
}

weak_alias(_adjtimex, adjtimex);
#endif

int pivot_root(const char *new_root, const char *put_old)
{
	return syscall(__NR_pivot_root, new_root, put_old);
}

# if __ANDROID_API__ < 21
int tcdrain(int fd)
{
	return ioctl(fd, TCSBRK, 1);
}
# endif

#if __ANDROID_API__ < 16
int setxattr(const char *path, const char *name, const void *value, size_t size, int flags)
{
    return syscall(__NR_setxattr, path, name, value, size, flags);
}

int lsetxattr(const char *path, const char *name, const void *value, size_t size, int flags)
{
    return syscall(__NR_lsetxattr, path, name, value, size, flags);
}

int removexattr(const char *path, const char *name)
{
    return syscall(__NR_removexattr, path, name);
}

int lremovexattr(const char *path, const char *name)
{
    return syscall(__NR_lremovexattr, path, name);
}
#endif

#if (__ANDROID_API__ < 21) || ((defined(__arm__) || defined(__i386__)) && (__ANDROID_API__ < 19))
int swapon(const char *path, int swapflags)
{
    return syscall(__NR_swapon, path, swapflags);
}

int swapoff(const char *path)
{
    return syscall(__NR_swapoff, path);
}
#endif

#endif
