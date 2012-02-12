#ifndef BB_ANDROID_H
#define BB_ANDROID_H 1

#include <android/api-level.h>

#include <sys/wait.h>
#define wait3(status, options, rusage) wait4(-1, status, options, rusage)

// syscalls
extern int sethostname(const char *name, size_t len);
extern int pivot_root(const char *new_root, const char *put_old);
extern int stime(const time_t *t);
extern pid_t getsid(pid_t pid);
extern ssize_t readahead(int fd, off64_t offset, size_t count);

#include <mntent.h>
#define MNTOPT_NOAUTO       "noauto"    /* Do not auto mount.  */
extern int addmntent(FILE *fp, const struct mntent *mnt);
extern char *hasmntopt (const struct mntent *mnt, const char *opt);

#if __ANDROID_API__ < 21
// bionic does not define stubs as weak
#define getmntent android_getmntent
extern struct mntent *getmntent(FILE *fp);
extern struct mntent *getmntent_r(FILE *fp, struct mntent *mnt, char *buf, int buflen);
extern FILE *setmntent(const char *filename, const char *type);
extern int endmntent(FILE *fp);

#include <termios.h>
extern int cfsetspeed (struct termios *termios_p, speed_t speed);
extern int tcdrain(int fd);

#include <linux/fs.h>
#define BLKDISCARD      _IO(0x12,119)
#define BLKSECDISCARD   _IO(0x12,125)

// linux/rtnetlink.h
#define RTA_TABLE 15
#endif

// unistd.h
extern int getlogin_r(char *name, size_t size);

#if __ANDROID_API__ < 12
#include <net/if_ether.h>
extern struct ether_addr *ether_aton_r(const char *asc, struct ether_addr *addr);
#endif

// sys/swap.h
#define SWAP_FLAG_PREFER        0x8000
#define SWAP_FLAG_PRIO_MASK     0x7fff
extern int swapon(const char *path, int swapflags);
extern int swapoff(const char *path);

// sys/timex.h
struct timex
{
  unsigned int modes;   /* mode selector */
  long int offset;  /* time offset (usec) */
  long int freq;    /* frequency offset (scaled ppm) */
  long int maxerror;    /* maximum error (usec) */
  long int esterror;    /* estimated error (usec) */
  int status;       /* clock command/status */
  long int constant;    /* pll time constant */
  long int precision;   /* clock precision (usec) (read only) */
  long int tolerance;   /* clock frequency tolerance (ppm) (read only) */
  struct timeval time;  /* (read only) */
  long int tick;    /* (modified) usecs between clock ticks */

  long int ppsfreq; /* pps frequency (scaled ppm) (ro) */
  long int jitter;  /* pps jitter (us) (ro) */
  int shift;        /* interval duration (s) (shift) (ro) */
  long int stabil;  /* pps stability (scaled ppm) (ro) */
  long int jitcnt;  /* jitter limit exceeded (ro) */
  long int calcnt;  /* calibration intervals (ro) */
  long int errcnt;  /* calibration errors (ro) */
  long int stbcnt;  /* stability limit exceeded (ro) */

  int tai;      /* TAI offset (ro) */

  /* ??? */
  int  :32; int  :32; int  :32; int  :32;
  int  :32; int  :32; int  :32; int  :32;
  int  :32; int  :32; int  :32;
};

extern int adjtimex(struct timex *buf);

#define ADJ_OFFSET              0x0001 /* time offset */
#define ADJ_FREQUENCY           0x0002 /* frequency offset */
#define ADJ_MAXERROR            0x0004 /* maximum time error */
#define ADJ_ESTERROR            0x0008 /* estimated time error */
#define ADJ_STATUS              0x0010 /* clock status */
#define ADJ_TIMECONST           0x0020 /* pll time constant */
#define ADJ_TICK                0x4000 /* tick value */
#define ADJ_OFFSET_SINGLESHOT   0x8001 /* old-fashioned adjtime() */

/* Status codes (timex.status) */
#define STA_PLL                 0x0001  /* enable PLL updates (rw) */
#define STA_PPSFREQ             0x0002  /* enable PPS freq discipline (rw) */
#define STA_PPSTIME             0x0004  /* enable PPS time discipline (rw) */
#define STA_FLL                 0x0008  /* select frequency-lock mode (rw) */
#define STA_INS                 0x0010  /* insert leap (rw) */
#define STA_DEL                 0x0020  /* delete leap (rw) */
#define STA_UNSYNC              0x0040  /* clock unsynchronized (rw) */
#define STA_FREQHOLD            0x0080  /* hold frequency (rw) */
#define STA_PPSSIGNAL           0x0100  /* PPS signal present (ro) */
#define STA_PPSJITTER           0x0200  /* PPS signal jitter exceeded (ro) */
#define STA_PPSWANDER           0x0400  /* PPS signal wander exceeded (ro) */
#define STA_PPSERROR            0x0800  /* PPS signal calibration error (ro) */
#define STA_CLOCKERR            0x1000  /* clock hardware fault (ro) */

// linux/capability.h
#include <linux/capability.h>

#ifndef cap_valid
#define _LINUX_CAPABILITY_VERSION_1 0x19980330
#define _LINUX_CAPABILITY_U32S_1 1
#define _LINUX_CAPABILITY_VERSION_2 0x20071026
#define _LINUX_CAPABILITY_U32S_2 2
#define _LINUX_CAPABILITY_VERSION_3 0x20080522
#define _LINUX_CAPABILITY_U32S_3 2

#define CAP_BLOCK_SUSPEND 36
#define CAP_LAST_CAP CAP_BLOCK_SUSPEND
#define cap_valid(x) ((x) >= 0 && (x) <= CAP_LAST_CAP)

#define CAP_TO_INDEX(x) ((x) >> 5)
#define CAP_TO_MASK(x) (1 << ((x) & 31))
#endif

// linux/prctl.h
#include <linux/prctl.h>

#ifndef PR_CAPBSET_READ
#define PR_CAPBSET_READ 23
#define PR_CAPBSET_DROP 24
#endif

// linux/sched.h
#ifndef SCHED_BATCH
#define SCHED_BATCH 3
#endif

#endif
